#include "mensaje_publicitario.h"
#include <iostream>
using namespace std;

MensajePublicitario::MensajePublicitario(int id, const std::string& mensaje, const std::string& categoria)
    : id(id), mensaje(mensaje), categoria(categoria)
{
    // Validar y asignar prioridad según categoría (requerimiento del enunciado)
    if (categoria == "AAA") {
        prioridad = 3; // Triple prioridad
    } else if (categoria == "B") {
        prioridad = 2; // Doble prioridad
    } else if (categoria == "C") {
        prioridad = 1; // Prioridad simple
    } else {
        // Categoría por defecto si no es válida
        prioridad = 1;
        this->categoria = "C";
        cout << "Advertencia: Categoría '" << categoria << "' inválida. Usando 'C' por defecto." << endl;
    }

    // Validar longitud del mensaje (máximo 500 caracteres - requerimiento)
    if (mensaje.length() > 500) {
        this->mensaje = mensaje.substr(0, 500);
        cout << "Advertencia: Mensaje ID " << id << " truncado a 500 caracteres." << endl;
    }
}

// Getters
int MensajePublicitario::getId() const
{
    return id;
}

const std::string& MensajePublicitario::getMensaje() const
{
    return mensaje;
}

const std::string& MensajePublicitario::getCategoria() const
{
    return categoria;
}

int MensajePublicitario::getPrioridad() const
{
    return prioridad;
}

bool MensajePublicitario::esCategoriaValida() const
{
    return (categoria == "C" || categoria == "B" || categoria == "AAA");
}

void MensajePublicitario::mostrarMensaje() const
{
    cout << "\n┌────────────────────────────────────────┐" << endl;
    cout << "│           MENSAJE PUBLICITARIO         │" << endl;
    cout << "│  Categoría: " << categoria;
    // Ajustar espacios para alineación
    int espacios = 25 - categoria.length();
    for (int s = 0; s < espacios; s++) cout << " ";
    cout << "│" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
    cout << mensaje << endl;
    cout << "┌────────────────────────────────────────┐" << endl;
    cout << "│         FIN MENSAJE PUBLICITARIO       │" << endl;
    cout << "└────────────────────────────────────────┘" << endl;
}
