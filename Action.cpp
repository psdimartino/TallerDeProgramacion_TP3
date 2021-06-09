#include <iostream>

class IAccion {
    public:
        virtual ~IAccion() {}
        virtual void excecute() = 0;
};

class Listar: public IAccion {
    public:
    virtual void excecute() {
        std::cerr << "Listar excecute" << std::endl;
    }
};

class Crear: public IAccion {
    private:
    std::string nombre;

    public:
    Crear(std::string nombre) : nombre(nombre) {}
    
    virtual void excecute() {
        std::cerr << "Crear excecute: " << nombre << std::endl;
    }

    std::string const &getNombre() const {
        return nombre;
    }
};

class Unirse: public IAccion {
    private:
    std::string nombre;
    
    public:
    Unirse(std::string nombre) : nombre(nombre) {}
    virtual void excecute() {
        std::cerr << "Unirse excecute: " << nombre << std::endl;
    }

    std::string const &getNombre() const {
        return nombre;
    }
};

class Jugar: public IAccion {
    private:
    uint8_t x, y;
    
    public:
    Jugar(uint8_t &x, uint8_t &y) :x(x), y(y) {}

    virtual void excecute() {
        std::cerr << "Jugar excecute: " << x << y << std::endl;
    }

    uint8_t getX() const {
        return x;
    }

    uint8_t getY() const {
        return y;
    }
};