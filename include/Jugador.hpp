#pragma once
#include<Dibujo.hpp>
#include<Actualizable.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
class Jugador : public Dibujo
{
private:

public:
    Jugador() : Dibujo(0,6,"Jugador") 
    {}
    ~Jugador() {}
 
    
};   