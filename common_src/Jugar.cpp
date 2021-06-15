#include "../common_src/Jugar.h"

Jugar::Jugar(int const &x, int const &y) : x(x), y(y) {}

uint8_t Jugar::getX() const {
    return x;
}

uint8_t Jugar::getY() const {
    return y;
}

void Jugar::ejecutar(MapaDePartidas &partidas,
                            std::string &nombrePartida, char &jugador) {
    if (!partidas.jugar(nombrePartida, jugador, x, y)) {
        result << "La posicion no es valida" << std::endl;
        return;
    }
    partidas[nombrePartida].esperarElTurnoDe(jugador);
    result << partidas[nombrePartida];
    if (partidas[nombrePartida].estaTerminada()) {
        char ganador = partidas[nombrePartida].obtenerGanador();
        if (ganador == VACIO) {
            result << "La partida ha terminado en empate" << std::endl;
        } else if (ganador == jugador) {
            result << "Felicitaciones! Ganaste!" << std::endl;
        } else {
            result << "Has perdido. Segui intentando!" << std::endl;
        }
    }
}
