#include "usuario.h"
#include "cancion.h"
#include <iostream>
using namespace std;

Usuario::Usuario(const std::string& nickname, const std::string& tipoMembresia,
                 const std::string& ciudad, const std::string& pais, int fechaInscripcion)
    : nickname(nickname),
    tipoMembresia(tipoMembresia),
    ciudad(ciudad),
    pais(pais),
    fechaInscripcion(fechaInscripcion),
    favoritos(nullptr),
    cantidadFavoritos(0),
    capacidadFavoritos(0),
    // ⬇️⬇️⬇️ AGREGAR ESTAS LINEAS NUEVAS ⬇️⬇️⬇️
    historialReproduccion(nullptr),
    cantidadEnHistorial(0),
    posicionActualHistorial(-1),
    cancionActual(nullptr),
    reproduciendo(false),
    contadorCancionesReproducidas(0),
    usuarioSeguido(nullptr)
// ⬆️⬆️⬆️ FIN DE AGREGADOS ⬆️⬆️⬆️
{
    // ⬇️⬇️⬇️ AGREGAR ESTO DENTRO DEL CONSTRUCTOR ⬇️⬇️⬇️
    // Inicializar historial de reproducción (solo para premium)
    if (esPremium()) {
        historialReproduccion = new Cancion*[MAX_HISTORIAL];
        for (int i = 0; i < MAX_HISTORIAL; ++i) {
            historialReproduccion[i] = nullptr;
        }
    }
    // ⬆️⬆️⬆️ FIN DE AGREGADOS ⬆️⬆️⬆️

    // Validar tipo de membresía
    if (tipoMembresia != "estandar" && tipoMembresia != "premium") {
        this->tipoMembresia = "estandar";
    }

    // Validar fecha
    if (!validarFecha(fechaInscripcion)) {
        this->fechaInscripcion = 20240101;
    }
}

// CONSTRUCTOR DE COPIA (requerido por el enunciado)
Usuario::Usuario(const Usuario& otro)
    : nickname(otro.nickname),
    tipoMembresia(otro.tipoMembresia),
    ciudad(otro.ciudad),
    pais(otro.pais),
    fechaInscripcion(otro.fechaInscripcion),
    favoritos(nullptr),
    cantidadFavoritos(0),
    capacidadFavoritos(0),
    usuarioSeguido(nullptr) // No copiamos el usuario seguido (es referencia)
{
    // Copiar lista de favoritos
    for (int i = 0; i < otro.cantidadFavoritos; ++i) {
        agregarFavorito(otro.favoritos[i]);
    }
}

Usuario::~Usuario()
{
    // No eliminamos las canciones (NO somos dueños)
    delete[] favoritos;
    if (historialReproduccion != nullptr) {
        delete[] historialReproduccion;
         }
}

// OPERADOR DE ASIGNACIÓN (sobrecarga requerida)
Usuario& Usuario::operator=(const Usuario& otro)
{
    if (this != &otro) { // Evitar auto-asignación
        // Copiar datos básicos
        nickname = otro.nickname;
        tipoMembresia = otro.tipoMembresia;
        ciudad = otro.ciudad;
        pais = otro.pais;
        fechaInscripcion = otro.fechaInscripcion;

        // Limpiar favoritos existentes
        limpiarFavoritos();
        delete[] favoritos;

        // Copiar lista de favoritos
        capacidadFavoritos = otro.capacidadFavoritos;
        if (capacidadFavoritos > 0) {
            favoritos = new Cancion*[capacidadFavoritos];
            for (int i = 0; i < otro.cantidadFavoritos; ++i) {
                favoritos[i] = otro.favoritos[i];
            }
            cantidadFavoritos = otro.cantidadFavoritos;
        } else {
            favoritos = nullptr;
            cantidadFavoritos = 0;
        }

        // No copiamos usuario seguido (es referencia)
        usuarioSeguido = nullptr;
    }
    return *this;
}

// OPERADOR DE IGUALDAD (sobrecarga requerida)
bool Usuario::operator==(const Usuario& otro) const
{
    return nickname == otro.nickname;
}

// OPERADOR DE DESIGUALDAD
bool Usuario::operator!=(const Usuario& otro) const
{
    return !(*this == otro);
}

void Usuario::aumentarCapacidadFavoritos()
{
    int nuevaCapacidad;

    if (capacidadFavoritos == 0) {
        nuevaCapacidad = 10; // Capacidad inicial
    } else {
        nuevaCapacidad = capacidadFavoritos * 2;
    }

    // Limitar a 10000 como máximo (requerimiento del enunciado)
    if (nuevaCapacidad > 10000) {
        nuevaCapacidad = 10000;
    }

    Cancion** nuevoArreglo = new Cancion*[nuevaCapacidad];

    for (int i = 0; i < cantidadFavoritos; ++i) {
        nuevoArreglo[i] = favoritos[i];
    }

    delete[] favoritos;
    favoritos = nuevoArreglo;
    capacidadFavoritos = nuevaCapacidad;
}

bool Usuario::validarFecha(int fecha) const
{
    // Validación básica de fecha (AAAAMMDD)
    if (fecha < 19000101 || fecha > 21001231) {
        return false;
    }

    int año = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;

    if (mes < 1 || mes > 12 || dia < 1 || dia > 31) {
        return false;
    }

    return true;
}

// Getters
const std::string& Usuario::getNickname() const { return nickname; }
const std::string& Usuario::getTipoMembresia() const { return tipoMembresia; }
const std::string& Usuario::getCiudad() const { return ciudad; }
const std::string& Usuario::getPais() const { return pais; }
int Usuario::getFechaInscripcion() const { return fechaInscripcion; }
bool Usuario::esPremium() const { return tipoMembresia == "premium"; }

// Gestión de favoritos
bool Usuario::agregarFavorito(Cancion* cancion)
{
    // Solo usuarios premium pueden tener favoritos
    if (!esPremium()) {
        cout << "Error: Solo usuarios premium pueden agregar favoritos." << endl;
        return false;
    }

    if (cancion == nullptr) {
        cout << "Error: Canción inválida." << endl;
        return false;
    }

    // Verificar límite de 10000 canciones
    if (estaLlenaListaFavoritos()) {
        cout << "Error: Lista de favoritos llena (máximo 10000 canciones)." << endl;
        return false;
    }

    // Verificar que no esté ya en favoritos
    if (tieneFavorito(cancion)) {
        cout << "Error: La canción ya está en favoritos." << endl;
        return false;
    }

    // Aumentar capacidad si es necesario
    if (cantidadFavoritos == capacidadFavoritos) {
        aumentarCapacidadFavoritos();
    }

    // Agregar a la lista
    favoritos[cantidadFavoritos] = cancion;
    cantidadFavoritos++;

    cout << "Canción '" << cancion->obtenerNombre()
         << "' agregada a favoritos." << endl;
    return true;
}

bool Usuario::eliminarFavorito(int idCancion)
{
    if (!esPremium()) {
        cout << "Error: Solo usuarios premium pueden eliminar favoritos." << endl;
        return false;
    }

    for (int i = 0; i < cantidadFavoritos; ++i) {
        if (favoritos[i] != nullptr && favoritos[i]->obtenerId() == idCancion) {
            // Mostrar información de la canción eliminada
            cout << "Eliminando canción '" << favoritos[i]->obtenerNombre()
                 << "' de favoritos." << endl;

            // Mover todas las canciones posteriores una posición hacia atrás
            for (int j = i; j < cantidadFavoritos - 1; ++j) {
                favoritos[j] = favoritos[j + 1];
            }
            cantidadFavoritos--;
            return true;
        }
    }

    cout << "Error: Canción con ID " << idCancion << " no encontrada en favoritos." << endl;
    return false;
}

bool Usuario::tieneFavorito(int idCancion) const
{
    if (!esPremium()) {
        return false;
    }

    for (int i = 0; i < cantidadFavoritos; ++i) {
        if (favoritos[i] != nullptr && favoritos[i]->obtenerId() == idCancion) {
            return true;
        }
    }

    return false;
}

bool Usuario::tieneFavorito(Cancion* cancion) const
{
    if (!esPremium() || cancion == nullptr) {
        return false;
    }

    return tieneFavorito(cancion->obtenerId());
}

int Usuario::getCantidadFavoritos() const { return cantidadFavoritos; }

Cancion* Usuario::getFavoritoEn(int indice) const
{
    if (indice < 0 || indice >= cantidadFavoritos) {
        return nullptr;
    }

    return favoritos[indice];
}

void Usuario::limpiarFavoritos()
{
    cantidadFavoritos = 0;
    cout << "Lista de favoritos limpiada." << endl;
}

bool Usuario::estaLlenaListaFavoritos() const
{
    return cantidadFavoritos >= 10000;
}

// Seguir usuario
bool Usuario::seguirUsuario(Usuario* usuario)
{
    if (!esPremium()) {
        cout << "Error: Solo usuarios premium pueden seguir a otros usuarios." << endl;
        return false;
    }

    if (usuario == nullptr) {
        cout << "Error: Usuario inválido." << endl;
        return false;
    }

    if (!usuario->esPremium()) {
        cout << "Error: Solo puedes seguir a usuarios premium." << endl;
        return false;
    }

    if (this == usuario) {
        cout << "Error: No puedes seguirte a ti mismo." << endl;
        return false;
    }

    if (usuarioSeguido != nullptr) {
        cout << "Dejando de seguir a: " << usuarioSeguido->getNickname() << endl;
    }

    usuarioSeguido = usuario;
    cout << "Ahora sigues a: " << usuario->getNickname() << endl;
    return true;
}

Usuario* Usuario::getUsuarioSeguido() const { return usuarioSeguido; }

void Usuario::dejarDeSeguir()
{
    if (usuarioSeguido != nullptr) {
        cout << "Dejando de seguir a: " << usuarioSeguido->getNickname() << endl;
        usuarioSeguido = nullptr;
    } else {
        cout << "No estás siguiendo a ningún usuario." << endl;
    }
}

bool Usuario::estaSiguiendoA(const std::string& nickname) const
{
    return (usuarioSeguido != nullptr && usuarioSeguido->getNickname() == nickname);
}

// Combinar listas (para funcionalidad de seguir)
bool Usuario::combinarConListaDe(Usuario* otroUsuario)
{
    if (!esPremium() || otroUsuario == nullptr || !otroUsuario->esPremium()) {
        cout << "Error: No se puede combinar listas." << endl;
        return false;
    }

    int cantidadOtro = otroUsuario->getCantidadFavoritos();
    int cancionesAgregadas = 0;

    cout << "Combinando lista de " << otroUsuario->getNickname()
         << " (" << cantidadOtro << " canciones)..." << endl;

    for (int i = 0; i < cantidadOtro; ++i) {
        Cancion* cancion = otroUsuario->getFavoritoEn(i);
        if (cancion != nullptr) {
            if (agregarFavorito(cancion)) {
                cancionesAgregadas++;
            }
        }
    }

    cout << "Se agregaron " << cancionesAgregadas << " nuevas canciones a tu lista." << endl;
    return cancionesAgregadas > 0;
}

// Utilidades
void Usuario::mostrarInformacion() const
{
    cout << "\n=== INFORMACIÓN DE USUARIO ===" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Membresía: " << tipoMembresia << endl;
    cout << "Ubicación: " << ciudad << ", " << pais << endl;
    cout << "Fecha de inscripción: " << fechaInscripcion << endl;
    cout << "Favoritos: " << cantidadFavoritos << " canciones" << endl;

    if (usuarioSeguido != nullptr) {
        cout << "Siguiendo a: " << usuarioSeguido->getNickname() << endl;
    } else {
        cout << "No sigue a ningún usuario" << endl;
    }
}

std::string Usuario::obtenerInfoResumida() const
{
    return nickname + " (" + tipoMembresia + ") - " + ciudad + ", " + pais;
}

// ============================================================================
// MÉTODOS DE NAVEGACIÓN EN HISTORIAL
// ============================================================================

bool Usuario::puedeRetroceder() const {
    return esPremium() && posicionActualHistorial > 0;
}

bool Usuario::puedeAvanzar() const {
    return esPremium() && posicionActualHistorial < cantidadEnHistorial - 1;
}

Cancion* Usuario::obtenerCancionAnterior() {
    if (!puedeRetroceder()) {
        cout << "No hay canciones anteriores en el historial." << endl;
        return nullptr;
    }
    posicionActualHistorial--;
    cout << "Retrocediendo a canción anterior..." << endl;
    return historialReproduccion[posicionActualHistorial];
}

Cancion* Usuario::obtenerCancionSiguiente() {
    if (!puedeAvanzar()) {
        cout << "No hay más canciones en el historial." << endl;
        return nullptr;
    }
    posicionActualHistorial++;
    cout << "Avanzando a siguiente canción..." << endl;
    return historialReproduccion[posicionActualHistorial];
}

void Usuario::agregarAlHistorial(Cancion* cancion) {
    if (!esPremium() || historialReproduccion == nullptr) {
        return;
    }

    // Si estamos en medio del historial, truncamos
    if (posicionActualHistorial < cantidadEnHistorial - 1) {
        cantidadEnHistorial = posicionActualHistorial + 1;
    }

    // Si el historial está lleno, desplazamos
    if (cantidadEnHistorial >= MAX_HISTORIAL) {
        for (int i = 0; i < MAX_HISTORIAL - 1; ++i) {
            historialReproduccion[i] = historialReproduccion[i + 1];
        }
        cantidadEnHistorial = MAX_HISTORIAL - 1;
    }

    // Agregar nueva canción
    historialReproduccion[cantidadEnHistorial] = cancion;
    posicionActualHistorial = cantidadEnHistorial;
    cantidadEnHistorial++;
}

void Usuario::limpiarHistorial() {
    if (historialReproduccion != nullptr) {
        for (int i = 0; i < MAX_HISTORIAL; ++i) {
            historialReproduccion[i] = nullptr;
        }
    }
    cantidadEnHistorial = 0;
    posicionActualHistorial = -1;
}

int Usuario::getCantidadEnHistorial() const {
    return cantidadEnHistorial;
}

// ============================================================================
// CONTROL DE REPRODUCCIÓN
// ============================================================================

void Usuario::iniciarReproduccion(Cancion* cancion) {
    if (cancion == nullptr) {
        cout << "Error: Canción inválida para reproducir." << endl;
        return;
    }

    cancionActual = cancion;
    reproduciendo = true;

    // Agregar al historial (solo premium)
    if (esPremium()) {
        agregarAlHistorial(cancion);
    }

    // Incrementar contador para publicidad (solo estándar)
    if (!esPremium()) {
        incrementarContadorPublicidad();
    }

    cout << "Reproduciendo: " << cancion->obtenerNombre() << endl;
}

void Usuario::detenerReproduccion() {
    if (!reproduciendo) {
        cout << "No hay reproducción en curso." << endl;
        return;
    }
    cout << "Deteniendo reproducción..." << endl;
    reproduciendo = false;
}

bool Usuario::estaReproduciendo() const {
    return reproduciendo;
}

Cancion* Usuario::getCancionActual() const {
    return cancionActual;
}

// ============================================================================
// CONTROL DE PUBLICIDAD
// ============================================================================

bool Usuario::debeMostrarPublicidad() const {
    // Usuarios estándar ven publicidad cada 2 canciones
    return !esPremium() && (contadorCancionesReproducidas % 2 == 0) && (contadorCancionesReproducidas > 0);
}

void Usuario::incrementarContadorPublicidad() {
    contadorCancionesReproducidas++;
}

void Usuario::reiniciarContadorPublicidad() {
    contadorCancionesReproducidas = 0;
}

int Usuario::getContadorCancionesReproducidas() const {
    return contadorCancionesReproducidas;
}
