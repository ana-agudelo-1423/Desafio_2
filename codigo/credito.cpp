#include "credito.h"
using namespace std;

Credito::Credito(int id, const std::string& nombre, const std::string& apellido,
                 const std::string& categoria, const std::string& afiliacion)
    : id(id),
    nombre(nombre),
    apellido(apellido),
    categoria(categoria),
    afiliacion(afiliacion)
{
}

Credito::~Credito()
{
}

int Credito::getId() const
{
    return id;
}

const string& Credito::getNombre() const
{
    return nombre;
}

const std::string& Credito::getApellido() const
{
    return apellido;
}

const std::string& Credito::getCategoria() const
{
    return categoria;
}

const std::string& Credito::getAfiliacion() const
{
    return afiliacion;
}
