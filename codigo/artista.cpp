#include "artista.h"
using namespace std;

Artista::Artista(int id, int edad, const string& nombre, const string& paisOrigen)
    : id(id),
    edad(edad),
    seguidores(0),
    posicion(0),
    nombre(nombre),
    paisOrigen(paisOrigen),
    albums(nullptr),
    cantidadAlbums(0),
    capacidadAlbums(0)
{
}

Artista::~Artista()
{
    for (int i = 0; i < cantidadAlbums; ++i)
    {
        if (albums[i] != nullptr)
        {
            delete albums[i];
            albums[i] = nullptr;
        }
    }

    delete[] albums;
    albums = nullptr;

    cantidadAlbums = 0;
    capacidadAlbums = 0;
}

void Artista::aumentarCapacidadAlbums()
{
    int nuevaCapacidad;

    if (capacidadAlbums == 0)
    {
        nuevaCapacidad = 2;
    }
    else
    {
        nuevaCapacidad = capacidadAlbums * 2;
    }

    Album** nuevoArreglo = new Album*[nuevaCapacidad];

    for (int i = 0; i < cantidadAlbums; ++i)
    {
        nuevoArreglo[i] = albums[i];
    }

    delete[] albums;
    albums = nuevoArreglo;
    capacidadAlbums = nuevaCapacidad;
}

void Artista::agregarAlbum(Album* a)
{
    if (cantidadAlbums == capacidadAlbums)
    {
        aumentarCapacidadAlbums();
    }

    albums[cantidadAlbums] = a;
    cantidadAlbums = cantidadAlbums + 1;
}

int Artista::obtenerCantidadAlbums() const
{
    return cantidadAlbums;
}

Album* Artista::obtenerAlbumEn(int indice) const
{
    if (indice < 0 || indice >= cantidadAlbums)
    {
        return nullptr;
    }

    return albums[indice];
}

int Artista::obtenerId() const
{
    return id;
}

int Artista::obtenerEdad() const
{
    return edad;
}

int Artista::obtenerSeguidores() const
{
    return seguidores;
}

int Artista::obtenerPosicion() const
{
    return posicion;
}

const string& Artista::obtenerNombre() const
{
    return nombre;
}

const string& Artista::obtenerPaisOrigen() const
{
    return paisOrigen;
}

void Artista::setSeguidores(int valor)
{
    seguidores = valor;
}

void Artista::setPosicion(int valor)
{
    posicion = valor;
}
