#ifndef COMMON_SRC_UNIRSE_H_
#define COMMON_SRC_UNIRSE_H_

#include <string>

#include "../common_src/Accion.h"

class Unirse: public IAccion {
    private:
     std::string nombre;

    public:
     explicit Unirse(std::string nombre);
     std::string const &getNombre() const;
     void ejecutar(MapaDePartidas &partidas,
                        std::string &nombrePartida, char &jugador) override;
};

#endif  // COMMON_SRC_UNIRSE_H_
