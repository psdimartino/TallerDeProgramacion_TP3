#include <stdlib.h>
#include <string.h>
#include <exception>

#include "../common_src/Socket.h"
#include "../server_src/Aceptador.h"
#include "../common_src/OSError.h"
#include "../server_src/Server.h"

void Server::jugar() {
    Aceptador aceptador(socket);
    aceptador.start();
    char c = 'a';
    while (c != 'q') {
        std::cin >> c;
    }
    try {
        aceptador.stop();
        aceptador.join();
    } catch (OSError& e) {
        e.what();
    }
}

Server::Server(const char *port) : socket(Socket(port)) {}

Server& Server::operator=(Server&& other) {
    if (this != &other) {
        socket = std::move(other.socket);
    }
    return *this;
}

Server::Server(Server&& other)
: socket(std::move(other.socket)) {}
