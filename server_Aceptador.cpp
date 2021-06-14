#include <vector>
#include <utility>

#include "server_Aceptador.h"
#include "server_Jugador.h"
#include "server_Thread.h"

Aceptador::Aceptador(Socket &socket)
    : socket(std::move(socket)), seguir_aceptando(true) {}

Aceptador& Aceptador::operator=(Aceptador&& other) {
    if (this != &other) {
        this->tatetis = std::move(other.tatetis);
        this->socket = std::move(other.socket);
    }
    return *this;
}

Aceptador::Aceptador(Aceptador&& other) : socket(std::move(other.socket)) {
    this->tatetis = std::move(other.tatetis);
}

// void Aceptador::stop() {
//     seguir_aceptando = false;
// }

void Aceptador::run() {
    is_running = true;
    std::cerr << "Running aceptador..." << std::endl;
    std::vector<Thread*> jugadores;
    while (seguir_aceptando) {
        std::cerr << "Waiting for a new player..." << std::endl;
        Socket peer = socket.accept();
        std::cerr << "Accepted a new peer" << std::endl;
        Thread *t = new Jugador(tatetis, peer);
        std::cerr << "new jugador" << std::endl;
        t->start();
        std::cerr << "t->run" << std::endl;
        jugadores.push_back(t);
        std::cerr << "push_back" << std::endl;
        // for (Thread* jugador : jugadores) {
        //     std::cerr << "jugador" << std::endl;
        //     if (jugador->isDead()) {
        //         std::cerr << "Jugador stopped playing" << std::endl;
        //         jugador->join();
        //         std::cerr << "joined player" << std::endl;
        //         delete jugador;
        //     }
        // }
    }
    for (Thread* jugador : jugadores) {
        if (jugador->isDead()) {
            std::cerr << "Jugador stopped playing" << std::endl;
            jugador->join();
            delete jugador;
        }
    }
    is_running = false;
    std::cerr << "Ending aceptador..." << std::endl;
}
