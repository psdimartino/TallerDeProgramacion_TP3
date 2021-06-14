#ifndef SERVER_ACEPTADOR_H_
#define SERVER_ACEPTADOR_H_

#include <map>
#include <string>
#include <atomic>
#include "common_TaTeTi.h"
#include "server_Thread.h"
#include "common_socket.h"


class Aceptador : public Thread {
 private:
    std::atomic<bool> seguir_aceptando;
    Socket socket;
    std::map<std::string, TaTeTi> tatetis;

 public:
    explicit Aceptador(Socket &socket);
    Aceptador& operator=(const Aceptador&) = delete;
    Aceptador& operator=(Aceptador&& other);
    Aceptador(Aceptador&& other);
    void stop();
    void run() override;
};

#endif  // SERVER_ACEPTADOR_H_
