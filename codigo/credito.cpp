#include "credito.h"
using namespace std;

Credito::Credito(int id, const string& nombre, const string& rol)
    : id(id), nombre(nombre), rol(rol)
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

const string& Credito::getRol() const
{
    return rol;
}
