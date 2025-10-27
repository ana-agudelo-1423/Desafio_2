#include <iostream>
#include <string>
#include "sistema.h"
#include "usuario.h"
#include "catalogo.h"
#include "artista.h"
#include "album.h"
#include "cancion.h"
    using namespace std;

//utilidades de entrada

static void limpiarBuffer()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

static int leerEntero()
{
    int x;
    while (!(cin >> x))
    {
        cout << "Entrada invalida. Ingrese un numero:" << endl;
        cin.clear();
        limpiarBuffer();
    }
    limpiarBuffer();
    return x;
}

static string leerLinea(const string& mensaje)
{
    string s;
    cout << mensaje;
    getline(cin, s);
    return s;
}

//ayudas de catalogo

static Artista* buscarArtistaDeAlbum(Catalogo* c, Album* album)
{
    if (c == nullptr || album == nullptr)
        return nullptr;

    for (int i = 0; i < c->obtenerCantidadArtistas(); ++i)
    {
        Artista* a = c->obtenerArtistaEn(i);
        if (a == nullptr) continue;

        for (int j = 0; j < a->obtenerCantidadAlbums(); ++j)
        {
            if (a->obtenerAlbumEn(j) == album)
                return a;
        }
    }
    return nullptr;
}

// utilidades de UI

static void mostrarInformacionPlanes()
{
    cout << endl << "   PLANES DISPONIBLES   " << endl;
    cout << endl << "PLAN ESTANDAR (Gratis)" << endl;
    cout << " - Reproduccion a 128 kbps" << endl;
    cout << " - Publicidad cada 2 canciones" << endl;
    cout << " - Sin favoritos ni historial" << endl;

    cout << endl << "PLAN PREMIUM (Pago)" << endl;
    cout << " - Reproduccion a 320 kbps" << endl;
    cout << " - Sin publicidad" << endl;
    cout << " - Favoritos e historial" << endl;
    cout << "                         " << endl;
}

static void verCatalogo(Sistema* sistema)
{
    Catalogo* c = sistema->obtenerCatalogo();
    if (c == nullptr)
        return;

    cout << endl << "    CATALOGO COMPLETO   " << endl;

    for (int i = 0; i < c->obtenerCantidadArtistas(); ++i)
    {
        Artista* a = c->obtenerArtistaEn(i);
        if (a == nullptr) continue;

        cout << endl << a->obtenerNombre() << " (" << a->obtenerPaisOrigen() << ")" << endl;

        for (int j = 0; j < a->obtenerCantidadAlbums(); ++j)
        {
            Album* al = a->obtenerAlbumEn(j);
            if (al == nullptr) continue;

            cout << "  - " << al->obtenerNombre() << endl;

            for (int k = 0; k < al->obtenerCantidadCanciones(); ++k)
            {
                Cancion* c = al->obtenerCancionEn(k);
                if (c == nullptr) continue;

                cout << "      * " << c->obtenerNombre()
                     << " [" << c->obtenerDuracion() << " seg]"
                     << " (ID: " << c->obtenerId() << ")" << endl;
            }
        }
    }
}

static void buscarCancionPorIdUI(Sistema* sistema)
{
    Catalogo* c = sistema->obtenerCatalogo();
    if (c == nullptr)
        return;

    cout << "Ingrese ID de la cancion:" << endl;
    int id = leerEntero();

    Cancion* cancion = c->buscarCancionPorId(id);
    if (cancion == nullptr)
    {
        cout << "Cancion no encontrada." << endl;
        return;
    }

    Album*  album  = c->buscarAlbumPorCancionId(id);
    Artista* artis = buscarArtistaDeAlbum(c, album);

    cout << endl << "Cancion encontrada:" << endl;
    cout << "Nombre: " << cancion->obtenerNombre() << endl;
    cout << "Duracion: " << cancion->obtenerDuracion() << " seg" << endl;
    cout << "Reproducciones: " << cancion->obtenerReproducciones() << endl;
    if (artis != nullptr)
        cout << "Artista: " << artis->obtenerNombre() << endl;
    if (album != nullptr)
        cout << "Album: " << album->obtenerNombre() << endl;
}



static void listarFavoritosUI(Usuario* usuario)
{
    int total = usuario->getCantidadFavoritos();

    cout << endl << "     FAVORITOS (" << total << ")    " << endl;

    if (total == 0)
    {
        cout << "No hay canciones en favoritos." << endl;
    }
    else
    {
        for (int i = 0; i < total; ++i)
        {
            Cancion* c = usuario->getFavoritoEn(i);
            if (c == nullptr) continue;

            cout << "  - " << c->obtenerNombre()
                 << " (ID: " << c->obtenerId()
                 << ", " << c->obtenerDuracion() << " seg)" << endl;
        }
    }
}

static void agregarFavoritoUI(Sistema* sistema, Usuario* usuario)
{
    cout << "Ingrese ID de la cancion a agregar:" << endl;
    int id = leerEntero();

    Catalogo* c = sistema->obtenerCatalogo();
    Cancion* cancion = c->buscarCancionPorId(id);

    if (cancion == nullptr)
    {
        cout << "Cancion no encontrada." << endl;
    }
    else
    {
        usuario->agregarFavorito(cancion);
    }
}

static void eliminarFavoritoUI(Usuario* usuario)
{
    cout << "Ingrese ID de la cancion a eliminar:" << endl;
    int id = leerEntero();

    bool ok = usuario->eliminarFavorito(id);
    if (!ok)
        cout << "No se pudo eliminar. Verifique el ID." << endl;
}

static void menuFavoritos(Sistema* sistema, Usuario* usuario)
{
    int opcion = 0;

    do
    {
        cout << endl << "   FAVORITOS (PREMIUM)   " << endl;
        cout << "1. Agregar cancion" << endl;
        cout << "2. Eliminar cancion" << endl;
        cout << "3. Ver favoritos" << endl;
        cout << "4. Volver" << endl;
        cout << "Seleccione una opcion:" << endl;

        opcion = leerEntero();

        if (opcion == 1)
            agregarFavoritoUI(sistema, usuario);
        else if (opcion == 2)
            eliminarFavoritoUI(usuario);
        else if (opcion == 3)
            listarFavoritosUI(usuario);
        else if (opcion == 4)
            cout << "Regresando..." << endl;
        else
            cout << "Opcion invalida." << endl;
    }
    while (opcion != 4);
}

static void menuHistorial(Usuario* usuario)
{
    int opcion = 0;

    do
    {
        cout << endl << "   HISTORIAL (PREMIUM)   " << endl;
        cout << "1. Cancion anterior" << endl;
        cout << "2. Cancion siguiente" << endl;
        cout << "3. Limpiar historial" << endl;
        cout << "4. Volver" << endl;
        cout << "Seleccione una opcion:" << endl;

        opcion = leerEntero();

        if (opcion == 1)
        {
            Cancion* c = usuario->obtenerCancionAnterior();
            if (c != nullptr)
                cout << "Anterior: " << c->obtenerNombre() << endl;
        }
        else if (opcion == 2)
        {
            Cancion* c = usuario->obtenerCancionSiguiente();
            if (c != nullptr)
                cout << "Siguiente: " << c->obtenerNombre() << endl;
        }
        else if (opcion == 3)
        {
            usuario->limpiarHistorial();
            cout << "Historial limpiado." << endl;
        }
        else if (opcion == 4)
        {
            cout << "Regresando..." << endl;
        }
        else
        {
            cout << "Opcion invalida." << endl;
        }
    }
    while (opcion != 4);
}

//MENUS USUARIOS

static void menuUsuarioEstandar(Sistema* sistema, Usuario* usuario)
{
    int opcion = 0;

    do
    {
        cout << endl << "   MENU USUARIO - " << usuario->getNickname() << " (ESTANDAR)   " << endl;
        cout << "1. Reproducir por ID" << endl;
        cout << "2. Ver catalogo musical" << endl;
        cout << "3. Buscar cancion por ID" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Seleccione una opcion:" << endl;

        opcion = leerEntero();

        if (opcion == 1)
        {
            cout << "Ingrese ID de la cancion:" << endl;
            int id = leerEntero();
            sistema->reproducirParaUsuario(usuario->getNickname(), id);
        }
        else if (opcion == 2)
        {
            verCatalogo(sistema);
        }
        else if (opcion == 3)
        {
            buscarCancionPorIdUI(sistema);
        }
        else if (opcion == 4)
        {
            cout << "Sesion cerrada para " << usuario->getNickname() << endl;
        }
        else
        {
            cout << "Opcion invalida." << endl;
        }
    }
    while (opcion != 4);
}

static void menuUsuarioPremium(Sistema* sistema, Usuario* usuario)
{
    int opcion = 0;

    do
    {
        cout << endl << "   MENU USUARIO - " << usuario->getNickname() << " (PREMIUM)    " << endl;
        cout << "1. Reproducir por ID" << endl;
        cout << "2. Ver catalogo musical" << endl;
        cout << "3. Buscar cancion por ID" << endl;
        cout << "4. Gestionar favoritos" << endl;
        cout << "5. Historial de reproduccion" << endl;
        cout << "6. Cerrar sesion" << endl;
        cout << "Seleccione una opcion:" << endl;

        opcion = leerEntero();

        if (opcion == 1)
        {
            cout << "Ingrese ID de la cancion:" << endl;
            int id = leerEntero();
            sistema->reproducirParaUsuario(usuario->getNickname(), id);
        }
        else if (opcion == 2)
        {
            verCatalogo(sistema);
        }
        else if (opcion == 3)
        {
            buscarCancionPorIdUI(sistema);
        }
        else if (opcion == 4)
        {
            menuFavoritos(sistema, usuario);
        }
        else if (opcion == 5)
        {
            menuHistorial(usuario);
        }
        else if (opcion == 6)
        {
            cout << "Sesion cerrada para " << usuario->getNickname() << endl;
        }
        else
        {
            cout << "Opcion invalida." << endl;
        }
    }
    while (opcion != 6);
}

//REGISTRO / SESION

static void registrarUsuarioUI(Sistema* sistema)
{
    cout << endl << "   REGISTRO DE USUARIO   " << endl;

    string nickname = leerLinea("Nickname: ");
    Usuario* existente = sistema->buscarUsuarioPorNickname(nickname);

    if (existente != nullptr)
    {
        cout << "Ya existe un usuario con ese nickname." << endl;
        return;
    }

    string password = leerLinea("Contrasena: ");

    cout << "Tipos de membresia:" << endl;
    cout << "1. Estandar (Gratis)" << endl;
    cout << "2. Premium (Pago)" << endl;
    cout << "Seleccione tipo (1-2):" << endl;
    int tipoOpcion = leerEntero();

    string tipo;
    if (tipoOpcion == 2)
        tipo = "premium";
    else
        tipo = "estandar";

    string ciudad = leerLinea("Ciudad: ");
    string pais   = leerLinea("Pais: ");
    int fecha = 20250101;

    bool ok = sistema->registrarUsuarioEnArchivo(nickname, password, tipo, ciudad, pais, fecha);

    if (ok)
    {
        cout << "Usuario " << nickname << " registrado como " << tipo << endl;
    }
}

static void iniciarSesionUI(Sistema* sistema)
{
    string nickname  = leerLinea("Ingrese su nickname: ");
    string password  = leerLinea("Contrasena: ");

    bool ok = sistema->iniciarSesionDesdeArchivo(nickname, password);

    if (!ok)
    {
        cout << "No fue posible iniciar sesion. Verifique el usuario." << endl;
        return;
    }

    Usuario* u = sistema->buscarUsuarioPorNickname(nickname);

    if (u == nullptr)
    {
        cout << "Error: el usuario no esta cargado." << endl;
        return;
    }

    cout << "Inicio de sesion exitoso. Bienvenido " << nickname << "!" << endl;

    if (u->esPremium())
        menuUsuarioPremium(sistema, u);
    else
        menuUsuarioEstandar(sistema, u);
}

static void cambiarPlanUI(Sistema* sistema)
{
    cout << endl << "   CAMBIO DE PLAN   " << endl;

    string nickname = leerLinea("Nickname: ");
    cout << "Nuevo plan:" << endl;
    cout << "1. Estandar" << endl;
    cout << "2. Premium" << endl;
    cout << "Seleccione (1-2):" << endl;
    int op = leerEntero();

    string nuevoTipo;
    if (op == 2)
        nuevoTipo = "premium";
    else
        nuevoTipo = "estandar";

    bool ok = sistema->cambiarPlanDeUsuarioEnArchivo(nickname, nuevoTipo);

    if (!ok)
        cout << "No fue posible cambiar el plan." << endl;
}

// MAIN

int main()
{

    Sistema sistema;

    sistema.setRutaArchivoUsuarios("C:\\Users\\USER\\Desktop\\Desafio_2\\codigo\\Usuarios.txt");

    bool ok = sistema.cargarDatos(
        "C:\\Users\\USER\\Desktop\\Desafio_2\\codigo\\Data\\Artistas.txt",
        "C:\\Users\\USER\\Desktop\\Desafio_2\\codigo\\Data\\Albums.txt",
        "C:\\Users\\USER\\Desktop\\Desafio_2\\codigo\\Data\\Canciones.txt",
        "C:\\Users\\USER\\Desktop\\Desafio_2\\codigo\\Data\\Creditos.txt",
        "C:\\Users\\USER\\Desktop\\Desafio_2\\codigo\\Data\\Cancion_creditos.txt"
        );

    if (!ok)
    {
        cout << "Error: no se pudieron cargar los datos." << endl;
        return 1;
    }

    sistema.cargarMensajesEstandarPorDefecto();

    int opcion = 0;
    int iteracionesMenu = 0;  // contador para métricas

    cout << "==========================================" << endl;
    cout << "           BIENVENIDO A UdeATunes         " << endl;
    cout << "==========================================" << endl;

    do
    {
        cout << endl << "   MENU PRINCIPAL   " << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Registrar nuevo usuario" << endl;
        cout << "3. Cambiar plan de usuario" << endl;
        cout << "4. Informacion de planes" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion:" << endl;

        opcion = leerEntero();
        iteracionesMenu = iteracionesMenu + 1;

        if (opcion == 1)
            iniciarSesionUI(&sistema);
        else if (opcion == 2)
            registrarUsuarioUI(&sistema);
        else if (opcion == 3)
            cambiarPlanUI(&sistema);
        else if (opcion == 4)
            mostrarInformacionPlanes();
        else if (opcion == 5)
            cout << endl << "Gracias por usar UdeATunes." << endl;
        else
            cout << "Opcion invalida." << endl;
    }
    while (opcion != 5);

    sistema.mostrarMetricas(iteracionesMenu);

    return 0;
}
