#include <string>

#include "../common_src/MapaDePartidas.h"
#include "../common_src/Accion.h"

std::string const IAccion::getResult() const {
    return std::move(result.str());
}
