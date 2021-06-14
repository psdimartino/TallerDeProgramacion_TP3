#ifndef SERVER_SRC_ACEPTADOR_H_
#define SERVER_SRC_ACEPTADOR_H_

#include <map>
#include <string>
#include <atomic>
#include "../common_src/TaTeTi.h"
#include "../server_src/Thread.h"
#include "../common_src/Socket.h"


class Aceptador : public Thread {
 private:
    Socket socket;
    std::atomic<bool> seguir_aceptando;
    std::map<std::string, TaTeTi> tatetis;

 public:
    explicit Aceptador(Socket &socket);
    Aceptador& operator=(const Aceptador&) = delete;
    Aceptador& operator=(Aceptador&& other);
    Aceptador(Aceptador&& other);
    void stop();
    void run() override;
};

#endif  // SERVER_SRC_ACEPTADOR_H_
