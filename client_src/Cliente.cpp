#include "../client_src/Cliente.h"

void Cliente::jugar() {
    std::string str;
    while (str.length() <= 128) {
        std::cin >> str;
        try {
            if (!str.compare("listar")) {
                socket.send(Listar());
            } else if (!str.compare("crear")) {
                std::cin >> std::ws;
                std::getline(std::cin, str);
                socket.send(Crear(str));
            } else if (!str.compare("unirse")) {
                std::cin >> std::ws;
                std::getline(std::cin, str);
                socket.send(Unirse(str));
            } else if (!str.compare("jugar")) {
                int i, j;
                std::cin >> i >> j;
                socket.send(Jugar(--i, --j));
            } else {
                std::cout << "No existe la accion." << std::endl;
                continue;
            }
            str = socket.readString();
        } catch (OSError &e) {
            std::cerr << e.what();
            break;
        }
        std::cout << str;
    }
}

Cliente::Cliente(const char *port, const char *service)
    : socket(Socket(port, service)) {}

Cliente& Cliente::operator=(Cliente&& other) {
    if (this != &other) {
        socket = std::move(other.socket);
    }
    return *this;
}

Cliente::Cliente(Cliente&& other)
: socket(std::move(other.socket)) {}
