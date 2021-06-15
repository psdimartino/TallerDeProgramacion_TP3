#include "../common_src/Unirse.h"

Unirse::Unirse(std::string const nombre) : nombre(nombre) {}

std::string const& Unirse::getNombre() const {
    return nombre;
}

void Unirse::ejecutar(MapaDePartidas &partidas,
                            std::string &nombrePartida, char &jugador) {
    if (!partidas.unirse(nombre)) {
        result << "La partida no existe o esta llena" << std::endl;
        return;
    }
    jugador = CRUZ;
    nombrePartida = std::move(nombre);
    partidas[nombrePartida].esperarElTurnoDe(jugador);
    result << partidas[nombrePartida];
}
