#ifndef SERVER_SRC_SERVER_H_
#define SERVER_SRC_SERVER_H_

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

class Server {
 private:
    Socket socket;

 public:
    void jugar();
    explicit Server(const char *port);
    Server& operator=(const Server&) = delete;
    Server& operator=(Server&& other);
    Server(Server&& other);
};

#endif  // SERVER_SRC_SERVER_H_
