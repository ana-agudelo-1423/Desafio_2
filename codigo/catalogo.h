#ifndef CATALOGO_H
#define CATALOGO_H

#include "artista.h"

class Catalogo
{
private:
    // Arreglo dinámico de punteros a Artista (NO dueños)
    Artista** listaArtistas;
    int       cantidadArtistas;
    int       capacidadArtistas;

    void      aumentarCapacidadArtistas();

public:
    Catalogo();
    ~Catalogo();

    void      agregarArtista(Artista* artista);
    int       obtenerCantidadArtistas() const;
    Artista*  obtenerArtistaEn(int indice) const;

    // Búsquedas en profundidad
    Cancion*  buscarCancionPorId(int idCancion) const;
    Album*    buscarAlbumPorCancionId(int idCancion) const;
};

#endif
