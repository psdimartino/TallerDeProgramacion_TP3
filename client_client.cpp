#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <limits>

#include "common_TaTeTi.h"
#include "common_socket.h"

#include "common_Accion.h"
#include "common_TaTeTi.h"

int main(int argc, char *argv[]) {
    Socket socket(argv[1], argv[2]);
    while (socket.isUp()) {
        std::string str;
        std::cin >> str;
        if (!str.compare("listar")) {
            socket.send(Listar());
        } else if (!str.compare("crear")) {
            std::getline(std::cin, str);
            socket.send(Crear(str));
        } else if (!str.compare("unirse")) {
            std::getline(std::cin, str);
            socket.send(Unirse(str));
        } else if (!str.compare("jugar")) {
            int i, j;
            std::cin >> i >> j;
            socket.send(Jugar(i, j));
        } else {
            std::cout << "No existe la accion." << std::endl;
            continue;
        }
        str = socket.readString();
        std::cout << str;
        if (str.length() > 127) break;
    }
    return 0;
}
