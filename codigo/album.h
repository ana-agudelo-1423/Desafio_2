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

    int puntuacion;
    std::string genero1;
    std::string genero2;
    std::string genero3;
    std::string genero4;

    Cancion** canciones;
    int cantidadCanciones;
    int capacidadCanciones;

    void aumentarCapacidadCanciones();
    void recalcularDuracionTotal();

public:
    Album(int id, const std::string& nombre, int fechaAAAAMMDD,
          const std::string& selloDisquero, const std::string& rutaPortada, int puntuacion, const std::string& genero1,
          const std::string& genero2, const std::string& genero3, const std::string& genero4);

    ~Album();

    void agregarCancion(Cancion* c);
    int obtenerCantidadCanciones() const;
    Cancion* obtenerCancionEn(int indice) const;

    float obtenerDuracionTotal() const;
    const std::string& obtenerNombre() const;
    const std::string& obtenerPortada() const;
    int obtenerId() const;

    int obtenerPuntuacion() const;
    const std::string&obtenerGenero1() const;
    const std::string&obtenerGenero2() const;
    const std::string&obtenerGenero3() const;
    const std::string&obtenerGenero4() const;
};

#endif
