#ifndef COMMON_SRC_LISTAR_H_
#define COMMON_SRC_LISTAR_H_

#include <string>

#include "../common_src/Accion.h"

class Listar: public IAccion {
    public:
     void ejecutar(MapaDePartidas &partidas,
                        std::string &nombrePartida, char &jugador) override;
};

#endif  // COMMON_SRC_LISTAR_H_
