#pragma once
#include<Dibujo.hpp>
#include<Actualizable.hpp>

class Bocha : public Dibujo,public Actualizable
{
private:
    int direccion;

public:
    Bocha(int x, int y) : Dibujo(x,y,"Bocha")
    {
        this->direccion=1;
    }
    ~Bocha() {}

    void CambiarDireccion()
    {
        this->direccion *= -1;
    }

    void DesplazarArriba()
    {
        this->y -= 1;
    }

    void DesplazarAbajo()
    {
        this->y += 1;
    }

    void Actualizar()
    {
        this->x += this->direccion;
    }
};