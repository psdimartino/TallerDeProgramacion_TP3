#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

#include "../server_src/Server.h"

int main(int argc, char *argv[]) {
    try {
        Server server(argv[1]);
        server.jugar();
    } catch (std::runtime_error &e) {
        std::cerr << e.what();
    }
    return 0;
}
