#ifndef PLAN_ESTANDAR_H
#define PLAN_ESTANDAR_H

#include "mensaje_publicitario.h"
#include "usuario.h"
#include "cancion.h"
#include "album.h"

class PlanEstandar
{
private:
    MensajePublicitario** listaMensajes;
    int                   cantidadMensajes;
    int                   capacidadMensajes;
    int                   indiceActualPublicidad;

    void aumentarCapacidadMensajes();

public:
    PlanEstandar();
    ~PlanEstandar();

    void agregarMensaje(MensajePublicitario* mensaje);
    int  obtenerCantidadMensajes() const;
    MensajePublicitario* obtenerMensajeEn(int indice) const;

    void reproducirCancion(Usuario* usuario, Cancion* cancion, Album* album);
    void mostrarPublicidad();

    int  getCalidad() const;
    const char* getNombrePlan() const;
};

#endif
