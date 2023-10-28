#include <iostream>
#include <Mascota.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    // Mascota m1;
    // Mascota m2;

    // m1.Comer();
    // m2.Comer();

    cout << "Tipos de datos" << endl;
    cout << "int" << sizeof(int) << endl;
    cout << "char" << sizeof(char) << endl;
    cout << "bool" << sizeof(bool) << endl;
    cout << "float" << sizeof(float) << endl;
    cout << "double" << sizeof(double) << endl;
    cout << "Mascota" << sizeof(Mascota) << endl;

    int a = 4;
    cout << "Direcciones de memoria" << endl;
    cout << "tamaño" << sizeof(a) << endl;
    cout << "contenido" << a << endl;
    cout << "direccion" << &a << endl;

    void *puntero = malloc(32);
    free(puntero);

    cout << "Direcciones de memoria" << endl;
    cout << "size of: " << sizeof(puntero) << endl;
    cout << "puntero1:" << puntero << endl;
    cout << "puntero2:" << &puntero << endl;

    // memoria dinámica en C
    cout << "Mascota en C: " << endl;
    Mascota *MascotaC = (Mascota *)malloc(sizeof(Mascota));
    MascotaC->Inicializar();
    MascotaC->DecirNombre();
    MascotaC->Destruir();
    free(MascotaC);

    // cout << "Tamaño Puntero: " << sizeof(Mascota) << endl;
    //  Memoria dinámica en C++
    cout << "Mascota en C++: " << endl;
    Mascota *MascotaCPP = new Mascota();
    MascotaCPP->DecirNombre();
    delete MascotaCPP;
    // std::cout<<"I changed de time zone, but what do i know"<<std::endl;
    return 0;
}
