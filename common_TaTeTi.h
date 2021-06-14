#ifndef SERVER_TATETI_H_
#define SERVER_TATETI_H_

#include <iostream>
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
    int jugadas = 0;
    int obtenerGanadorColumnas() const;
    int obtenerGanadorFilas() const;
    int obtenerGanadorDiagonales() const;
    std::condition_variable cv;
    std::mutex m;

 public:
    TaTeTi();
    friend std::ostream& operator<<(std::ostream &os, const TaTeTi &t);
    TaTeTi& operator=(const TaTeTi&) = delete;
    TaTeTi& operator=(TaTeTi&& other);
    TaTeTi(TaTeTi&& other);

    void jugar(char const &jugador, int const &i, int const &j);
    bool sePuedeJugar(int const &i, int const &j) const;
    bool quedanEspaciosLibres() const;
    char obtenerGanador() const;
    bool estaTerminada() const;
    bool esElTurnoDe(char jugador) const;
    void esperarElTurnoDe(char const &jugador);
};

#endif  // SERVER_TATETI_H_
