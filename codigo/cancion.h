#ifndef CANCION_H
#define CANCION_H

#include <string>
#include "credito.h"

class Cancion
{
private:
    int id;
    int reproducciones;
    float duracion;

    std::string nombre;
    std::string ruta128;
    std::string ruta320;

    Credito** creditos;
    int cantidadCreditos;
    int capacidadCreditos;

    void aumentarCapacidadCreditos();

public:
    Cancion(int id, float duracion,
            const std::string& nombre,
            const std::string& ruta128,
            const std::string& ruta320);

    ~Cancion();

    // Créditos
    void agregarCredito(Credito* c);
    int  obtenerCantidadCreditos() const;
    Credito* obtenerCreditoEn(int indice) const;

    void        reproducir(bool altaCalidad);
    void        reproducir(bool altaCalidad, const std::string& rutaPortadaAlbum);
    int  obtenerReproducciones() const;

    // Getters
    int obtenerId() const;
    float obtenerDuracion() const;
    const std::string& obtenerNombre() const;
};

#endif
