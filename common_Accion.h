#ifndef SERVER_ACCION_H_
#define SERVER_ACCION_H_

#include <iostream>
#include <map>
#include <sstream> 

#include "common_TaTeTi.h"

class IAccion {
    protected:
     std::stringstream result;
    public:
     virtual ~IAccion() {}
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) = 0;
     std::string const getResult() const;
};

class Listar: public IAccion {
    public:
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;
};

class Crear: public IAccion {
    private:
     std::string nombre;

    public:
     explicit Crear(std::string nombre);
     std::string const &getNombre() const;
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;
};

class Unirse: public IAccion {
    private:
     std::string nombre;
    
    public:
     explicit Unirse(std::string nombre);
     std::string const &getNombre() const;
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;

};

class Jugar: public IAccion {
    private:
    int x, y;
    
    public:
     Jugar(int const &x, int const &y);
     uint8_t getX() const;
     uint8_t getY() const;
     virtual void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;
};

#endif  // SERVER_ACCION_H_
