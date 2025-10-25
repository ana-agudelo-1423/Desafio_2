#include "sistema.h"
#include "usuario.h"
#include <iostream>
#include <limits>
using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerOpcion() {
    int opcion;
    while (!(cin >> opcion)) {
        cout << " Entrada invalida. Ingrese un numero: ";
        limpiarBuffer();
    }
    limpiarBuffer();
    return opcion;
}

string leerString(const string& mensaje) {
    string input;
    cout << mensaje;
    getline(cin, input);
    return input;
}

void mostrarMenuPrincipal() {
    cout << "\n===  BIENVENIDO A UdeATunes  ===" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Registrar nuevo usuario" << endl;
    cout << "3. Informacion de planes" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void mostrarInformacionPlanes() {
    cout << "\n=== PLANES DISPONIBLES ===" << endl;
    cout << "\n PLAN ESTANDAR (Gratis)" << endl;
    cout << " - Escucha canciones a 128 kbps" << endl;
    cout << " - Cada 2 canciones veras un mensaje publicitario" << endl;
    cout << " - No puedes crear ni seguir listas de favoritos" << endl;

    cout << "\n PLAN PREMIUM ($19.900 / mes)" << endl;
    cout << " - Calidad de audio 320 kbps" << endl;
    cout << " - Sin publicidad" << endl;
    cout << " - Crea y sigue listas de favoritos (hasta 10.000 canciones)" << endl;
    cout << " - Acceso a controles: siguiente, anterior y repetir" << endl;
    cout << "\n=====================================\n";
}

void menuUsuario(Sistema& sistema, Usuario* usuario) {
    int opcion = 0;
    do {
        cout << "\n=== MENU DE USUARIO - " << usuario->getNickname();
        cout << " (" << (usuario->esPremium() ? "PREMIUM 🔸" : "ESTÁNDAR 🔹") << ") ===" << endl;
        cout << "1. Reproducción aleatoria" << endl;
        cout << "2. Ver catálogo musical" << endl;
        cout << "3. Buscar canción por ID" << endl;
        cout << "4. Ver estadísticas de mensajes" << endl;
        cout << "5. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";

        opcion = leerOpcion();

        switch (opcion) {
        case 1:
            sistema.reproduccionAleatoria(usuario);
            break;

        case 2: {
            Catalogo* c = sistema.getCatalogo();
            cout << "\n=== CATALOGO COMPLETO ===" << endl;
            for (int i = 0; i < c->obtenerCantidadArtistas(); ++i) {
                Artista* a = c->obtenerArtistaEn(i);
                cout << "\n " << a->obtenerNombre() << " (" << a->obtenerPaisOrigen() << ")" << endl;

                for (int j = 0; j < a->obtenerCantidadAlbums(); ++j) {
                    Album* album = a->obtenerAlbumEn(j);
                    cout << "    " << album->obtenerNombre() << endl;

                    for (int k = 0; k < album->obtenerCantidadCanciones(); ++k) {
                        Cancion* cancion = album->obtenerCancionEn(k);
                        cout << "      ▶️ " << cancion->obtenerNombre()
                             << " [" << cancion->obtenerDuracion() << " min]"
                             << " (ID: " << cancion->obtenerId() << ")" << endl;
                    }
                }
            }
            break;
        }

        case 3: {
            cout << "Ingrese ID de la cancion: ";
            int id = leerOpcion();
            Cancion* cancion = sistema.buscarCancionPorId(id);
            if (cancion) {
                cout << "\n Cancion encontrada:" << endl;
                cout << "Nombre: " << cancion->obtenerNombre() << endl;
                cout << "Duracion: " << cancion->obtenerDuracion() << " min" << endl;
                cout << "Reproducciones: " << cancion->obtenerReproducciones() << endl;

                // Buscar artista y álbum
                Artista* artista = sistema.buscarArtistaPorCancionId(id);
                Album* album = sistema.buscarAlbumPorCancionId(id);
                if (artista) cout << "Artista: " << artista->obtenerNombre() << endl;
                if (album) cout << "Álbum: " << album->obtenerNombre() << endl;
            } else {
                cout << " Canción no encontrada." << endl;
            }
            break;
        }

        case 4:
            sistema.mostrarEstadisticasMensajes();
            break;

        case 5:
            cout << " Sesión cerrada para " << usuario->getNickname() << endl;
            break;

        default:
            cout << " Opción invalida." << endl;
        }

    } while (opcion != 5);
}

void registrarUsuario(Sistema& sistema) {
    cout << "\n=== REGISTRO DE USUARIO ===" << endl;

    string nickname = leerString("Ingrese nickname: ");

    if (sistema.buscarUsuario(nickname)) {
        cout << " Ya existe un usuario con ese nickname." << endl;
        return;
    }

    cout << "Tipos de membresía disponibles:" << endl;
    cout << "1. Estandar (Gratis)" << endl;
    cout << "2. Premium ($19.900/mes)" << endl;
    cout << "Seleccione tipo (1-2): ";

    int tipoOpcion = leerOpcion();
    string tipo = (tipoOpcion == 2) ? "premium" : "estandar";

    string ciudad = leerString("Ciudad: ");
    string pais = leerString("País: ");

    // Fecha automática
    int fecha = 20241201;

    Usuario* nuevo = new Usuario(nickname, tipo, ciudad, pais, fecha);
    sistema.agregarUsuario(nuevo);

    cout << "Usuario " << nickname << " registrado exitosamente como "
         << (tipo == "premium" ? "PREMIUM 🎉" : "ESTANDAR") << endl;
}

int main() {
    Sistema sistema;
    int opcion = 0;

    cout << "==========================================" << endl;
    cout << "        BIENVENIDO A UdeATunes      " << endl;
    cout << "     Tu plataforma de musica favorita     " << endl;
    cout << "==========================================" << endl;

    do {
        mostrarMenuPrincipal();
        opcion = leerOpcion();

        switch (opcion) {
        case 1: {
            string nickname = leerString("Ingrese su nickname: ");
            Usuario* usuario = sistema.buscarUsuario(nickname);
            if (usuario) {
                cout << "✅ Inicio de sesión exitoso. Bienvenido " << nickname << "!" << endl;
                menuUsuario(sistema, usuario);
            } else {
                cout << "❌ Usuario no encontrado." << endl;
            }
            break;
        }

        case 2:
            registrarUsuario(sistema);
            break;

        case 3:
            mostrarInformacionPlanes();
            break;

        case 4:
            cout << "\n==========================================" << endl;
            cout << "  Gracias por usar UdeATunes 🎵" << endl;
            cout << "        ¡Hasta pronto! 👋" << endl;
            cout << "==========================================" << endl;
            sistema.guardarDatos();
            break;

        default:
            cout << " Opción invalida. Intente nuevamente." << endl;
        }

    } while (opcion != 4);

    return 0;
}
