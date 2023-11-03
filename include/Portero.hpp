#pragma once
#include <Dibujo.hpp>
#include <Actualizable.hpp>
#include <Bocha.hpp>

class Portero : public Dibujo, public Actualizable
{

private: 

public:

    Portero() : Dibujo("Portero")
    {
    }
    Portero(int x, int y) : Dibujo(x, y, "Portero")
    {
    }
    void Actualizar()
    {
        // this->x +=1;
    }

    void DesplazarIzquierda()
    {
        this->x -= 1;
    }
    void DesplazarDerecha()
    {
        this->x += 1;
    }
    void DesplazarArriba()
    {
        this->y -= 1;
    }
    void DesplazarAbajo()
    {
        this->y += 1;
    }

    ~Portero() {}
};