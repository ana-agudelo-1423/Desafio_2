#include "mensaje_publicitario.h"
#include <iostream>
using namespace std;

MensajePublicitario::MensajePublicitario(int id, const std::string& mensaje, const std::string& categoria)
    : id(id), mensaje(mensaje), categoria(categoria), vecesMostrado(0)
{
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

void MensajePublicitario::mostrarMensaje() const
{
    cout << "\n+----------------------------------------+" << endl;
    cout << "|        MENSAJE PUBLICITARIO            |" << endl;

    cout << "|  Categoria: " << categoria;
    int espacios = 26 - (int)categoria.length();
    if (espacios < 0) espacios = 0;
    for (int s = 0; s < espacios; ++s) cout << ' ';
    cout << "|" << endl;

    cout << "+----------------------------------------+" << endl;
    cout << mensaje << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "|      FIN MENSAJE PUBLICITARIO          |" << endl;
    cout << "+----------------------------------------+" << endl;
}

void MensajePublicitario::mostrarMensaje() {

    incrementarContador();


    cout << "\n+----------------------------------------+" << endl;
    cout << "|        MENSAJE PUBLICITARIO            |" << endl;

    cout << "|  Categoria: " << categoria;
    int espacios = 26 - (int)categoria.length();
    if (espacios < 0) espacios = 0;
    for (int s = 0; s < espacios; ++s) std::cout << ' ';
    cout << "|" << std::endl;

    cout << "+----------------------------------------+" << endl;
    cout << mensaje << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "|      FIN MENSAJE PUBLICITARIO          |" << endl;
    cout << "+----------------------------------------+" << endl;
}
