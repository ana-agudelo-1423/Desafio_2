#ifndef USUARIO_H
#define USUARIO_H

#include <string>

// Forward declarations para evitar includes circulares
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

public:
    Usuario(const std::string& nickname, const std::string& tipoMembresia,
            const std::string& ciudad, const std::string& pais, int fechaInscripcion);
    ~Usuario();

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
    int getCantidadFavoritos() const;
    Cancion* getFavoritoEn(int indice) const;
    void limpiarFavoritos();

    // Seguir usuario
    void seguirUsuario(Usuario* usuario);
    Usuario* getUsuarioSeguido() const;
    void dejarDeSeguir();

    // Combinar listas (para funcionalidad de seguir)
    void combinarConListaDe(Usuario* otroUsuario);
};

#endif
