#ifndef CREDITO_H
#define CREDITO_H

#include <string>

class Credito {
private:
    int         id;
    std::string nombre;
    std::string apellido;
    std::string categoria;
    std::string afiliacion;


public:
    Credito(int id, const std::string& nombre, const std::string& apellido,
            const std::string& categoria, const std::string& afiliacion);
    ~Credito();

    int getId() const;
    const std::string& getNombre() const;
    const std::string&  getApellido() const;
    const std::string&  getCategoria() const;
    const std::string&  getAfiliacion() const;
};

#endif
