#ifndef SERVER_SAFEMAP_H_
#define SERVER_SAFEMAP_H_

#include <map>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "common_TaTeTi.h"

class MapaDePartidas {
 private:
    std::map<std::string, TaTeTi> &tatetis;
    // std::condition_variable cv;
    std::mutex mCrear;
    std::mutex mUnirse;

 public:
    bool crear(std::string nombre);
    bool unirse(std::string nombre);
    void jugar(std::string nombre, int i, int j);
    MapaDePartidas();
    MapaDePartidas& operator=(const MapaDePartidas&) = delete;
    MapaDePartidas& operator=(MapaDePartidas&& other);
    MapaDePartidas(MapaDePartidas&& other);
};

#endif  // SERVER_SAFEMAP_H_
