#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#include <sys/types.h>
#include <netdb.h>
#include <iostream>

#include "Action.cpp"

#define LISTAR 0x6C
#define CREAR 0x6E
#define UNIRSE 0x6A
#define JUGAR 0x70

class Socket {
 private:
    int sfd;
    struct addrinfo hints;
    struct sockaddr peer_addr;
    void sendHexa(const char hexa) const;

 public:
    void connect(const char *service, const char *port );
    void bind(const char *port);
    void accept();
    void listen();
    Socket();
    ~Socket();
    void send(const char *data, uint16_t l);
    uint16_t read(char *data);
    void send(Listar const &listar);
    void send(Crear const &crear);
    void send(Unirse const &unirse);
    void send(Jugar const &jugar);
    void send(std::string const &msg);
    std::string readString();
    IAccion *read();

   //  friend std::ostream& operator<<(std::ostream &os, const Socket &other);
   //  Socket& operator<<(const Socket&) = delete;
   //  Socket& operator=(Socket&& other);
   //  Socket(Socket&& other);
};

#endif  // COMMON_SOCKET_H_
