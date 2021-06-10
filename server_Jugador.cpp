#include "server_Jugador.h"

Jugador::Jugador(std::map<std::string, TaTeTi> &tatetis, Socket &socket)
    : tatetis(tatetis), socket(socket) {}

Jugador& Jugador::operator=(Jugador&& other) {
    if (this != &other) {
        this->jugador = other.jugador;
        this->nombrePartida = std::move(other.nombrePartida);
        this->tatetis = std::move(other.tatetis);
    }
    return *this;
}

TaTeTi& Jugador::partida() {
    return tatetis[nombrePartida];
}

Jugador::Jugador(Jugador&& other) : tatetis(other.tatetis) {
    this->jugador = other.jugador;
    this->nombrePartida = std::move(other.nombrePartida);
}

bool Jugador::estaEnUnaPartida() const {
    return !nombrePartida.empty();
}

void Jugador::run() {
    while (estaEnUnaPartida() && !partida.estaTerminada()) {
        IAccion* accion = socket.read();
        socket.send(accion->excecute(tatetis, partida(), jugador));
        delete accion;
    }
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