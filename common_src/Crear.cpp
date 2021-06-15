#include "../common_src/Crear.h"

Crear::Crear(std::string const nombre) : nombre(nombre) {}

std::string const& Crear::getNombre() const {
    return nombre;
}

void Crear::ejecutar(MapaDePartidas &partidas,
                            std::string &nombrePartida, char &jugador) {
    if (!partidas.crear(nombre)) {
        result << "La partida ya existe";
        return;
    }
    jugador = CIRCULO;
    result << partidas[nombre];
    nombrePartida = std::move(nombre);
}
