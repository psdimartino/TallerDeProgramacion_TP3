#ifndef SERVER_SRC_JUGADOR_H_
#define SERVER_SRC_JUGADOR_H_

#include <map>
#include <string>
#include "../common_src/TaTeTi.h"
#include "../server_src/Thread.h"
#include "../common_src/Socket.h"
#include "../common_src/MapaDePartidas.h"


class Jugador : public Thread {
 private:
    Socket socket;
    char jugador = VACIO;
    std::string nombrePartida;
    MapaDePartidas &partidas;
    bool estaEnUnaPartida() const;

 public:
    Jugador(MapaDePartidas &partidas, Socket &socket);
    Jugador& operator=(const Jugador&) = delete;
    Jugador& operator=(Jugador&& other);
    Jugador(Jugador&& other);

    void run() override;
    void stop() override;
};

#endif  // SERVER_SRC_JUGADOR_H_
