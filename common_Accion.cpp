#include "common_Accion.h"

Crear::Crear(std::string const nombre) : nombre(nombre) {}

Unirse::Unirse(std::string const nombre) : nombre(nombre) {}

Jugar::Jugar(int const &x, int const &y) : x(x), y(y) {}

void Listar::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) {
    result << "Partidas:\n";
    for (auto const &pair: tatetis) {
        result << " - " + pair.first + "\n";
    }
}

void Crear::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) {
    if (tatetis.count(nombre) != 0) {
        result << "La partida ya existe";
        return;
    }
    tatetis.emplace(nombre, TaTeTi());
    jugador = 'O';
    result << tatetis[nombre];
    nombrePartida = std::move(nombre);
}

void Unirse::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) {
    if (tatetis.count(nombre) == 0) {
        result << "La partida no existe" << std::endl;
        return;
    }
    jugador = 'X';
    nombrePartida = std::move(nombre);
    tatetis[nombrePartida].esperarElTurnoDe(jugador);
    result << tatetis[nombre];
}

void Jugar::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) {
    if (!tatetis[nombrePartida].sePuedeJugar(x, y)) {
        result << "La posicion no es valida" << std::endl;
        return;
    }
    tatetis[nombrePartida].jugar(jugador, x, y);
    tatetis[nombrePartida].esperarElTurnoDe(jugador);
    result << tatetis[nombrePartida];
    if (tatetis[nombrePartida].estaTerminada()) {
        char ganador = tatetis[nombrePartida].obtenerGanador();
        if (ganador == 0) {
            result << "La partida ha terminado en empate!" << std::endl;
        } else if (ganador == jugador) {
            result << "Felicitaciones! Ganaste!" << std::endl;
        } else {
            result << "Has perdido. Segui intentando!" << std::endl;
        };
    }
}

std::string const IAccion::getResult() const {
    return result.str();
}

std::string const& Crear::getNombre() const {
    return nombre;
}

std::string const& Unirse::getNombre() const {
    return nombre;
}

uint8_t Jugar::getX() const {
    return x;
}

uint8_t Jugar::getY() const {
    return y;
}
