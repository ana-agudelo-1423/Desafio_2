#include "mensaje_publicitario.h"
#include <iostream>
using namespace std;

MensajePublicitario::MensajePublicitario(int id, const std::string& mensaje, const std::string& categoria)
    : id(id), mensaje(mensaje), categoria(categoria), vecesMostrado(0)  // Inicializar vecesMostrado
{
    // Validar y asignar prioridad según categoría
    if (categoria == "AAA") {
        prioridad = 3;
    } else if (categoria == "B") {
        prioridad = 2;
    } else if (categoria == "C") {
        prioridad = 1;
    } else {
        prioridad = 1;
        this->categoria = "C";
        cout << "Advertencia: Categoría '" << categoria << "' inválida. Usando 'C' por defecto." << endl;
    }

    // Validar longitud del mensaje
    if (mensaje.length() > 500) {
        this->mensaje = mensaje.substr(0, 500);
        cout << "Advertencia: Mensaje ID " << id << " truncado a 500 caracteres." << endl;
    }
}

// Getters - VERIFICAR que no estén duplicados en el archivo
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

int MensajePublicitario::getVecesMostrado() const
{
    return vecesMostrado;
}

bool MensajePublicitario::esCategoriaValida() const
{
    return (categoria == "C" || categoria == "B" || categoria == "AAA");
}

void MensajePublicitario::incrementarContador() {
    vecesMostrado++;
}

void MensajePublicitario::mostrarMensaje() {
    incrementarContador();

    cout << "\n==========================================" << endl;
    cout << "           MENSAJE PUBLICITARIO         " << endl;
    cout << "  Categoría: " << categoria;

    int espacios = 25 - categoria.length();
    for (int s = 0; s < espacios; s++) cout << " ";
    cout << "" << endl;

    cout << "  Prioridad: " << prioridad;
    espacios = 26 - to_string(prioridad).length();
    for (int s = 0; s < espacios; s++) cout << " ";
    cout << "" << endl;

    cout << "==========================================" << endl;
    cout << mensaje << endl;
    cout << "==========================================" << endl;
    cout << "         FIN MENSAJE PUBLICITARIO       " << endl;
    cout << "==========================================" << endl;
}
