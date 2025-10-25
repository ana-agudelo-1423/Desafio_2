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
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

// ======= CONSTRUCTOR / DESTRUCTOR =======

Sistema::Sistema()
    : catalogo(new Catalogo()),
    usuarios(nullptr),
    cantidadUsuarios(0),
    capacidadUsuarios(0),
    mensajesPublicitarios(nullptr),
    cantidadMensajes(0),
    capacidadMensajes(0)
{
    srand(time(nullptr));
    cargarDatos();
    cargarCatalogo();
}

Sistema::~Sistema()
{
    guardarDatos();

    delete catalogo;

    for (int i = 0; i < cantidadUsuarios; ++i)
        delete usuarios[i];
    delete[] usuarios;

    for (int i = 0; i < cantidadMensajes; ++i)
        delete mensajesPublicitarios[i];
    delete[] mensajesPublicitarios;
}

// ======= GESTIÓN DE MEMORIA =======

void Sistema::aumentarCapacidadUsuarios() {
    int nuevaCapacidad = (capacidadUsuarios == 0) ? 5 : capacidadUsuarios * 2;
    Usuario** nuevo = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; ++i)
        nuevo[i] = usuarios[i];

    delete[] usuarios;
    usuarios = nuevo;
    capacidadUsuarios = nuevaCapacidad;
}

void Sistema::aumentarCapacidadMensajes() {
    int nuevaCapacidad = (capacidadMensajes == 0) ? 10 : capacidadMensajes * 2;
    MensajePublicitario** nuevo = new MensajePublicitario*[nuevaCapacidad];

    for (int i = 0; i < cantidadMensajes; ++i)
        nuevo[i] = mensajesPublicitarios[i];

    delete[] mensajesPublicitarios;
    mensajesPublicitarios = nuevo;
    capacidadMensajes = nuevaCapacidad;
}

// ======= CARGA / GUARDADO GENERAL =======

void Sistema::cargarDatos() {
    cargarUsuariosDesdeArchivo();
    cargarMensajesDesdeArchivo();
    //cout << " Datos cargados correctamente.\n";
}

void Sistema::guardarDatos() {
    guardarUsuariosEnArchivo();
    guardarMensajesEnArchivo();
    //cout << " Datos guardados correctamente.\n";
}

// ======= CARGA / GUARDADO DE USUARIOS =======

void Sistema::cargarUsuariosDesdeArchivo() {
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string nick, tipo, ciudad, pais, fechaStr;
            getline(ss, nick, ';');
            getline(ss, tipo, ';');
            getline(ss, ciudad, ';');
            getline(ss, pais, ';');
            getline(ss, fechaStr, ';');
            int fecha = stoi(fechaStr);
            agregarUsuario(new Usuario(nick, tipo, ciudad, pais, fecha));
        }
        archivo.close();
    } else {
        //cout << "[Aviso] No se encontro 'usuarios.txt'. Se usaran datos de ejemplo.\n";
        agregarUsuario(new Usuario("juan_perez", "premium", "Bogota", "Colombia", 20241015));
        agregarUsuario(new Usuario("maria_gomez", "estandar", "Medellin", "Colombia", 20241010));
        agregarUsuario(new Usuario("carlos_li", "premium", "Cali", "Colombia", 20241005));
    }
}

void Sistema::guardarUsuariosEnArchivo() {
    ofstream archivo("usuarios.txt", ios::trunc);
    if (archivo.is_open()) {
        for (int i = 0; i < cantidadUsuarios; ++i) {
            Usuario* u = usuarios[i];
            if (u) {
                archivo << u->getNickname() << ";"
                        << u->getTipoMembresia() << ";"
                        << u->getCiudad() << ";"
                        << u->getPais() << ";"
                        << u->getFechaInscripcion() << "\n";
            }
        }
        archivo.close();
    }
}

// ======= CARGA / GUARDADO DE MENSAJES =======

void Sistema::cargarMensajesDesdeArchivo() {
    ifstream archivo("mensajes.txt");
    if (archivo.is_open()) {
        string linea;
        int idCounter = 1;
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string texto, categoria;
            getline(ss, texto, ';');
            getline(ss, categoria, ';');
            agregarMensajePublicitario(new MensajePublicitario(idCounter, texto, categoria));
            idCounter++;
        }
        archivo.close();
    } else {
       // cout << "[Aviso] No se encontro 'mensajes.txt'. Se usaran mensajes de ejemplo.\n";
        agregarMensajePublicitario(new MensajePublicitario(1, "Disfruta de la mejor música con UdeATunes.", "C"));
        agregarMensajePublicitario(new MensajePublicitario(2, "Hazte premium y escucha sin anuncios.", "B"));
        agregarMensajePublicitario(new MensajePublicitario(3, "Promoción limitada: 50% de descuento en membresía anual.", "AAA"));
    }
}

void Sistema::guardarMensajesEnArchivo() {
    ofstream archivo("mensajes.txt", ios::trunc);
    if (archivo.is_open()) {
        for (int i = 0; i < cantidadMensajes; ++i) {
            MensajePublicitario* m = mensajesPublicitarios[i];
            if (m)
                archivo << m->getMensaje() << ";" << m->getCategoria() << "\n";
        }
        archivo.close();
    }
}

// ======= CARGA DE CATÁLOGO DESDE ARCHIVOS =======

void Sistema::cargarArtistasDesdeArchivo() {
    ifstream archivo("Artistas.txt");
    if (!archivo.is_open()) {
      //  cout << " No se pudo abrir Artistas.txt. Usando datos de ejemplo." << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar header

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, edadStr, nombre, pais;

        getline(ss, idStr, ';');
        getline(ss, edadStr, ';');
        getline(ss, nombre, ';');
        getline(ss, pais, ';');

        int id = stoi(idStr);
        int edad = stoi(edadStr);

        Artista* artista = new Artista(id, edad, nombre, pais);
        artista->setSeguidores(rand() % 10000000 + 1000000);
        artista->setPosicion(rand() % 100 + 1);

        catalogo->agregarArtista(artista);
        cout << " Cargado artista: " << nombre << " (" << pais << ")" << endl;
    }
    archivo.close();
}

void Sistema::cargarAlbumesDesdeArchivo() {
    ifstream archivo("albums.txt");
    if (!archivo.is_open()) {
       // cout << " No se pudo abrir albums.txt. Usando datos de ejemplo." << endl;
        cargarAlbumesEjemplo();
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar header

    int albumesCargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, nombre, fechaStr, sello, portada, artistaStr;

        getline(ss, idStr, ';');
        getline(ss, nombre, ';');
        getline(ss, fechaStr, ';');
        getline(ss, sello, ';');
        getline(ss, portada, ';');
        getline(ss, artistaStr, ';');

        int id = stoi(idStr);
        int fecha = stoi(fechaStr);
        int idArtista = stoi(artistaStr);

        Album* album = new Album(id, nombre, fecha, sello, portada);

        bool artistaEncontrado = false;
        for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
            Artista* artista = catalogo->obtenerArtistaEn(i);
            if (artista && artista->obtenerId() == idArtista) {
                artista->agregarAlbum(album);
                artistaEncontrado = true;
                albumesCargados++;
                cout << " Álbum '" << nombre << "' agregado a " << artista->obtenerNombre() << endl;
                break;
            }
        }

        if (!artistaEncontrado) {
            cout << " No se encontró artista con ID " << idArtista << " para el álbum '" << nombre << "'" << endl;
            delete album;
        }
    }
    archivo.close();

    cout << " Se cargaron " << albumesCargados << " albumes correctamente." << endl;
}

void Sistema::cargarAlbumesEjemplo() {
    Artista* artista1 = catalogo->obtenerArtistaEn(0);
    if (artista1) {
        Album* album1 = new Album(101, "Laundry Service", 20011113, "Epic Records", "shakira_laundry.jpg");
        artista1->agregarAlbum(album1);
    }

    Artista* artista2 = catalogo->obtenerArtistaEn(4);
    if (artista2) {
        Album* album2 = new Album(105, "Un Verano Sin Ti", 20220506, "Rimas Entertainment", "badbunny_verano.jpg");
        artista2->agregarAlbum(album2);
    }
}

void Sistema::cargarCancionesDesdeArchivo() {
    ifstream archivo("Canciones.txt");
    if (!archivo.is_open()) {
       // cout << " No se pudo abrir Canciones.txt" << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar header

    int cancionesCargadas = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, albumStr, duracionStr, nombre, ruta128, ruta320;

        getline(ss, idStr, ';');
        getline(ss, albumStr, ';');
        getline(ss, duracionStr, ';');
        getline(ss, nombre, ';');
        getline(ss, ruta128, ';');
        getline(ss, ruta320, ';');

        int id = stoi(idStr);
        int albumId = stoi(albumStr);
        float duracion = stof(duracionStr) / 60.0f;

        Cancion* cancion = new Cancion(id, duracion, nombre, ruta128, ruta320);

        bool albumEncontrado = false;
        for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
            Artista* artista = catalogo->obtenerArtistaEn(i);
            if (artista) {
                for (int j = 0; j < artista->obtenerCantidadAlbums(); ++j) {
                    Album* album = artista->obtenerAlbumEn(j);
                    if (album && album->obtenerId() == albumId) {
                        album->agregarCancion(cancion);
                        albumEncontrado = true;
                        cancionesCargadas++;
                        cout << " Canción '" << nombre << "' agregada a "
                             << album->obtenerNombre() << " - " << artista->obtenerNombre() << endl;
                        break;
                    }
                }
                if (albumEncontrado) break;
            }
        }

        if (!albumEncontrado) {
            cout << " No se encontró álbum con ID " << albumId << " para la canción '" << nombre << "'" << endl;
            delete cancion;
        }
    }
    archivo.close();

    cout << " Se cargaron " << cancionesCargadas << " canciones correctamente." << endl;
}

void Sistema::cargarCreditosDesdeArchivo() {
    ifstream archivo("Creditos.txt");
    if (!archivo.is_open()) {
       // cout << " No se pudo abrir Creditos.txt" << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Saltar header

    int creditosCargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, nombre, rol;

        getline(ss, idStr, ';');
        getline(ss, nombre, ';');
        getline(ss, rol, ';');

        int id = stoi(idStr);
        creditosCargados++;
        cout << " Cargado crédito: " << nombre << " - " << rol << endl;
    }
    archivo.close();

    cout << " Se cargaron " << creditosCargados << " créditos correctamente." << endl;
}

void Sistema::cargarCatalogo() {


    cargarArtistasDesdeArchivo();
    cargarAlbumesDesdeArchivo();
    cargarCancionesDesdeArchivo();
    cargarCreditosDesdeArchivo();

    int totalAlbumes = 0;
    int totalCanciones = 0;
    for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
        Artista* artista = catalogo->obtenerArtistaEn(i);
        if (artista) {
            totalAlbumes += artista->obtenerCantidadAlbums();
            for (int j = 0; j < artista->obtenerCantidadAlbums(); ++j) {
                Album* album = artista->obtenerAlbumEn(j);
                if (album) {
                    totalCanciones += album->obtenerCantidadCanciones();
                }
            }
        }
    }
}

// ======= GESTIÓN DE USUARIOS =======

void Sistema::agregarUsuario(Usuario* nuevoUsuario) {
    if (!nuevoUsuario) return;
    if (cantidadUsuarios == capacidadUsuarios) aumentarCapacidadUsuarios();
    usuarios[cantidadUsuarios++] = nuevoUsuario;
}

Usuario* Sistema::buscarUsuario(const string& nick) const {
    for (int i = 0; i < cantidadUsuarios; ++i)
        if (usuarios[i] && usuarios[i]->getNickname() == nick)
            return usuarios[i];
    return nullptr;
}

// ======= GESTIÓN DE MENSAJES =======

void Sistema::agregarMensajePublicitario(MensajePublicitario* m) {
    if (!m) return;
    if (cantidadMensajes == capacidadMensajes) aumentarCapacidadMensajes();
    mensajesPublicitarios[cantidadMensajes++] = m;
}

MensajePublicitario* Sistema::obtenerMensajeAleatorio() const {
    if (cantidadMensajes == 0) return nullptr;
    int indice = rand() % cantidadMensajes;
    return mensajesPublicitarios[indice];
}

void Sistema::mostrarEstadisticasMensajes() const {
    cout << "\n=== ESTADÍSTICAS DE MENSAJES PUBLICITARIOS ===" << endl;
    if (cantidadMensajes == 0) {
        cout << "No hay mensajes publicitarios cargados." << endl;
        return;
    }

    for (int i = 0; i < cantidadMensajes; ++i) {
        MensajePublicitario* m = mensajesPublicitarios[i];
        if (m) {
            cout << "ID: " << m->getId()
            << " | Categoría: " << m->getCategoria()
            << " | Prioridad: " << m->getPrioridad()
            << " | Veces mostrado: " << m->getVecesMostrado() << endl;
        }
    }
}

// ======= REPRODUCCIÓN ALEATORIA =======

void Sistema::reproduccionAleatoria(Usuario* usuarioActual) {
    if (!usuarioActual) {
        cout << "❌ Debe iniciar sesión primero.\n";
        return;
    }

    if (catalogo->obtenerCantidadArtistas() == 0) {
        cout << "❌ No hay artistas en el catálogo.\n";
        return;
    }

    cout << "\n=== REPRODUCCIÓN ALEATORIA ===" << endl;
    cout << "👤 Usuario: " << usuarioActual->getNickname();
    cout << " (" << (usuarioActual->esPremium() ? "PREMIUM 🎵" : "ESTÁNDAR 🔊") << ")" << endl;

    int iteraciones = 0;
    const int K = 5;

    for (int i = 0; i < K; ++i) {
        iteraciones++;

        int indiceArtista = rand() % catalogo->obtenerCantidadArtistas();
        Artista* artista = catalogo->obtenerArtistaEn(indiceArtista);
        iteraciones++;

        if (artista && artista->obtenerCantidadAlbums() > 0) {
            int indiceAlbum = rand() % artista->obtenerCantidadAlbums();
            Album* album = artista->obtenerAlbumEn(indiceAlbum);
            iteraciones++;

            if (album && album->obtenerCantidadCanciones() > 0) {
                int indiceCancion = rand() % album->obtenerCantidadCanciones();
                Cancion* cancion = album->obtenerCancionEn(indiceCancion);
                iteraciones++;

                if (cancion) {
                    cout << "\n🎵 Canción " << (i + 1) << "/" << K << endl;
                    cout << "👤 Artista: " << artista->obtenerNombre() << endl;
                    cout << "💿 Álbum: " << album->obtenerNombre() << endl;
                    cout << "🎶 Canción: " << cancion->obtenerNombre() << endl;
                    cout << "⏱️ Duración: " << cancion->obtenerDuracion() << " min" << endl;
                    cout << "🖼️ Portada: " << album->obtenerPortada() << endl;

                    bool altaCalidad = usuarioActual->esPremium();
                    cout << "🔊 Audio: " << cancion->obtenerRuta(altaCalidad) << endl;

                    if (!usuarioActual->esPremium() && (i + 1) % 2 == 0) {
                        MensajePublicitario* mensaje = obtenerMensajeAleatorio();
                        if (mensaje) {
                            cout << "\n📢 PUBLICIDAD:" << endl;
                            mensaje->mostrarMensaje();
                        }
                    }

                    cancion->aumentarReproducciones();

                    cout << "▶️ Reproduciendo...";
                    this_thread::sleep_for(chrono::seconds(2));
                    cout << " ✅ Completado" << endl;
                }
            }
        }
    }

    mostrarMetricas(iteraciones);
}

// ======= BÚSQUEDAS =======

Cancion* Sistema::buscarCancionPorId(int id) const {
    for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
        Artista* artista = catalogo->obtenerArtistaEn(i);
        if (artista) {
            for (int j = 0; j < artista->obtenerCantidadAlbums(); ++j) {
                Album* album = artista->obtenerAlbumEn(j);
                if (album) {
                    for (int k = 0; k < album->obtenerCantidadCanciones(); ++k) {
                        Cancion* cancion = album->obtenerCancionEn(k);
                        if (cancion && cancion->obtenerId() == id) {
                            return cancion;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

Album* Sistema::buscarAlbumPorCancionId(int id) const {
    for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
        Artista* artista = catalogo->obtenerArtistaEn(i);
        if (artista) {
            for (int j = 0; j < artista->obtenerCantidadAlbums(); ++j) {
                Album* album = artista->obtenerAlbumEn(j);
                if (album) {
                    for (int k = 0; k < album->obtenerCantidadCanciones(); ++k) {
                        Cancion* cancion = album->obtenerCancionEn(k);
                        if (cancion && cancion->obtenerId() == id) {
                            return album;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

Artista* Sistema::buscarArtistaPorCancionId(int id) const {
    Album* album = buscarAlbumPorCancionId(id);
    if (album) {
        for (int i = 0; i < catalogo->obtenerCantidadArtistas(); ++i) {
            Artista* artista = catalogo->obtenerArtistaEn(i);
            if (artista) {
                for (int j = 0; j < artista->obtenerCantidadAlbums(); ++j)
                    if (artista->obtenerAlbumEn(j) == album)
                        return artista;
            }
        }
    }
    return nullptr;
}

// ======= MÉTRICAS =======

void Sistema::mostrarMetricas(int iteraciones) const {
    cout << "\n=== MÉTRICAS ===" << endl;
    cout << "🔄 Iteraciones realizadas: " << iteraciones << endl;
    cout << "💾 Memoria consumida: " << calcularMemoriaTotal() << " bytes" << endl;
}

size_t Sistema::calcularMemoriaTotal() const {
    size_t memoria = sizeof(Sistema);
    memoria += sizeof(Usuario*) * capacidadUsuarios;
    for (int i = 0; i < cantidadUsuarios; ++i)
        if (usuarios[i]) memoria += sizeof(Usuario);
    memoria += sizeof(MensajePublicitario*) * capacidadMensajes;
    for (int i = 0; i < cantidadMensajes; ++i)
        if (mensajesPublicitarios[i]) memoria += sizeof(MensajePublicitario);
    memoria += sizeof(Catalogo);
    return memoria;
}

// ======= GETTER =======

Catalogo* Sistema::getCatalogo() const {
    return catalogo;
}
