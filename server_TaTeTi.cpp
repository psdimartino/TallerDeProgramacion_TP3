#include "server_TaTeTi.h"

TaTeTi::TaTeTi() {}

std::ostream& operator<<(std::ostream &os, const TaTeTi &t) {
    std::cout << "Quedan espacios libres: " << t.quedanEspaciosLibres() << std::endl;
    std::cout << "Ganador: " << t.obtenerGanador() << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << "  " << t.tablero[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    return os;
}

TaTeTi& TaTeTi::operator=(TaTeTi&& other) {
    return *this;
}

TaTeTi::TaTeTi(TaTeTi&& other) {
    //  memcpy del tablero
}

bool TaTeTi::sePuedeJugar(int &i, int &j) const {
    return tablero[i][j] == VACIO && i < 3  && j < 3;
}

void TaTeTi::jugar(int &jugador, int &i, int &j) {
    if (!sePuedeJugar(i, j)) {
        // throw jugadores, i, j
        std::cerr << "No se puede jugar en " << i << " " << j << std::endl;
        return;
    }
    tablero[i][j] = static_cast<estado>(jugador);
}


bool TaTeTi::quedanEspaciosLibres() const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tablero[i][j] == VACIO) {
                return true;
            }
        }
    }
    return false;
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


int TaTeTi::obtenerGanador() const {  // 0 es sin ganador
    int aux;
    if ((aux = obtenerGanadorDiagonales()) != 0) {
        std::cerr << "Gano por diagonales " << std::endl;
        return aux;
    }
    if ((aux = obtenerGanadorFilas()) != 0) {
        std::cerr << "Gano por filas " << std::endl;
        return aux;
    }
    if ((aux = obtenerGanadorColumnas()) != 0) {
        std::cerr << "Gano por columnas " << std::endl;
        return aux;
    }
    return 0;
}

