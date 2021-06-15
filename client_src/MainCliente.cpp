#include <stdlib.h>

#include "../client_src/Cliente.h"

int main(int argc, char *argv[]) {
    try {
        Cliente cliente(argv[1], argv[2]);
        cliente.jugar();
    } catch (std::runtime_error &e) {
        std::cerr << e.what();
    }
    return 0;
}
