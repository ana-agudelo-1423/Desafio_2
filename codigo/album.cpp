#include "album.h"
using namespace std;

Album::Album(int id, const std::string& nombre, int fechaAAAAMMDD,
             const std::string& selloDisquero, const std::string& rutaPortada,
             int puntuacion, const std::string& genero1,
             const std::string& genero2, const std::string& genero3, const std::string& genero4)

    : id(id),
    nombre(nombre),
    fechaAAAAMMDD(fechaAAAAMMDD),
    selloDisquero(selloDisquero),
    rutaPortada(rutaPortada),
    duracionTotal(0.0f),
    puntuacion(puntuacion),
    genero1(genero1),
    genero2(genero2),
    genero3(genero3),
    genero4(genero4),
    canciones(nullptr),
    cantidadCanciones(0),
    capacidadCanciones(0)
{
}

Album::~Album()
{
    for (int i = 0; i < cantidadCanciones; ++i)
    {
        if (canciones[i] != nullptr)
        {
            delete canciones[i];
            canciones[i] = nullptr;
        }
    }

    delete[] canciones;
    canciones = nullptr;

    cantidadCanciones = 0;
    capacidadCanciones = 0;
    duracionTotal = 0.0f;
}

void Album::aumentarCapacidadCanciones()
{
    int nuevaCapacidad;

    if (capacidadCanciones == 0)
    {
        nuevaCapacidad = 2;
    }
    else
    {
        nuevaCapacidad = capacidadCanciones * 2;
    }

    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadCanciones; ++i)
    {
        nuevoArreglo[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevoArreglo;
    capacidadCanciones = nuevaCapacidad;
}

void Album::recalcularDuracionTotal()
{
    float total = 0.0f;

    for (int i = 0; i < cantidadCanciones; ++i)
    {
        if (canciones[i] != nullptr)
        {
            total = total + canciones[i]->obtenerDuracion();
        }
    }

    duracionTotal = total;
}

void Album::agregarCancion(Cancion* c)
{
    if (cantidadCanciones == capacidadCanciones)
    {
        aumentarCapacidadCanciones();
    }

    canciones[cantidadCanciones] = c;
    cantidadCanciones = cantidadCanciones + 1;

    recalcularDuracionTotal();
}

int Album::obtenerCantidadCanciones() const
{
    return cantidadCanciones;
}

Cancion* Album::obtenerCancionEn(int indice) const
{
    if (indice < 0 || indice >= cantidadCanciones)
    {
        return nullptr;
    }

    return canciones[indice];
}

float Album::obtenerDuracionTotal() const
{
    return duracionTotal;
}

const string& Album::obtenerNombre() const
{
    return nombre;
}

const string& Album::obtenerPortada() const
{
    return rutaPortada;
}

int Album::obtenerId() const
{
    return id;
}

int Album::obtenerPuntuacion() const
{
    return puntuacion;
}

const std::string& Album::obtenerGenero1() const
{
    return genero1;
}

const std::string& Album::obtenerGenero2() const
{
    return genero2;
}

const std::string& Album::obtenerGenero3() const
{
    return genero3;
}

const std::string& Album::obtenerGenero4() const
{
    return genero4;
}
