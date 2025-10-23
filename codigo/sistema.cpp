#include "sistema.h"
#include "catalogo.h"
#include "usuario.h"
#include "mensaje_publicitario.h"
#include "cancion.h"
#include "album.h"
#include "artista.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Sistema::Sistema()
    : catalogo(new Catalogo()),
    usuarios(nullptr),
    cantidadUsuarios(0),
    capacidadUsuarios(0),
    mensajesPublicitarios(nullptr),
    cantidadMensajes(0),
    capacidadMensajes(0),
    usuarioActual(nullptr)
{
    srand(time(nullptr)); // Para generación de números aleatorios
    cargarDatos(); // Cargar datos iniciales
}

Sistema::~Sistema()
{
    // Eliminar catálogo
    delete catalogo;

    // Eliminar usuarios
    for (int i = 0; i < cantidadUsuarios; ++i) {
        delete usuarios[i];
    }
    delete[] usuarios;

    // Eliminar mensajes publicitarios
    for (int i = 0; i < cantidadMensajes; ++i) {
        delete mensajesPublicitarios[i];
    }
    delete[] mensajesPublicitarios;
}

void Sistema::aumentarCapacidadUsuarios()
{
    int nuevaCapacidad = (capacidadUsuarios == 0) ? 5 : capacidadUsuarios * 2;

    Usuario** nuevoArreglo = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; ++i) {
        nuevoArreglo[i] = usuarios[i];
    }

    delete[] usuarios;
    usuarios = nuevoArreglo;
    capacidadUsuarios = nuevaCapacidad;
}

void Sistema::aumentarCapacidadMensajes()
{
    int nuevaCapacidad = (capacidadMensajes == 0) ? 10 : capacidadMensajes * 2;

    MensajePublicitario** nuevoArreglo = new MensajePublicitario*[nuevaCapacidad];

    for (int i = 0; i < cantidadMensajes; ++i) {
        nuevoArreglo[i] = mensajesPublicitarios[i];
    }

    delete[] mensajesPublicitarios;
    mensajesPublicitarios = nuevoArreglo;
    capacidadMensajes = nuevaCapacidad;
}

void Sistema::cargarDatos()
{
    // TODO: Implementar carga desde archivos
    // Por ahora creamos algunos datos de ejemplo

    // Crear usuarios de ejemplo
    registrarUsuario("juan_perez", "premium", "Bogota", "Colombia", 20241015);
    registrarUsuario("maria_gomez", "estandar", "Medellin", "Colombia", 20241010);
    registrarUsuario("carlos_li", "premium", "Cali", "Colombia", 20241005);
}

void Sistema::guardarDatos()
{
    // TODO: Implementar guardado a archivos
}

// Gestión de usuarios
bool Sistema::iniciarSesion(const std::string& nickname)
{
    Usuario* usuario = buscarUsuario(nickname);
    if (usuario != nullptr) {
        usuarioActual = usuario;
        cout << "Sesión iniciada como: " << nickname << endl;
        return true;
    }
    cout << "Usuario no encontrado: " << nickname << endl;
    return false;
}

void Sistema::cerrarSesion()
{
    usuarioActual = nullptr;
    cout << "Sesión cerrada." << endl;
}

bool Sistema::registrarUsuario(const std::string& nickname, const std::string& tipoMembresia,
                               const std::string& ciudad, const std::string& pais, int fechaInscripcion)
{
    // Verificar que el nickname no exista
    if (buscarUsuario(nickname) != nullptr) {
        return false;
    }

    // Aumentar capacidad si es necesario
    if (cantidadUsuarios == capacidadUsuarios) {
        aumentarCapacidadUsuarios();
    }

    // Crear nuevo usuario
    usuarios[cantidadUsuarios] = new Usuario(nickname, tipoMembresia, ciudad, pais, fechaInscripcion);
    cantidadUsuarios++;

    return true;
}

Usuario* Sistema::buscarUsuario(const std::string& nickname) const
{
    for (int i = 0; i < cantidadUsuarios; ++i) {
        if (usuarios[i] != nullptr && usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}

Usuario* Sistema::getUsuarioActual() const { return usuarioActual; }
int Sistema::getCantidadUsuarios() const { return cantidadUsuarios; }

// Gestión de mensajes publicitarios
void Sistema::agregarMensajePublicitario(MensajePublicitario* mensaje)
{
    if (mensaje == nullptr) return;

    if (cantidadMensajes == capacidadMensajes) {
        aumentarCapacidadMensajes();
    }

    mensajesPublicitarios[cantidadMensajes] = mensaje;
    cantidadMensajes++;
}

MensajePublicitario* Sistema::obtenerMensajeAleatorio() const
{
    if (cantidadMensajes == 0) return nullptr;

    int indice = rand() % cantidadMensajes;
    return mensajesPublicitarios[indice];
}

int Sistema::getCantidadMensajes() const { return cantidadMensajes; }

// Funcionalidades principales
void Sistema::reproduccionAleatoria()
{
    if (usuarioActual == nullptr) {
        cout << "Debe iniciar sesión primero." << endl;
        return;
    }

    if (catalogo->obtenerCantidadArtistas() == 0) {
        cout << "No hay artistas en el catálogo." << endl;
        return;
    }

    cout << "=== REPRODUCCIÓN ALEATORIA ===" << endl;

    // Contador de métricas
    int iteraciones = 0;

    // Reproducir K=5 canciones (requerimiento del enunciado)
    for (int i = 0; i < 5; ++i) {
        iteraciones++;

        // Seleccionar artista aleatorio
        int indiceArtista = rand() % catalogo->obtenerCantidadArtistas();
        Artista* artista = catalogo->obtenerArtistaEn(indiceArtista);
        iteraciones++;

        if (artista != nullptr && artista->obtenerCantidadAlbums() > 0) {
            // Seleccionar álbum aleatorio
            int indiceAlbum = rand() % artista->obtenerCantidadAlbums();
            Album* album = artista->obtenerAlbumEn(indiceAlbum);
            iteraciones++;

            if (album != nullptr && album->obtenerCantidadCanciones() > 0) {
                // Seleccionar canción aleatoria
                int indiceCancion = rand() % album->obtenerCantidadCanciones();
                Cancion* cancion = album->obtenerCancionEn(indiceCancion);
                iteraciones++;

                if (cancion != nullptr) {
                    // Mostrar información de reproducción
                    cout << "\n--- Canción " << (i + 1) << " ---" << endl;
                    cout << "Artista: " << artista->obtenerNombre() << endl;
                    cout << "Álbum: " << album->obtenerNombre() << endl;
                    cout << "Canción: " << cancion->obtenerNombre() << endl;
                    cout << "Duración: " << cancion->obtenerDuracion() << " min" << endl;
                    cout << "Portada: " << album->obtenerPortada() << endl;

                    // Mostrar ruta de audio según calidad
                    bool altaCalidad = usuarioActual->esPremium();
                    cout << "Audio: " << cancion->obtenerRuta(altaCalidad) << endl;

                    // Mostrar publicidad para usuarios estándar (cada 2 canciones)
                    if (!usuarioActual->esPremium() && (i + 1) % 2 == 0) {
                        MensajePublicitario* mensaje = obtenerMensajeAleatorio();
                        if (mensaje != nullptr) {
                            cout << "\n[MENSAJE PUBLICITARIO]" << endl;
                            cout << mensaje->getMensaje() << endl;
                        }
                    }

                    // Incrementar reproducciones
                    cancion->aumentarReproducciones();

                    // Simular reproducción (3 segundos - requerimiento)
                    cout << "Reproduciendo...";
                    // TODO: Implementar chrono para 3 segundos

                    cout << " [COMPLETADO]" << endl;
                }
            }
        }
    }

    // Mostrar métricas
    mostrarMetricas(iteraciones);
}

void Sistema::gestionarFavoritos()
{
    if (usuarioActual == nullptr) {
        cout << "Debe iniciar sesión primero." << endl;
        return;
    }

    if (!usuarioActual->esPremium()) {
        cout << "Esta funcionalidad es solo para usuarios premium." << endl;
        return;
    }

    cout << "=== GESTIÓN DE FAVORITOS ===" << endl;
    cout << "1. Agregar canción a favoritos" << endl;
    cout << "2. Eliminar canción de favoritos" << endl;
    cout << "3. Ver mis favoritos" << endl;
    cout << "Seleccione opción: ";

    int opcion;
    cin >> opcion;

    int iteraciones = 0;

    switch (opcion) {
    case 1: {
        cout << "Ingrese ID de la canción: ";
        int idCancion;
        cin >> idCancion;

        Cancion* cancion = buscarCancionPorId(idCancion);
        iteraciones++;

        if (cancion != nullptr) {
            if (usuarioActual->agregarFavorito(cancion)) {
                cout << "Canción agregada a favoritos." << endl;
            } else {
                cout << "No se pudo agregar la canción (¿ya está en favoritos?)." << endl;
            }
        } else {
            cout << "Canción no encontrada." << endl;
        }
        break;
    }
    case 2: {
        cout << "Ingrese ID de la canción a eliminar: ";
        int idCancion;
        cin >> idCancion;

        if (usuarioActual->eliminarFavorito(idCancion)) {
            cout << "Canción eliminada de favoritos." << endl;
        } else {
            cout << "Canción no encontrada en favoritos." << endl;
        }
        break;
    }
    case 3: {
        int cantidad = usuarioActual->getCantidadFavoritos();
        cout << "Tienes " << cantidad << " canciones en favoritos:" << endl;

        for (int i = 0; i < cantidad; ++i) {
            Cancion* cancion = usuarioActual->getFavoritoEn(i);
            if (cancion != nullptr) {
                cout << (i + 1) << ". " << cancion->obtenerNombre()
                << " (ID: " << cancion->obtenerId() << ")" << endl;
            }
            iteraciones++;
        }
        break;
    }
    default:
        cout << "Opción inválida." << endl;
    }

    mostrarMetricas(iteraciones);
}

void Sistema::seguirListaFavoritos(const std::string& nickname)
{
    if (usuarioActual == nullptr) {
        cout << "Debe iniciar sesión primero." << endl;
        return;
    }

    if (!usuarioActual->esPremium()) {
        cout << "Esta funcionalidad es solo para usuarios premium." << endl;
        return;
    }

    Usuario* usuarioASeguir = buscarUsuario(nickname);
    int iteraciones = 1; // Por la búsqueda

    if (usuarioASeguir != nullptr && usuarioASeguir->esPremium()) {
        usuarioActual->seguirUsuario(usuarioASeguir);
        usuarioActual->combinarConListaDe(usuarioASeguir);
        cout << "Ahora sigues la lista de favoritos de: " << nickname << endl;
        cout << "Se han combinado " << usuarioASeguir->getCantidadFavoritos()
             << " canciones a tu lista." << endl;
    } else {
        cout << "Usuario no encontrado o no es premium." << endl;
    }

    mostrarMetricas(iteraciones);
}

void Sistema::ejecutarListaFavoritos()
{
    if (usuarioActual == nullptr) {
        cout << "Debe iniciar sesión primero." << endl;
        return;
    }

    if (!usuarioActual->esPremium()) {
        cout << "Esta funcionalidad es solo para usuarios premium." << endl;
        return;
    }

    int cantidadFavoritos = usuarioActual->getCantidadFavoritos();
    if (cantidadFavoritos == 0) {
        cout << "No tienes canciones en favoritos." << endl;
        return;
    }

    cout << "=== EJECUTAR LISTA DE FAVORITOS ===" << endl;
    cout << "¿Reproducir en orden original (1) o aleatorio (2)? ";

    int opcion;
    cin >> opcion;

    int iteraciones = 0;

    // TODO: Implementar reproducción completa con control de navegación
    // Por ahora mostramos las canciones que se reproducirían

    cout << "Reproduciendo " << cantidadFavoritos << " canciones:" << endl;

    for (int i = 0; i < cantidadFavoritos; ++i) {
        Cancion* cancion = usuarioActual->getFavoritoEn(i);
        if (cancion != nullptr) {
            Album* album = buscarAlbumPorCancionId(cancion->obtenerId());
            iteraciones++;

            cout << "\n" << (i + 1) << ". " << cancion->obtenerNombre() << endl;
            if (album != nullptr) {
                cout << "   Álbum: " << album->obtenerNombre() << endl;
                cout << "   Portada: " << album->obtenerPortada() << endl;
            }
            cout << "   Audio: " << cancion->obtenerRuta(usuarioActual->esPremium()) << endl;

            // Simular reproducción
            cout << "   [REPRODUCIENDO...]" << endl;
        }
        iteraciones++;
    }

    mostrarMetricas(iteraciones);
}

// Métricas
void Sistema::mostrarMetricas(int iteraciones) const
{
    cout << "\n=== MÉTRICAS ===" << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria consumida: " << calcularMemoriaTotal() << " bytes" << endl;
}

size_t Sistema::calcularMemoriaTotal() const
{
    size_t memoria = 0;

    // Memoria del sistema base
    memoria += sizeof(Sistema);

    // Memoria de usuarios
    memoria += sizeof(Usuario*) * capacidadUsuarios;
    for (int i = 0; i < cantidadUsuarios; ++i) {
        if (usuarios[i] != nullptr) {
            memoria += sizeof(Usuario);
            memoria += sizeof(Cancion*) * 10000; // Capacidad máxima de favoritos
        }
    }

    // Memoria de mensajes publicitarios
    memoria += sizeof(MensajePublicitario*) * capacidadMensajes;
    for (int i = 0; i < cantidadMensajes; ++i) {
        if (mensajesPublicitarios[i] != nullptr) {
            memoria += sizeof(MensajePublicitario);
        }
    }

    // Memoria del catálogo (simplificado)
    memoria += sizeof(Catalogo);

    return memoria;
}

// Búsquedas auxiliares
Cancion* Sistema::buscarCancionPorId(int id) const
{
    return catalogo->buscarCancionPorId(id);
}

Album* Sistema::buscarAlbumPorCancionId(int id) const
{
    return catalogo->buscarAlbumPorCancionId(id);
}

Artista* Sistema::buscarArtistaPorCancionId(int id) const
{
    // Implementar búsqueda similar a las del catálogo
    // Por simplicidad, usamos el catálogo existente
    Album* album = catalogo->buscarAlbumPorCancionId(id);
    if (album != nullptr) {
        // Buscar qué artista tiene este álbum
        for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
            Artista* artista = catalogo->obtenerArtistaEn(i);
            if (artista != nullptr) {
                for (int j = 0; j < artista->obtenerCantidadAlbums(); ++j) {
                    if (artista->obtenerAlbumEn(j) == album) {
                        return artista;
                    }
                }
            }
        }
    }
    return nullptr;
}

Catalogo* Sistema::getCatalogo() const { return catalogo; }
