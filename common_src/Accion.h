#ifndef COMMON_SRC_ACCION_H_
#define COMMON_SRC_ACCION_H_

#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include "../common_src/TaTeTi.h"
#include "../common_src/MapaDePartidas.h"

class IAccion {
    protected:
     std::stringstream result;
    public:
     virtual ~IAccion() {}
     virtual void ejecutar(MapaDePartidas &partidas,
                            std::string &nombrePartida, char &jugador) = 0;
     std::string const getResult() const;
};

#endif  // COMMON_SRC_ACCION_H_
