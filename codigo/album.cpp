#include "album.h"
using namespace std;

Album::Album(
    int id,
    const string& nombre,
    int fechaAAAAMMDD,
    const string& selloDisquero,
    const string& rutaPortada
    )
    : id(id),
    nombre(nombre),
    fechaAAAAMMDD(fechaAAAAMMDD),
    selloDisquero(selloDisquero),
    rutaPortada(rutaPortada),
    duracionTotal(0.0f),
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
