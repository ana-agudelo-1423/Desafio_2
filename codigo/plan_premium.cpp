#include "plan_premium.h"
#include <iostream>
using namespace std;

PlanPremium::PlanPremium()
{
}

PlanPremium::~PlanPremium()
{
}

void PlanPremium::reproducirCancion(Usuario* usuario, Cancion* cancion, Album* album)
{
    if (usuario == nullptr || cancion == nullptr || album == nullptr)
    {
        cout << "Error: datos invalidos para reproducir en PlanPremium." << endl;
        return;
    }

    // MUESTRA portada y reproduce a 320 kbps (alta calidad)
    // Esta variante imprime portada y luego el audio (segun el enunciado)
    cancion->reproducir(true, album->obtenerPortada());

    // Notificar al usuario (esto agrega al historial si es premium)
    usuario->iniciarReproduccion(cancion);
}

bool PlanPremium::agregarAFavoritos(Usuario* usuario, Cancion* cancion)
{
    if (usuario == nullptr || cancion == nullptr)
    {
        return false;
    }

    return usuario->agregarFavorito(cancion);
}

Cancion* PlanPremium::retroceder(Usuario* usuario)
{
    if (usuario == nullptr)
    {
        return nullptr;
    }

    return usuario->obtenerCancionAnterior();
}

Cancion* PlanPremium::avanzar(Usuario* usuario)
{
    if (usuario == nullptr)
    {
        return nullptr;
    }

    return usuario->obtenerCancionSiguiente();
}

int PlanPremium::getCalidad() const
{
    return 320;
}

const char* PlanPremium::getNombrePlan() const
{
    return "premium";
}
