#include <stdlib.h>
#include <string.h>

#include "server_TaTeTi.h"
#include "common_socket.h"

int main(int argc, char *argv[]) {
    Socket socket;
    socket.connect(argv[1], argv[2]);
    const char *msg = "Hola mundo";
    socket.send(msg, strlen(msg));
    return 0;
}
