#ifndef COMMON_SRC_CREAR_H_
#define COMMON_SRC_CREAR_H_

#include <string>

#include "../common_src/Accion.h"

class Crear: public IAccion {
    private:
     std::string nombre;

    public:
     explicit Crear(std::string nombre);
     std::string const &getNombre() const;
     void ejecutar(MapaDePartidas &partidas,
                    std::string &nombrePartida, char &jugador) override;
};

#endif  // COMMON_SRC_CREAR_H_
