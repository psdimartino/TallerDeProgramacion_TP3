#ifndef COMMON_SRC_TATETI_H_
#define COMMON_SRC_TATETI_H_

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>

#define VACIO ' '
#define CIRCULO 'O'
#define CRUZ 'X'

class TaTeTi {
 private:
    char tablero[3][3] = { {VACIO, VACIO, VACIO},
                           {VACIO, VACIO, VACIO},
                           {VACIO, VACIO, VACIO} };
    int jugadores = 1;
    int jugadas = 0;
    int obtenerGanadorColumnas() const;
    int obtenerGanadorFilas() const;
    int obtenerGanadorDiagonales() const;
    mutable std::condition_variable cv;
    mutable std::mutex m;

 public:
    TaTeTi();
    friend std::ostream& operator<<(std::ostream &os, const TaTeTi &t);
    TaTeTi& operator=(const TaTeTi&) = delete;
    TaTeTi& operator=(TaTeTi&& other);
    TaTeTi(TaTeTi&& other);

    void unirse();
    bool estaLlena();
    void jugar(char const &jugador, int const &i, int const &j);
    bool sePuedeJugar(int const &i, int const &j) const;
    bool quedanEspaciosLibres() const;
    char obtenerGanador() const;
    bool estaTerminada() const;
    bool esElTurnoDe(char jugador) const;
    void esperarElTurnoDe(char const &jugador) const;
};

#endif  // COMMON_SRC_TATETI_H_
