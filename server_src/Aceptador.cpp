#include <vector>
#include <utility>

#include "../server_src/Aceptador.h"
#include "../server_src/Jugador.h"
#include "../common_src/OSError.h"
#include "../server_src/Thread.h"


Aceptador::Aceptador(Socket &socket)
    : socket(std::move(socket)), seguir_aceptando(true) {}

Aceptador& Aceptador::operator=(Aceptador&& other) {
    if (this != &other) {
        this->partidas = std::move(other.partidas);
        this->socket = std::move(other.socket);
    }
    return *this;
}

Aceptador::Aceptador(Aceptador&& other) : socket(std::move(other.socket)) {
    this->partidas = std::move(other.partidas);
}

void Aceptador::run() {
    is_running = true;
    std::vector<std::unique_ptr<Thread>> jugadores;
    while (seguir_aceptando) {
        try {
            Socket peer = socket.accept();
            std::unique_ptr<Thread> t(new Jugador(partidas, peer));
            t->start();
            jugadores.push_back(std::move(t));
        } catch (OSError& e) {
            if (!seguir_aceptando) break;
            e.what();
        }
    }
    for (std::unique_ptr<Thread> &jugador : jugadores) {
        jugador->stop();
        jugador->join();
    }
    is_running = false;
}

void Aceptador::stop() {
    seguir_aceptando = false;
    socket.close();
}
