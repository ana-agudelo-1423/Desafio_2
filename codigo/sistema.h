#ifndef SISTEMA_H
#define SISTEMA_H

#include "catalogo.h"
#include "usuario.h"
#include <string>

// Forward declaration
class MensajePublicitario;

class Sistema {
private:
    Catalogo* catalogo;
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

    MensajePublicitario** mensajesPublicitarios;
    int cantidadMensajes;
    int capacidadMensajes;

    Usuario* usuarioActual;

    // Métodos auxiliares
    void aumentarCapacidadUsuarios();
    void aumentarCapacidadMensajes();
    void cargarDatos();
    void guardarDatos();

public:
    Sistema();
    ~Sistema();

    // Gestión de usuarios
    bool iniciarSesion(const std::string& nickname);
    void cerrarSesion();
    bool registrarUsuario(const std::string& nickname, const std::string& tipoMembresia,
                          const std::string& ciudad, const std::string& pais, int fechaInscripcion);
    Usuario* buscarUsuario(const std::string& nickname) const;
    Usuario* getUsuarioActual() const;
    int getCantidadUsuarios() const;

    // Gestión de mensajes publicitarios
    void agregarMensajePublicitario(MensajePublicitario* mensaje);
    MensajePublicitario* obtenerMensajeAleatorio() const;
    int getCantidadMensajes() const;

    // Funcionalidades principales DEL MENÚ
    void reproduccionAleatoria();                    // Funcionalidad III
    void gestionarFavoritos();                       // Funcionalidad IV-a
    void seguirListaFavoritos(const std::string& nickname); // Funcionalidad IV-b
    void ejecutarListaFavoritos();                   // Funcionalidad IV-c

    // Métricas (Funcionalidad V)
    void mostrarMetricas(int iteraciones) const;
    size_t calcularMemoriaTotal() const;

    // Búsquedas auxiliares
    Cancion* buscarCancionPorId(int id) const;
    Album* buscarAlbumPorCancionId(int id) const;
    Artista* buscarArtistaPorCancionId(int id) const;

    // Acceso al catálogo
    Catalogo* getCatalogo() const;
};

#endif
