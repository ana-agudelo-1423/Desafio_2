#ifndef USUARIO_H
#define USUARIO_H

#include <string>

// Forward declarations
class Cancion;

class Usuario {
private:
    std::string nickname;
    std::string tipoMembresia; // "estandar" o "premium"
    std::string ciudad;
    std::string pais;
    int fechaInscripcion; // Formato AAAAMMDD

    // Lista de favoritos (solo para premium)
    Cancion** favoritos;
    int cantidadFavoritos;
    int capacidadFavoritos;

    // Usuario seguido (solo para premium)
    Usuario* usuarioSeguido;

    void aumentarCapacidadFavoritos();
    bool validarFecha(int fecha) const;

public:
    // Constructores
    Usuario(const std::string& nickname, const std::string& tipoMembresia,
            const std::string& ciudad, const std::string& pais, int fechaInscripcion);
    Usuario(const Usuario& otro); // Constructor de copia
    ~Usuario();

    // Operadores de sobrecarga (requeridos - mínimo 2)
    Usuario& operator=(const Usuario& otro);
    bool operator==(const Usuario& otro) const;
    bool operator!=(const Usuario& otro) const;

    // Getters
    const std::string& getNickname() const;
    const std::string& getTipoMembresia() const;
    const std::string& getCiudad() const;
    const std::string& getPais() const;
    int getFechaInscripcion() const;
    bool esPremium() const;

    // Gestión de favoritos
    bool agregarFavorito(Cancion* cancion);
    bool eliminarFavorito(int idCancion);
    bool tieneFavorito(int idCancion) const;
    bool tieneFavorito(Cancion* cancion) const;
    int getCantidadFavoritos() const;
    Cancion* getFavoritoEn(int indice) const;
    void limpiarFavoritos();
    bool estaLlenaListaFavoritos() const;

    // Seguir usuario
    bool seguirUsuario(Usuario* usuario);
    Usuario* getUsuarioSeguido() const;
    void dejarDeSeguir();
    bool estaSiguiendoA(const std::string& nickname) const;

    // Combinar listas (para funcionalidad de seguir)
    bool combinarConListaDe(Usuario* otroUsuario);

    // Utilidades
    void mostrarInformacion() const;
    std::string obtenerInfoResumida() const;
};

#endif
