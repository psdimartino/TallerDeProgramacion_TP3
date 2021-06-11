#include "common_Accion.h"

void Listar::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador) {
    result << "Partidas:\n";
    for (auto const &pair: tatetis) {
        result << " - " + pair.first + "\n";
    }
}

void Crear::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador) {
    if (tatetis.count(nombre) != 0) {
        result << "La partida ya existe";
        return;
    }
    tatetis.emplace(nombre, TaTeTi());
    jugador = 1;
    nombrePartida = std::move(nombre);
    result << tatetis[nombre];
}

void Unirse::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador) {
    if (tatetis.count(nombre) == 0) {
        result << "La partida no existe";
        return;
    }
    jugador = 2;
    nombrePartida = std::move(nombre);
    result << tatetis[nombre];
    tatetis[nombrePartida].esperarElTurnoDe(jugador);
}

void Jugar::excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador) {
    if (!tatetis[nombrePartida].sePuedeJugar(x, y)) {
        result << "La posicion no es valida";
    }
    tatetis[nombrePartida].jugar(jugador, x, y);
    tatetis[nombrePartida].esperarElTurnoDe(jugador);
    result << tatetis[nombrePartida];
}

std::string const& IAccion::getResult() const {
    return std::move(result.str());
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
