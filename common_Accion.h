#ifndef SERVER_ACCION_H_
#define SERVER_ACCION_H_

#include <iostream>
#include <map>
#include <sstream> 

#include "server_TaTeTi.h"

class IAccion {
    protected:
     std::stringstream result;
    public:
     virtual ~IAccion() {}
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador) = 0;
    //  friend std::ostream& operator<<(std::string &os, const IAccion &other);
     std::string const& getResult() const;
};

class Listar: public IAccion {
    public:
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador);
};

class Crear: public IAccion {
    private:
     std::string nombre;

    public:
     Crear(std::string nombre);
     std::string const &getNombre() const;
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador);
};

class Unirse: public IAccion {
    private:
     std::string nombre;
    
    public:
     Unirse(std::string nombre);
     std::string const &getNombre() const;
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador);

};

class Jugar: public IAccion {
    private:
    int x, y;
    
    public:
     Jugar(int &x, int &y);
     uint8_t getX() const;
     uint8_t getY() const;
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, int &jugador);
};

#endif  // SERVER_ACCION_H_
