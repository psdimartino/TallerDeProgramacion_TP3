#ifndef SERVER_SAFEMAP_H_
#define SERVER_SAFEMAP_H_

#include <condition_variable>
#include <iostream>
#include <string>
#include <mutex>
#include <map>

#include "../common_src/TaTeTi.h"

class MapaDePartidas {
 private:
    std::map<std::string, TaTeTi> tatetis;
    std::mutex m;

 public:
    bool crear(std::string const &nombre);
    bool unirse(std::string const &nombre);
    bool jugar(std::string const &nombre, char jugador, int i, int j);
    MapaDePartidas();
    MapaDePartidas& operator=(const MapaDePartidas&) = delete;
    MapaDePartidas& operator=(MapaDePartidas&& other);
    MapaDePartidas(MapaDePartidas&& other);
    TaTeTi& operator[](std::string const &nombre);
    friend std::ostream& operator<<(std::ostream &os, const MapaDePartidas &m);
};

#endif  // SERVER_SAFEMAP_H_
