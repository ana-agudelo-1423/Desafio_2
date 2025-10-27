#include "plan_estandar.h"
#include <iostream>
using namespace std;

PlanEstandar::PlanEstandar()
    : listaMensajes(nullptr),
    cantidadMensajes(0),
    capacidadMensajes(0),
    indiceActualPublicidad(0)
{
}

PlanEstandar::~PlanEstandar()
{
    delete[] listaMensajes;
    listaMensajes = nullptr;
    cantidadMensajes = 0;
    capacidadMensajes = 0;
}

void PlanEstandar::aumentarCapacidadMensajes()
{
    int nuevaCapacidad;

    if (capacidadMensajes == 0)
    {
        nuevaCapacidad = 2;
    }
    else
    {
        nuevaCapacidad = capacidadMensajes * 2;
    }

    MensajePublicitario** nuevoArreglo = new MensajePublicitario*[nuevaCapacidad];

    for (int i = 0; i < cantidadMensajes; ++i)
    {
        nuevoArreglo[i] = listaMensajes[i];
    }

    delete[] listaMensajes;
    listaMensajes = nuevoArreglo;
    capacidadMensajes = nuevaCapacidad;
}

void PlanEstandar::agregarMensaje(MensajePublicitario* mensaje)
{
    if (mensaje == nullptr)
    {
        return;
    }

    if (cantidadMensajes == capacidadMensajes)
    {
        aumentarCapacidadMensajes();
    }

    listaMensajes[cantidadMensajes] = mensaje;
    cantidadMensajes = cantidadMensajes + 1;
}

int PlanEstandar::obtenerCantidadMensajes() const
{
    return cantidadMensajes;
}

MensajePublicitario* PlanEstandar::obtenerMensajeEn(int indice) const
{
    if (indice < 0 || indice >= cantidadMensajes)
    {
        return nullptr;
    }

    return listaMensajes[indice];
}

void PlanEstandar::mostrarPublicidad()
{
    if (cantidadMensajes == 0)
    {
        cout << "[PUBLICIDAD] No hay mensajes configurados." << endl;
        return;
    }

    MensajePublicitario* mensajeActual = listaMensajes[indiceActualPublicidad];

    if (mensajeActual != nullptr)
    {
        mensajeActual->mostrarMensaje();
    }
    else
    {
        cout << "[PUBLICIDAD] Mensaje inválido." << endl;
    }

    indiceActualPublicidad = indiceActualPublicidad + 1;

    if (indiceActualPublicidad >= cantidadMensajes)
    {
        indiceActualPublicidad = 0;
    }
}

void PlanEstandar::reproducirCancion(Usuario* usuario, Cancion* cancion, Album* album)
{
    if (usuario == nullptr || cancion == nullptr || album == nullptr)
    {
        cout << "Error: datos inválidos para reproducir." << endl;
        return;
    }

    cout << "Portada: " << album->obtenerPortada() << endl;

    bool altaCalidad = false;
    cancion->reproducir(altaCalidad);

    usuario->incrementarContadorPublicidad();

    if (usuario->debeMostrarPublicidad())
    {
        mostrarPublicidad();
    }
}

int PlanEstandar::getCalidad() const
{
    return 128;
}

const char* PlanEstandar::getNombrePlan() const
{
    return "estandar";
}
