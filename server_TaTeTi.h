#ifndef SERVER_TATETI_H_
#define SERVER_TATETI_H_

#include <iostream>

enum estado { VACIO, CIRUCLO, CRUZ };

class TaTeTi {
 private:
    estado tablero[3][3] = { VACIO };
    int obtenerGanadorColumnas() const;
    int obtenerGanadorFilas() const;
    int obtenerGanadorDiagonales() const;

 public:
    TaTeTi();
    friend std::ostream& operator<<(std::ostream &os, const TaTeTi &other);
    TaTeTi& operator=(const TaTeTi&) = delete;
    TaTeTi& operator=(TaTeTi&& other);
    TaTeTi(TaTeTi&& other);

    void jugar(int &jugador, int &i, int &j);
    bool sePuedeJugar(int &i, int &j) const;
    bool quedanEspaciosLibres() const;
    int obtenerGanador() const;
};

#endif  // SERVER_TATETI_H_
