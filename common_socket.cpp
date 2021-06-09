#include <stdexcept>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <exception>
#include <utility>

#include "common_OSError.h"
#include "common_socket.h"

Socket::Socket() {
    memset(&hints, 0, sizeof(addrinfo));
    memset(&peer_addr, 0, sizeof(sockaddr));
    this->hints.ai_family = AF_INET;
    this->hints.ai_socktype = SOCK_STREAM;
}

void Socket::connect(const char *port, const char *service ) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(port, service, &this->hints, &result)) != 0) {
        std::cerr << "Error in getaddrinfo" << std::endl;
        throw std::invalid_argument("Error en getaddrinfo. Puerto o direccion incorrecta");
        return;
    }
    for ( this->sfd = 0, it = result; it != NULL; it = it->ai_next ) {
        this->sfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if (this->sfd != -1) {
            if (::connect(this->sfd, it->ai_addr, it->ai_addrlen) != -1) {
                freeaddrinfo(result);
                return;
            } else { close(this->sfd); }
        }
    }
    freeaddrinfo(result);
    throw std::runtime_error("Error while trying to connect");
}

void Socket::bind(const char *port ) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(NULL, port, &this->hints, &result)) != 0) {
        std::cerr << "Error in getaddrinfo" << std::endl;
        return;
    }
    it = result;
    for ( this->sfd = 0; it != NULL; it = it->ai_next ) {
        this->sfd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if ( this->sfd != -1 ) {
            if ( ::bind(this->sfd, it->ai_addr, it->ai_addrlen) == 0 ) {
                freeaddrinfo(result);
                return;
            } else { close(this->sfd); }
        }
    }
    freeaddrinfo(result);
    throw std::runtime_error("Error while trying to bind");
}

void Socket::accept() {
    struct sockaddr peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);
    int cfd;
    if ( (cfd = ::accept(this->sfd, &peer_addr, &peer_addr_len)) == -1 ) {
        throw std::runtime_error("Error while trying to accept the connection");
        return;
    }
    close(this->sfd);
    this->sfd = cfd;
}

void Socket::listen() {
    if ( ::listen(this->sfd, 10) == -1 ) {
        throw std::runtime_error("Error while trying to listen");
        return;
    }
}

Socket::~Socket() {
    close(this->sfd);
    this->sfd = -1;
}

void Socket::send(const char *data, uint16_t l) {
    uint8_t l_net[2];
    l_net[0] = htons(l) % 256;
    l_net[1] = htons(l) / 256;
    uint16_t sent = 0;
    while (sent < (l + 2)) {
        if (sent < 2) {
            sent += ::send(this->sfd, &l_net[sent], 2 - sent, MSG_NOSIGNAL);
        } else {
            sent += ::send(this->sfd, &data[sent-2], l - (sent-2), MSG_NOSIGNAL);
        }
    }
}

void Socket::sendHexa(const char hexa) const {
    while (::send(this->sfd, &hexa, 1, MSG_NOSIGNAL) != 1) {}
}

void Socket::send(std::string const &msg) {
    uint8_t l_net[2];
    const uint16_t l = msg.length();
    l_net[0] = htons(msg.length()) % 256;
    l_net[1] = htons(msg.length()) / 256;
    uint16_t sent = 0;
    while (sent < (l + 2)) {
        if (sent < 2) {
            sent += ::send(this->sfd, &l_net[sent], 2 - sent, MSG_NOSIGNAL);
        } else {
            sent += ::send(this->sfd, &msg.c_str()[sent-2], l - (sent-2), MSG_NOSIGNAL);
        }
    }
}

void Socket::send(Listar const &listar) {
    sendHexa(LISTAR);
}

void Socket::send(Crear const &crear) {
    sendHexa(CREAR);
    send(crear.getNombre());
}

void Socket::send(Unirse const &unirse) {
    sendHexa(UNIRSE);
    send(unirse.getNombre());
}

void Socket::send(Jugar const &jugar) {
    sendHexa(JUGAR);
    const uint8_t coordenadas = (jugar.getX() << 4) | jugar.getY();
    sendHexa(coordenadas);
}

uint16_t Socket::read(char *data) {
    uint8_t l_net[2];
    uint16_t l = 0, read = 0;
    while (read < (l + 2)) {
        if (read < 2) {
            read += recv(this->sfd, &l_net[read], 2 - read, MSG_NOSIGNAL);
            if (read == 2) l = ntohs(l_net[1] * 256 + l_net[0]);
            if (!read) return 0;
        } else {
            read += recv(this->sfd, &data[read-2], l - (read-2), MSG_NOSIGNAL);
        }
    }
    data[l] = '\0';
    return l;
}

std::string Socket::readString() {
    uint8_t l_net[2];
    char data[100];
    uint16_t l = 0, read = 0;
    while (read < (l + 2)) {
        if (read < 2) {
            read += recv(this->sfd, &l_net[read], 2 - read, MSG_NOSIGNAL);
            if (read == 2) l = ntohs(l_net[1] * 256 + l_net[0]);
            if (!read) return 0;
        } else {
            read += recv(this->sfd, &data[read-2], l - (read-2), MSG_NOSIGNAL);
        }
    }
    data[l] = '\0';
    return std::string(data);
}

IAccion *Socket::read() {
    uint8_t hexa;
    recv(this->sfd, &hexa, 1, MSG_NOSIGNAL);
    switch (hexa) {
        case LISTAR:
            return new Listar();
            break;
        case CREAR: {
                std::string nombre = readString(); 
                return new Crear(nombre);
            }
            break;
        case UNIRSE: {
                std::string nombre = readString(); 
                return new Unirse(nombre);
            }
            break;
        case JUGAR: {
                recv(this->sfd, &hexa, 1, MSG_NOSIGNAL);
                uint8_t x = hexa >> 4;
                uint8_t y = hexa & 0x0F;
                return new Jugar(x, y);
            }
            break;
    }
}