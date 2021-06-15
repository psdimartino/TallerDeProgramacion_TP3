#include <string.h>
#include <stdexcept>
#include "../common_src/TaTeTi.h"
TaTeTi::TaTeTi() {}

std::ostream& operator<<(std::ostream &os, const TaTeTi &t) {
    os << "    1 . 2 . 3 .\n";
    os << "  +---+---+---+\n";
    for (int i = 0; i < 3; i++) {
        os << i + 1 << " |";
        for (int j = 0; j < 3; j++) {
            os << " " << t.tablero[j][i]  << " |";
        }
        os << "\n  +---+---+---+\n";
    }
    return os;
}

TaTeTi& TaTeTi::operator=(TaTeTi&& other) {
    if (this != &other) {
        memmove(this->tablero, other.tablero, 9);
    }
    return *this;
}

TaTeTi::TaTeTi(TaTeTi&& other) {
    memmove(this->tablero, other.tablero, 9);
}

bool TaTeTi::sePuedeJugar(int const &i, int const &j) const {
    return i < 3  && j < 3 && tablero[i][j] == VACIO;
}

bool TaTeTi::estaTerminada() const {
    return (obtenerGanador() != VACIO) || !quedanEspaciosLibres();
}

void TaTeTi::jugar(char const &jugador, int const &i, int const &j) {
    if (!sePuedeJugar(i, j)) {
        throw std::runtime_error("Posiciones no validas");
    }
    tablero[i][j] = jugador;
    jugadas++;
    cv.notify_one();
}


bool TaTeTi::quedanEspaciosLibres() const {
    return jugadas < 9;
}

int TaTeTi::obtenerGanadorColumnas() const {
    for (int i = 0; i < 3; ++i) {
        if (tablero[i][0] == VACIO) continue;
        if (tablero[i][1] != tablero[i][0]) continue;
        if (tablero[i][2] != tablero[i][0]) continue;
        return tablero[i][0];
    }
    return 0;
}

int TaTeTi::obtenerGanadorFilas() const {
    for (int i = 0; i < 3; ++i) {
        if (tablero[0][i] == VACIO) continue;
        if (tablero[1][i] != tablero[0][i]) continue;
        if (tablero[2][i] != tablero[0][i]) continue;
        return tablero[0][i];
    }
    return 0;
}

int TaTeTi::obtenerGanadorDiagonales() const {
    if (tablero[1][1] == VACIO) {  // El ganador necesita la celda central
        return 0;
    }
    if (tablero[0][0] == tablero[1][1] && tablero[2][2] == tablero[1][1]) {
        return tablero[1][1];
    }
    if (tablero[2][0] == tablero[1][1] && tablero[0][2] == tablero[1][1]) {
        return tablero[1][1];
    }

    return 0;
}


char TaTeTi::obtenerGanador() const {  // 0 es sin ganador
    char aux;
    if ((aux = obtenerGanadorDiagonales()) != 0) {
        return aux;
    }
    if ((aux = obtenerGanadorFilas()) != 0) {
        return aux;
    }
    if ((aux = obtenerGanadorColumnas()) != 0) {
        return aux;
    }
    return VACIO;
}

bool TaTeTi::esElTurnoDe(char jugador) const {
    return (jugadas % 2)? jugador == CRUZ : jugador == CIRCULO;
}

void TaTeTi::esperarElTurnoDe(char const &jugador) const {
    std::unique_lock<std::mutex> lg(m);
    while (!esElTurnoDe(jugador) && !estaTerminada()) {
        cv.wait(lg);
    }
}

bool TaTeTi::estaLlena() {
    return jugadores == 2;
}

void TaTeTi::unirse() {
    if (estaLlena()) {
        throw std::runtime_error("Se intentó unirse a una partida llena");
    }
    jugadores++;
}

