#ifndef COMMON_SRC_JUGAR_H_
#define COMMON_SRC_JUGAR_H_

#include <string>

#include "../common_src/Accion.h"

class Jugar: public IAccion {
    private:
    int x, y;

    public:
     Jugar(int const &x, int const &y);
     uint8_t getX() const;
     uint8_t getY() const;
     void ejecutar(MapaDePartidas &partidas,
                        std::string &nombrePartida, char &jugador) override;
};

#endif  // COMMON_SRC_JUGAR_H_
