#ifndef COMMON_ACCION_H_
#define COMMON_ACCION_H_

#include <iostream>
#include <sstream>
#include <string>
#include <map>

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
     void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;
};

class Crear: public IAccion {
    private:
     std::string nombre;

    public:
     explicit Crear(std::string nombre);
     std::string const &getNombre() const;
     void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;
};

class Unirse: public IAccion {
    private:
     std::string nombre;

    public:
     explicit Unirse(std::string nombre);
     std::string const &getNombre() const;
     void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;

};

class Jugar: public IAccion {
    private:
    int x, y;

    public:
     Jugar(int const &x, int const &y);
     uint8_t getX() const;
     uint8_t getY() const;
     void excecute(std::map<std::string, TaTeTi> &tatetis, std::string &nombrePartida, char &jugador) override;
};

#endif  // COMMON_ACCION_H_
