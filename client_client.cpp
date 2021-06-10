#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "server_TaTeTi.h"
#include "common_socket.h"

#include "common_Accion.h"

int main(int argc, char *argv[]) {
    Socket socket;
    socket.connect(argv[1], argv[2]);
    std::string actionStr;
    while (std::cin >> actionStr) {
        if (!actionStr.compare("listar")) {
            socket.send(Listar());
        } else if (!actionStr.compare("crear")) {
            std::string name;
            std::cin >> name;
            socket.send(Crear(name));
        } else if (!actionStr.compare("unirse")) {
            std::string name;
            std::cin >> name;
            socket.send(Unirse(name));;
        } else if (!actionStr.compare("jugar")) {
            int i, j;
            std::cin >> i >> j;
            socket.send(Jugar(i, j));
        }
        // Imprimir respuesta. Si es el caso de crear, 
        // va a tener que esperar de todas formas, asi que sale.
    }
    return 0;
    // uint8_t hexa = 0x12;
    // int x = (hexa >> 4) & 0x0F;
    // int y = hexa & 0x0F;
    // std::cerr << "hexa<" << hexa << "> x<" << x << "> y<" << y << ">" << std::endl;
    // uint8_t res = 0, a = 1, b = 2;
    // res = b | (a << 4);
    // uint8_t expected = 0x12;
    // std::cout << (expected == res) << std::endl;
}
