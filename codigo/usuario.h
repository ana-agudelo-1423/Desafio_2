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

    // Lista de favoritos
    Cancion** favoritos;
    int cantidadFavoritos;
    int capacidadFavoritos;

    // ⬇️⬇️⬇️ AGREGAR ESTAS VARIABLES QUE FALTAN ⬇️⬇️⬇️
    // Historial de reproducción (SOLO premium)
    static const int MAX_HISTORIAL = 4;
    Cancion** historialReproduccion;
    int cantidadEnHistorial;
    int posicionActualHistorial;

    // Estado de reproducción actual
    Cancion* cancionActual;      // ✅ FALTA ESTA DECLARACIÓN
    bool reproduciendo;          // ✅ FALTA ESTA DECLARACIÓN

    // Control de publicidad (SOLO estándar)
    int contadorCancionesReproducidas;

    // Usuario seguido
    Usuario* usuarioSeguido;
    // ⬆️⬆️⬆️ FIN DE AGREGADOS ⬆️⬆️⬆️

    void aumentarCapacidadFavoritos();
    bool validarFecha(int fecha) const;


public:
    // Constructores
    Usuario(const std::string& nickname, const std::string& tipoMembresia,
            const std::string& ciudad, const std::string& pais, int fechaInscripcion);
    Usuario(const Usuario& otro);
    ~Usuario();

    // Operadores
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

    // Gestión de favoritos (COMPATIBLE con Sistema.cpp)
    bool agregarFavorito(Cancion* cancion);
    bool eliminarFavorito(int idCancion);
    bool tieneFavorito(int idCancion) const;
    bool tieneFavorito(Cancion* cancion) const;
    int getCantidadFavoritos() const;
    Cancion* getFavoritoEn(int indice) const;
    void limpiarFavoritos();
    bool estaLlenaListaFavoritos() const;

    // Seguir usuario (COMPATIBLE con Sistema.cpp)
    bool seguirUsuario(Usuario* usuario); // ✅ MANTENER Usuario* para compatibilidad
    Usuario* getUsuarioSeguido() const;   // ✅ MANTENER para compatibilidad
    void dejarDeSeguir();
    bool estaSiguiendoA(const std::string& nickname) const;

    // Combinar listas (NECESARIO para Sistema.cpp)
    bool combinarConListaDe(Usuario* otroUsuario); // ✅ AGREGAR este método

    // Gestión de reproducción e historial
    void iniciarReproduccion(Cancion* cancion);
    void detenerReproduccion();
    bool estaReproduciendo() const;
    Cancion* getCancionActual() const;

    // Navegación en historial (solo premium)
    bool puedeRetroceder() const;
    bool puedeAvanzar() const;
    Cancion* obtenerCancionAnterior();
    Cancion* obtenerCancionSiguiente();
    void agregarAlHistorial(Cancion* cancion);
    void limpiarHistorial();
    int getCantidadEnHistorial() const;

    // Control de publicidad (para estándar)
    bool debeMostrarPublicidad() const;
    void incrementarContadorPublicidad();
    void reiniciarContadorPublicidad();
    int getContadorCancionesReproducidas() const;

    // Utilidades
    void mostrarInformacion() const;
    std::string obtenerInfoResumida() const;
};

#endif
