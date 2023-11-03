#include <Dibujo.hpp>
#include <Ventana.hpp>
#include <list>
#include <curses.h>
#include <Portero.hpp>
#include <Porteria.hpp>
#include <Bocha.hpp>
#include <Jugador.hpp>

using namespace std;

int main(int argc, char const *argv[])
{

   Ventana ventana;
   Portero *portero = new Portero(109, 5);
   Porteria *porteria = new Porteria(115, 0);
   Jugador* jugador = new Jugador();
   Bocha* bocha = new Bocha(10,8);


   list<Dibujo*> dibujos;
   dibujos.push_back(portero);
   dibujos.push_back(porteria);
   dibujos.push_back(jugador);
   dibujos.push_back(bocha);

   list<Actualizable*> actualizables;
   actualizables.push_back(portero);
   actualizables.push_back(porteria);
   actualizables.push_back(bocha);
 
   
   
   while (true)
   {

      int key = getch();
      if (key == 'q' || key == 'q')
      {
         // Salir del juego
         break;
      }

      if (key==KEY_LEFT)
      {
         portero->DesplazarIzquierda();
      } 

      if (key==KEY_RIGHT)
      {
         portero->DesplazarDerecha();
      }

      if (key==KEY_DOWN)
      {
         portero->DesplazarAbajo();
      } 

      if (key==KEY_UP)
      {
         portero->DesplazarArriba();
      }

      if(key == 'p')
      {
         bocha->CambiarDireccion();
      }

      if(key == 'w')
      {
         bocha->DesplazarArriba();
      }

      if(key == 's')
      {
         bocha->DesplazarAbajo();
      }
      ventana.Dibujar(dibujos);
      ventana.Actualizar(actualizables);
   }

   return 0;
}
