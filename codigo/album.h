#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "cancion.h"

class Album
{
private:
    int id;
    std::string nombre;
    int fechaAAAAMMDD;
    std::string selloDisquero;
    std::string rutaPortada;
    float duracionTotal;

    Cancion** canciones;
    int cantidadCanciones;
    int capacidadCanciones;

    void aumentarCapacidadCanciones();
    void recalcularDuracionTotal();

public:
    Album(int id, const std::string& nombre, int fechaAAAAMMDD,
          const std::string& selloDisquero, const std::string& rutaPortada);

    ~Album();

    void agregarCancion(Cancion* c);
    int obtenerCantidadCanciones() const;
    Cancion* obtenerCancionEn(int indice) const;

    float obtenerDuracionTotal() const;
    const std::string& obtenerNombre() const;
    const std::string& obtenerPortada() const;
    int obtenerId() const;
};

#endif
