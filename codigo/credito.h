#ifndef CREDITO_H
#define CREDITO_H

#include <string>

class Credito {
private:
    int id;
    std::string nombre;
    std::string rol;  //Para productor, músico o compositor

public:
    Credito(int id, const std::string& nombre, const std::string& rol);
    ~Credito();

    int getId() const;
    const std::string& getNombre() const;
    const std::string& getRol() const;
};

#endif
