#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
class Mascota
{
private:
    string nombre;

public:
    Mascota(/* args */)
    {
        cout << "Ha nacido una mascota" << endl;
        this->nombre = "Caramelo";
    }
    void Inicializar()
    {
        cout<<"Ha nacido una nueva mascota"<<endl;
        this->nombre = "Caramelo" ;
    }


    ~Mascota()
    {
        cout << "Adios perro" << endl;
    }
    void Destruir()
    {
        cout<<"Adios perros"<<endl;
    }

    void DecirNombre()
    {
        cout << "Mi nombre es:" << this->nombre << endl;
    }
};