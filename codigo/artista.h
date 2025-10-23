#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include "album.h"

class Artista
{
private:
    int id;
    int edad;
    int seguidores;
    int posicion;
    std::string nombre;
    std::string paisOrigen;

    Album** albums;
    int cantidadAlbums;
    int capacidadAlbums;

    void aumentarCapacidadAlbums();

public:
    Artista(int id, int edad, const std::string& nombre, const std::string& paisOrigen);
    ~Artista();

    void agregarAlbum(Album* a);
    int obtenerCantidadAlbums() const;
    Album* obtenerAlbumEn(int indice) const;


    int obtenerId() const;
    int obtenerEdad() const;
    int obtenerSeguidores() const;
    int obtenerPosicion() const;
    const std::string& obtenerNombre() const;
    const std::string& obtenerPaisOrigen() const;

    // Setters
    void setSeguidores(int valor);
    void setPosicion(int valor);
};

#endif
