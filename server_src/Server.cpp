#include <stdlib.h>
#include <string.h>

#include "../common_src/Socket.h"
#include "../server_src/Aceptador.h"

int main(int argc, char *argv[]) {
    Socket socket(argv[1]);
    Thread *t = new Aceptador(socket);
    std::cerr << "New aceptador" << std::endl;
    t->start();
    std::cerr << "Running thread aceptador" << std::endl;
    char c = 'a';
    while (c != 'q') {
        std::cin >> c;
    }
    // t.stop();

    // for (int ronda = 0; ronda < 9 ; ronda++) {
    //     int ganador, i = 0, j = 0, turno = ronda % 2 + 1;
    //     std::cout << "Ronda " << ronda << " juega " << turno << std::endl;
    //     do {
    //         std::cout << "Ingrese las coordenadas: ";
    //         std::cin >> i >> j;
    //         i--; j--;
    //     } while (!tateti.sePuedeJugar(i, j));
    //     tateti.jugar(turno, i , j);
    //     std::cout << tateti << std::endl;
    //     if ((ganador = tateti.obtenerGanador()) != 0) {
    //         std::cout << "Ganó el jugador " << ganador << "!" << std::endl;
    //         break;
    //     }
    //     if ( !tateti.quedanEspaciosLibres() ) {
    //         std::cout << "Empataron" << std::endl;
    //         break;
    //     }
    // }

    // Socket socket;
    // socket.bind(argv[1]);
    // socket.listen();
    // socket.accept();
    // while (1) {
    //     IAccion* accion = socket.read();
    //     socket.send(accion->excecute(tateti));
    //     delete accion;
    // }
    return 0;
}
