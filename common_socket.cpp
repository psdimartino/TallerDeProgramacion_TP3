#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "common_socket.h"

Socket::Socket() {
    this->hints.ai_family = AF_INET;
    this->hints.ai_socktype = SOCK_STREAM;
}

void Socket::connect(const char *service, const char *port ) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(port, service, &this->hints, &result)) != 0) {
        // error_exit_msg("Error in getaddrinfo");
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
    // error_exit_msg("Error while trying to connect");
}

void Socket::bind(const char *port ) {
    struct addrinfo *result, *it;
    if ((getaddrinfo(NULL, port, &this->hints, &result)) != 0) {
        // error_exit_msg("Error in getaddrinfo");
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
    // error_exit_msg("Error while trying to bind");
}

void Socket::accept() {
    struct sockaddr peer_addr;
    socklen_t peer_addr_len = sizeof(peer_addr);
    int cfd;
    if ( (cfd = ::accept(this->sfd, &peer_addr, &peer_addr_len)) == -1 ) {
        // error_exit_msg("Error while trying to accept the connection");
    }
    close(this->sfd);
    this->sfd = cfd;
}

void Socket::listen() {
    if ( ::listen(this->sfd, 10) == -1 ) {
        // error_exit_msg("Error while trying to listen");
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
