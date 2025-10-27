#ifndef USUARIO_H
#define USUARIO_H

#include <string>

    class Cancion;
class Usuario;

class Usuario {
private:
    std::string nickname;
    std::string tipoMembresia;
    std::string ciudad;
    std::string pais;
    int fechaInscripcion;

    Cancion** favoritos;
    int cantidadFavoritos;
    int capacidadFavoritos;

    static const int MAX_HISTORIAL = 4;
    Cancion** historialReproduccion;
    int cantidadEnHistorial;
    int posicionActualHistorial;

    Cancion* cancionActual;
    bool reproduciendo;

    int contadorCancionesReproducidas;

    Usuario* usuarioSeguido;

    void aumentarCapacidadFavoritos();
    bool validarFecha(int fecha) const;

public:
    Usuario(const std::string& nickname, const std::string& tipoMembresia,
            const std::string& ciudad, const std::string& pais, int fechaInscripcion);
    Usuario(const Usuario& otro);
    ~Usuario();

    Usuario& operator=(const Usuario& otro);
    bool operator==(const Usuario& otro) const;
    bool operator!=(const Usuario& otro) const;

    const std::string& getNickname() const;
    const std::string& getTipoMembresia() const;
    const std::string& getCiudad() const;
    const std::string& getPais() const;
    int getFechaInscripcion() const;
    bool esPremium() const;

    bool agregarFavorito(Cancion* cancion);
    bool eliminarFavorito(int idCancion);
    bool tieneFavorito(int idCancion) const;
    bool tieneFavorito(Cancion* cancion) const;
    int getCantidadFavoritos() const;
    Cancion* getFavoritoEn(int indice) const;
    void limpiarFavoritos();
    bool estaLlenaListaFavoritos() const;

    bool seguirUsuario(Usuario* usuario);
    Usuario* getUsuarioSeguido() const;
    void dejarDeSeguir();
    bool estaSiguiendoA(const std::string& nickname) const;

    bool combinarConListaDe(Usuario* otroUsuario);

    void iniciarReproduccion(Cancion* cancion);
    void detenerReproduccion();
    bool estaReproduciendo() const;
    Cancion* getCancionActual() const;

    bool puedeRetroceder() const;
    bool puedeAvanzar() const;
    Cancion* obtenerCancionAnterior();
    Cancion* obtenerCancionSiguiente();
    void agregarAlHistorial(Cancion* cancion);
    void limpiarHistorial();
    int getCantidadEnHistorial() const;

    bool debeMostrarPublicidad() const;
    void incrementarContadorPublicidad();
    void reiniciarContadorPublicidad();
    int getContadorCancionesReproducidas() const;

    void mostrarInformacion() const;
    std::string obtenerInfoResumida() const;

    void setTipoMembresia(const std::string& tipo);
};

#endif
