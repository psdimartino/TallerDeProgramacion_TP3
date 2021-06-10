#include <iostream>
#include <map>

#include "common_Accion.h"

std::string Listar::excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador) {
    std::string result = "Partidas:";
    for (auto const &pair: tatetis) {
        result += " - " + pair.first + "\n";
    }
    return result;
}

std::string Crear::excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador) {
    std::string result << tateti;
    return << tateti;
}

std::string Unirse::excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador) {

}

std::string Jugar::excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador) {

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
