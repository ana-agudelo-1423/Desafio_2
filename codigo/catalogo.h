#ifndef CATALOGO_H
#define CATALOGO_H

#include "artista.h"

class Catalogo
{
private:
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

    Cancion*  buscarCancionPorId(int idCancion) const;
    Album*    buscarAlbumPorCancionId(int idCancion) const;

    Artista*  buscarArtistaPorId(int idArtista) const;
    Album*    buscarAlbumPorId(int idAlbum) const;
};

#endif
