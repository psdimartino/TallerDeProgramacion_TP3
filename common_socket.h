#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#include <sys/types.h>
#include <netdb.h>
#include <iostream>

class Socket {
   int sfd;
   struct addrinfo hints;
   struct sockaddr peer_addr;

 private:
    int obtenerGanadorColumnas() const;
    int obtenerGanadorFilas() const;
    int obtenerGanadorDiagonales() const;

 public:
    void connect(const char *service, const char *port );
    void bind(const char *port);
    void accept();
    void listen();
    Socket();
    ~Socket();
    void send(const char *data, uint16_t l);
    uint16_t read(char *data);

   //  friend std::ostream& operator<<(std::ostream &os, const Socket &other);
   //  Socket& operator<<(const Socket&) = delete;
   //  Socket& operator=(Socket&& other);
   //  Socket(Socket&& other);
};

#endif  // COMMON_SOCKET_H_
