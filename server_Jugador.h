#ifndef SERVER_JUGADOR_H_
#define SERVER_JUGADOR_H_

#include <map>
#include <string>
#include "common_TaTeTi.h"
#include "server_Thread.h"
#include "common_socket.h"


class Jugador : public Thread {
 private:
    Socket socket;
    char jugador = VACIO;
    std::string nombrePartida;
    std::map<std::string, TaTeTi> &tatetis;

    TaTeTi& partida();
    bool estaEnUnaPartida() const;

 public:
    Jugador(std::map<std::string, TaTeTi> &tatetis, Socket &socket);
    Jugador& operator=(const Jugador&) = delete;
    Jugador& operator=(Jugador&& other);
    Jugador(Jugador&& other);

    void run() override;
};

#endif  // SERVER_JUGADOR_H_
