#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdexcept>
#include <exception>
#include <utility>
#include <string>

#include "common_socket.h"
#include "common_Accion.h"
#include "common_OSError.h"


Socket::~Socket() {
    close(this->sfd);
}

Socket::Socket(int sfd) : sfd(sfd) {}

Socket::Socket(const char *port) { // server
    struct addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct sockaddr peer_addr;
    memset(&peer_addr, 0, sizeof(sockaddr));

    bind(port, hints);
    listen();
}

Socket::Socket(const char *port, const char *service) { // client
    struct addrinfo hints;
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    std::cerr << "Connecting..." << std::endl;

    connect(service, port, hints);
    std::cerr << "Connected: " << sfd << std::endl;
}

Socket& Socket::operator=(Socket&& other) {
    if (this != &other) {
        this->sfd = other.sfd;
        other.sfd = -1;
    }
    return *this;
}

Socket::Socket(Socket&& other) : sfd(other.sfd) {
    other.sfd = -1;
}

void Socket::connect(const char *service, const char *port, addrinfo &hints) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(port, service, &hints, &result)) != 0)
        throw std::invalid_argument("En getaddrinfo. Puerto o direccion incorrecta");

    for ( this->sfd = 0, it = result; it != NULL; it = it->ai_next ) {
        this->sfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if (this->sfd == -1) continue;
        if (::connect(this->sfd, it->ai_addr, it->ai_addrlen) == -1) {
            close(this->sfd);
            continue;
        }
        freeaddrinfo(result);
        return;
    }
    freeaddrinfo(result);
    throw std::runtime_error("No se pudo conectar");
}

void Socket::bind(const char *port, addrinfo &hints) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(NULL, port, &hints, &result)) != 0)
        throw std::invalid_argument("En getaddrinfo. Puerto o direccion incorrecta");

    it = result;
    for (this->sfd = 0; it != NULL; it = it->ai_next) {
        this->sfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if ( this->sfd != -1 ) {
            if (::bind(this->sfd, it->ai_addr, it->ai_addrlen) == 0) {
                freeaddrinfo(result);
                return;
            } else { close(this->sfd); }
        }
    }
    freeaddrinfo(result);
    throw std::runtime_error("No se pudo hacer bind a ningun addrinfo");
}

Socket Socket::accept() {
    struct sockaddr peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);
    int peer;
    if ((peer = ::accept(this->sfd, &peer_addr, &peer_addr_len)) == -1)
        throw std::runtime_error("No se pudo aceptar correctamente la conexion");
    return std::move(Socket(peer));
}

void Socket::listen() {
    if ( ::listen(this->sfd, 10) == -1 )
        throw std::runtime_error("En listen");
}

void Socket::send(const char &hexa) {
    int sent = ::send(this->sfd, &hexa, 1, MSG_NOSIGNAL);
    if (sent == -1) throw OSError("No se pudo enviar un byte");
    if (sent == 0) this->sfd = -1;
}

void Socket::read(char &hexa) {
    int read = ::recv(this->sfd, &hexa, 1, MSG_NOSIGNAL);
    if (read == -1) throw OSError("No se pudo leer un byte");
    if (read == 0) this->sfd = -1;
}

void Socket::send(std::string const &msg) {
    uint8_t l_net[2];
    const uint16_t l = msg.length();
    l_net[0] = htons(l) % 256;
    l_net[1] = htons(l) / 256;
    uint16_t sent = 0;
    while (sent < (l + 2)) {
        if (sent < 2) {
            sent += ::send(this->sfd, &l_net[sent], 2 - sent, MSG_NOSIGNAL);
        } else {
            sent += ::send(this->sfd, &msg.c_str()[sent-2], l - (sent-2), MSG_NOSIGNAL);
        }
        if (sent == 0) {
            this->sfd = -1;
            break;
        }
    }
}

std::string Socket::readString() {
    uint8_t l_net[2];
    char data[1000];
    uint16_t l = 0, read = 0;
    while (read < (l + 2)) {
        if (read < 2) {
            read += recv(this->sfd, &l_net[read], 2 - read, MSG_NOSIGNAL);
            if (read == 2) l = ntohs(l_net[1] * 256 + l_net[0]);
            if (read == 0) {
                this->sfd = -1;
                std::cerr << "Se cerró el socket" << std::endl;
                break;
            }
        } else {
            read += recv(this->sfd, &data[read-2], l - (read-2), MSG_NOSIGNAL);
        }
    }
    data[l] = '\0';
    return std::string(data);
}

void Socket::send(Listar const &listar) {
    send(LISTAR);
}

void Socket::send(Crear const &crear) {
    send(CREAR);
    send(crear.getNombre());
}

void Socket::send(Unirse const &unirse) {
    send(UNIRSE);
    send(unirse.getNombre());
}

void Socket::send(Jugar const &jugar) {
    send(JUGAR);
    const uint8_t coordenadas = (jugar.getX() << 4) | jugar.getY();
    send(coordenadas);
}

IAccion *Socket::read() {
    char hexa;
    read(hexa);
    switch (hexa) {
        case LISTAR:
            return new Listar();
        case CREAR:
            return new Crear(readString());
        case UNIRSE:
            return new Unirse(readString());
        case JUGAR:
            read(hexa);
            int x = (hexa >> 4) & 0x0F, y = hexa & 0x0F;
            return new Jugar(x, y);
    }
    throw std::runtime_error("Lectura incorrecta de la accion");
}

// std::istream& Socket::operator>>(std::istream& is) {
//     std::string str(is.rdbuf());
//     send();
//     return is;
// }

std::ostream& Socket::operator<<(std::ostream& os) {
    os << readString();
    return os;
}

bool Socket::isUp() const {
    return sfd != -1;
}
