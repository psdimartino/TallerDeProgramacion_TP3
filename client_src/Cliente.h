#ifndef CLIENTE_SRC_CLIENTE_H_
#define CLIENTE_SRC_CLIENTE_H_

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <limits>

#include "../common_src/Socket.h"
#include "../common_src/Accion.h"
#include "../common_src/Listar.h"
#include "../common_src/Crear.h"
#include "../common_src/Jugar.h"
#include "../common_src/Unirse.h"
#include "../common_src/TaTeTi.h"
#include "../common_src/OSError.h"

class Cliente {
 private:
    Socket socket;

 public:
    void jugar();
    Cliente(const char *port, const char *service);
    Cliente& operator=(const Cliente&) = delete;
    Cliente& operator=(Cliente&& other);
    Cliente(Cliente&& other);
};

#endif  // CLIENTE_SRC_CLIENTE_H_
