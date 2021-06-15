#include <utility>
#include <string>
#include <memory>

#include "../common_src/Socket.h"
#include "../common_src/OSError.h"
#include "../server_src/Jugador.h"

Jugador::Jugador(MapaDePartidas &partidas, Socket &socket)
    : socket(std::move(socket)), partidas(partidas) {}

Jugador& Jugador::operator=(Jugador&& other) {
    if (this != &other) {
        this->jugador = other.jugador;
        this->nombrePartida = std::move(other.nombrePartida);
        this->socket = std::move(other.socket);
    }
    return *this;
}

Jugador::Jugador(Jugador&& other) :
    socket(std::move(other.socket)), partidas(other.partidas) {
    this->jugador = other.jugador;
    this->nombrePartida = std::move(other.nombrePartida);
    this->socket = std::move(other.socket);
}

bool Jugador::estaEnUnaPartida() const {
    return !nombrePartida.empty();
}

void Jugador::run() {
    is_running = true;
    while (!estaEnUnaPartida() || !partidas[nombrePartida].estaTerminada()) {
        try {
            std::unique_ptr<IAccion> accion(socket.read());
            accion->ejecutar(partidas, nombrePartida, jugador);
            socket.send(accion->getResult());
        } catch (OSError &e) {
            std::cerr << e.what();
            break;
        }
    }
    is_running = false;
}

void Jugador::stop() {
    if (!estaEnUnaPartida() || !partidas[nombrePartida].estaLlena()) {
        socket.close();
    }
}
