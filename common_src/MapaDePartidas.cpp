#include <utility>

#include "../common_src/MapaDePartidas.h"
#include "../common_src/TaTeTi.h"

bool MapaDePartidas::crear(std::string const &nombre) {
    std::unique_lock<std::mutex> lg(m);
    if (tatetis.count(nombre) != 0) {
        return false;
    }
    tatetis.emplace(std::piecewise_construct,
          std::forward_as_tuple(nombre),
          std::forward_as_tuple());
    return true;
}

bool MapaDePartidas::unirse(std::string const &nombre) {
    std::unique_lock<std::mutex> lg(m);
    if (tatetis.count(nombre) == 0) {
        return false;
    }
    if (tatetis[nombre].estaLlena()) {
        return false;
    }
    tatetis[nombre].unirse();
    return true;
}

bool MapaDePartidas::jugar(std::string const &nombre,
                                char jugador, int x, int y) {
    if (!tatetis[nombre].sePuedeJugar(x, y)) {
        return false;
    }
    tatetis[nombre].jugar(jugador, x, y);
    return true;
}

TaTeTi& MapaDePartidas::operator[](std::string const &nombre) {
    return tatetis[nombre];
}

MapaDePartidas::MapaDePartidas() {}

MapaDePartidas& MapaDePartidas::operator=(MapaDePartidas&& other) {
    if (this != &other) {
        this->tatetis = std::move(other.tatetis);
    }
    return *this;
}

MapaDePartidas::MapaDePartidas(MapaDePartidas&& other)
    : tatetis(std::move(other.tatetis)) {}

std::ostream& operator<<(std::ostream &os, const MapaDePartidas &m) {
    os << "Partidas:\n";
    for (auto const &pair : m.tatetis) {
        os << " - " <<  pair.first << std::endl;
    }
    return os;
}
