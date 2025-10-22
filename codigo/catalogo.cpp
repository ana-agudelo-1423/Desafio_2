#include "catalogo.h"
using namespace std;

Catalogo::Catalogo()
    : listaArtistas(nullptr),
    cantidadArtistas(0),
    capacidadArtistas(0)
{
}

Catalogo::~Catalogo()
{
    // No se eliminan los Artista* (NO somos dueños)
    delete[] listaArtistas;
}

void Catalogo::aumentarCapacidadArtistas()
{
    int nuevaCapacidad;

    if (capacidadArtistas == 0)
    {
        nuevaCapacidad = 2;
    }
    else
    {
        nuevaCapacidad = capacidadArtistas * 2;
    }

    Artista** nuevoArreglo = new Artista*[nuevaCapacidad];

    for (int i = 0; i < cantidadArtistas; ++i)
    {
        nuevoArreglo[i] = listaArtistas[i];
    }

    delete[] listaArtistas;
    listaArtistas = nuevoArreglo;
    capacidadArtistas = nuevaCapacidad;
}

void Catalogo::agregarArtista(Artista* artista)
{
    if (cantidadArtistas == capacidadArtistas)
    {
        aumentarCapacidadArtistas();
    }

    listaArtistas[cantidadArtistas] = artista;
    cantidadArtistas = cantidadArtistas + 1;
}

int Catalogo::obtenerCantidadArtistas() const
{
    return cantidadArtistas;
}

Artista* Catalogo::obtenerArtistaEn(int indice) const
{
    if (indice < 0 || indice >= cantidadArtistas)
    {
        return nullptr;
    }

    return listaArtistas[indice];
}

Cancion* Catalogo::buscarCancionPorId(int idCancion) const
{
    for (int i = 0; i < cantidadArtistas; ++i)
    {
        Artista* artistaActual = listaArtistas[i];

        if (artistaActual == nullptr)
        {
            continue;
        }

        for (int j = 0; j < artistaActual->obtenerCantidadAlbums(); ++j)
        {
            Album* albumActual = artistaActual->obtenerAlbumEn(j);

            if (albumActual == nullptr)
            {
                continue;
            }

            for (int k = 0; k < albumActual->obtenerCantidadCanciones(); ++k)
            {
                Cancion* cancionActual = albumActual->obtenerCancionEn(k);

                if (cancionActual != nullptr)
                {
                    if (cancionActual->obtenerId() == idCancion)
                    {
                        return cancionActual;
                    }
                }
            }
        }
    }

    return nullptr;
}

Album* Catalogo::buscarAlbumPorCancionId(int idCancion) const
{
    for (int i = 0; i < cantidadArtistas; ++i)
    {
        Artista* artistaActual = listaArtistas[i];

        if (artistaActual == nullptr)
        {
            continue;
        }

        for (int j = 0; j < artistaActual->obtenerCantidadAlbums(); ++j)
        {
            Album* albumActual = artistaActual->obtenerAlbumEn(j);

            if (albumActual == nullptr)
            {
                continue;
            }

            for (int k = 0; k < albumActual->obtenerCantidadCanciones(); ++k)
            {
                Cancion* cancionActual = albumActual->obtenerCancionEn(k);

                if (cancionActual != nullptr)
                {
                    if (cancionActual->obtenerId() == idCancion)
                    {
                        return albumActual;
                    }
                }
            }
        }
    }

    return nullptr;
}
