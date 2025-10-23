#ifndef MENSAJE_PUBLICITARIO_H
#define MENSAJE_PUBLICITARIO_H

#include <string>

class MensajePublicitario {
private:
    int id;
    std::string mensaje;
    std::string categoria; // "C", "B" o "AAA"
    int prioridad; // Calculada: C=1, B=2, AAA=3

public:
    MensajePublicitario(int id, const std::string& mensaje, const std::string& categoria);

    // Getters
    int getId() const;
    const std::string& getMensaje() const;
    const std::string& getCategoria() const;
    int getPrioridad() const;

    // Validación
    bool esCategoriaValida() const;

    // Utilidades
    void mostrarMensaje() const;
};

#endif
