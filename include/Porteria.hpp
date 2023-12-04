#pragma once
#include <Dibujo.hpp>
#include <Actualizable.hpp>
#include <Jugador.hpp>
#include <SFML/Graphics.hpp>

class Porteria : public Dibujo, public Actualizable
{
private:

public:

    Porteria() : Dibujo("Porteria")
    {
    }
    Porteria(int x, int y) : Dibujo(x, y, "Porteria")
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

    ~Porteria() {}
};