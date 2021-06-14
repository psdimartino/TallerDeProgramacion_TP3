#ifndef COMMON_SRC_SOCKET_H_
#define COMMON_SRC_SOCKET_H_

#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <string>

#include "../common_src/Accion.h"

#define LISTAR 0x6C
#define CREAR 0x6E
#define UNIRSE 0x6A
#define JUGAR 0x70

class Socket {
 private:
    int sfd;
    explicit Socket(int sfd);
    void send(const char &hexa);
    void read(char &hexa);
    void connect(const char *service, const char *port, addrinfo &hints);
    void bind(const char *port, addrinfo &hints);
    void listen();

 public:
    explicit Socket(const char *port);
    Socket(const char *port, const char *service);
    Socket accept();
    ~Socket();
    void send(Listar const &listar);
    void send(Crear const &crear);
    void send(Unirse const &unirse);
    void send(Jugar const &jugar);
    void send(std::string const &msg);
    std::string readString();
    IAccion *read();
    std::istream& operator>>(std::istream& is);
    std::ostream& operator<<(std::ostream& is);
    bool isUp() const;

    Socket& operator=(const Socket&) = delete;
   //  friend std::ostream& operator<<(std::ostream &os, const Socket &other);
    Socket& operator=(Socket&& other);
    Socket(Socket&& other);
};

#endif  // COMMON_SRC_SOCKET_H_
