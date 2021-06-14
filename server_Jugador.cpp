#include <utility>
#include <string>

#include "common_socket.h"
#include "server_Jugador.h"

Jugador::Jugador(std::map<std::string, TaTeTi> &tatetis, Socket &socket)
    : socket(std::move(socket)), tatetis(tatetis) {}

Jugador& Jugador::operator=(Jugador&& other) {
    if (this != &other) {
        this->jugador = other.jugador;
        this->nombrePartida = std::move(other.nombrePartida);
        // this->tatetis = other.tatetis;
        this->socket = std::move(other.socket);
    }
    return *this;
}

TaTeTi& Jugador::partida() {
    return tatetis[nombrePartida];
}

Jugador::Jugador(Jugador&& other) : socket(std::move(other.socket)), tatetis(other.tatetis) {
    this->jugador = other.jugador;
    this->nombrePartida = std::move(other.nombrePartida);
    // this->tatetis = other.tatetis;
    this->socket = std::move(other.socket);
}

bool Jugador::estaEnUnaPartida() const {
    return !nombrePartida.empty();
}

void Jugador::run() {
    std::cerr << "Jugador is playing " << socket.isUp() << std::endl;
    is_running = true;
    while (!estaEnUnaPartida() || !partida().estaTerminada()) {
        IAccion* accion = socket.read();
        std::cout << "Accion leida " << std::endl;
        accion->excecute(tatetis, nombrePartida, jugador);
        socket.send(accion->getResult());
        delete accion;
    }
    std::cout << "fin run " << std::endl;
    is_running = false;
    // Enviar resultados de la partida
}

// for (int ronda = 0; ronda < 9 ; ronda++) {
    //     int ganador, i = 0, j = 0, turno = ronda % 2 + 1;
    //     std::cout << "Ronda " << ronda << " juega " << turno << std::endl;
    //     do {
    //         std::cout << "Ingrese las coordenadas: ";
    //         std::cin >> i >> j;
    //         i--; j--;
    //     } while (!tateti.sePuedeJugar(i, j));
    //     tateti.jugar(turno, i , j);
    //     std::cout << tateti << std::endl;
    //     if ((ganador = tateti.obtenerGanador()) != 0) {
    //         std::cout << "Ganó el jugador " << ganador << "!" << std::endl;
    //         break;
    //     }
    //     if ( !tateti.quedanEspaciosLibres() ) {
    //         std::cout << "Empataron" << std::endl;
    //         break;
    //     }
    // }
