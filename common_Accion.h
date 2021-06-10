#ifndef SERVER_ACCION_H_
#define SERVER_ACCION_H_

#include <iostream>
#include <map>

#include "server_TaTeTi.h"

class IAccion {
    public:
     virtual ~IAccion() {}
     virtual std::string excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador) = 0;
};

class Listar: public IAccion {
    public:
     virtual std::string excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador);
};

class Crear: public IAccion {
    private:
     std::string nombre;

    public:
     Crear(std::string nombre);
     std::string const &getNombre() const;
     virtual std::string excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador);
};

class Unirse: public IAccion {
    private:
     std::string nombre;
    
    public:
     Unirse(std::string nombre);
     std::string const &getNombre() const;
     virtual std::string excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador);

};

class Jugar: public IAccion {
    private:
    int x, y;
    
    public:
     Jugar(int &x, int &y);
     virtual std::string excecute(std::map<std::string, TaTeTi> &tatetis, TaTeTi &tateti, int &jugador);
     uint8_t getX() const;
     uint8_t getY() const;
};

#endif  // SERVER_ACCION_H_
