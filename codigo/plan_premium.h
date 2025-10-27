#ifndef PLAN_PREMIUM_H
#define PLAN_PREMIUM_H

#include "usuario.h"
#include "cancion.h"
#include "album.h"

class PlanPremium
{
public:
    PlanPremium();
    ~PlanPremium();

    // Reproduce en 320 kbps y agrega al historial del usuario (premium)
    void reproducirCancion(Usuario* usuario, Cancion* cancion, Album* album);

    // Ayudas opcionales (delegan en Usuario)
    bool agregarAFavoritos(Usuario* usuario, Cancion* cancion);
    Cancion* retroceder(Usuario* usuario);
    Cancion* avanzar(Usuario* usuario);

    int         getCalidad() const;
    const char* getNombrePlan() const;
};

#endif
