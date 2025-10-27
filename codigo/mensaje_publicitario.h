#ifndef MENSAJE_PUBLICITARIO_H
#define MENSAJE_PUBLICITARIO_H

#include <string>
#include <iostream>

class MensajePublicitario {
private:
    int id;
    std::string mensaje;
    std::string categoria;
    int prioridad;
    int vecesMostrado;  // Asegurar que esta línea existe

public:
    MensajePublicitario(int id, const std::string& mensaje, const std::string& categoria);

    // Getters
    int getId() const;
    const std::string& getMensaje() const;
    const std::string& getCategoria() const;
    int getPrioridad() const;
    int getVecesMostrado() const;  // Asegurar que esta declaración existe

    bool esCategoriaValida() const;
    void mostrarMensaje();  // Sin const porque modifica vecesMostrado
    void incrementarContador();  // Esta declaración debe existir
    void mostrarMensaje() const;
};

#endif
