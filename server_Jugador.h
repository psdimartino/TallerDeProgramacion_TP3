#ifndef SERVER_JUGADOR_H_
#define SERVER_JUGADOR_H_

#include <map>
#include "server_TaTeTi.h"
#include "server_Thread.h"
#include "common_socket.h"


class Jugador : public Thread {
 private:
    Socket socket;
    int jugador;
    std::string nombrePartida;
    std::map<std::string, TaTeTi> &tatetis;
    TaTeTi& partida();
    bool estaEnUnaPartida() const;

 public:
    Jugador(std::map<std::string, TaTeTi> &tatetis, Socket &socket);
    Jugador& operator=(const Jugador&) = delete;
    Jugador& operator=(Jugador&& other);
    Jugador(Jugador&& other);

    virtual void run();
};

#endif  // SERVER_JUGADOR_H_
