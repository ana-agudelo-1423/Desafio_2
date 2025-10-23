#include "cancion.h"
using namespace std;

Cancion::Cancion(
    int id,
    float duracion,
    const string& nombre,
    const string& ruta128,
    const string& ruta320
    )
    : id(id),
    reproducciones(0),
    duracion(duracion),
    nombre(nombre),
    ruta128(ruta128),
    ruta320(ruta320),
    creditos(nullptr),
    cantidadCreditos(0),
    capacidadCreditos(0)
{
}

Cancion::~Cancion()
{
    delete[] creditos;
}

void Cancion::aumentarCapacidadCreditos()
{
    int nuevaCapacidad;

    if (capacidadCreditos == 0)
    {
        nuevaCapacidad = 2;
    }
    else
    {
        nuevaCapacidad = capacidadCreditos * 2;
    }

    Credito** nuevoArreglo = new Credito*[nuevaCapacidad];

    for (int i = 0; i < cantidadCreditos; ++i)
    {
        nuevoArreglo[i] = creditos[i];
    }

    delete[] creditos;
    creditos = nuevoArreglo;
    capacidadCreditos = nuevaCapacidad;
}

void Cancion::agregarCredito(Credito* c)
{
    if (cantidadCreditos == capacidadCreditos)
    {
        aumentarCapacidadCreditos();
    }

    creditos[cantidadCreditos] = c;
    cantidadCreditos = cantidadCreditos + 1;
}

int Cancion::obtenerCantidadCreditos() const
{
    return cantidadCreditos;
}

Credito* Cancion::obtenerCreditoEn(int indice) const
{
    if (indice < 0 || indice >= cantidadCreditos)
    {
        return nullptr;
    }

    return creditos[indice];
}

void Cancion::aumentarReproducciones()
{
    reproducciones = reproducciones + 1;
}

int Cancion::obtenerReproducciones() const
{
    return reproducciones;
}

const string& Cancion::obtenerRuta(bool altaCalidad) const
{
    if (altaCalidad)
    {
        return ruta320;
    }
    else
    {
        return ruta128;
    }
}

int Cancion::obtenerId() const
{
    return id;
}

float Cancion::obtenerDuracion() const
{
    return duracion;
}

const string& Cancion::obtenerNombre() const
{
    return nombre;
}
