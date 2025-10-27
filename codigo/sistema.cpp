#include "sistema.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;

Sistema::Sistema()
    : listaUsuarios(nullptr),
    cantidadUsuarios(0),
    capacidadUsuarios(0),
    rutaArchivoUsuarios("Usuarios.txt")
{
}

Sistema::~Sistema()
{
    delete[] listaUsuarios;
    listaUsuarios = nullptr;
    cantidadUsuarios = 0;
    capacidadUsuarios = 0;
}

void Sistema::setRutaArchivoUsuarios(const std::string& ruta)
{
    rutaArchivoUsuarios = ruta;
}

void Sistema::aumentarCapacidadUsuarios()
{
    int nuevaCapacidad = (capacidadUsuarios == 0) ? 2 : capacidadUsuarios * 2;
    Usuario** nuevoArreglo = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; ++i)
        nuevoArreglo[i] = listaUsuarios[i];

    delete[] listaUsuarios;
    listaUsuarios = nuevoArreglo;
    capacidadUsuarios = nuevaCapacidad;
}

bool Sistema::cargarDatos(const std::string& rutaArtistas,
                          const std::string& rutaAlbums,
                          const std::string& rutaCanciones,
                          const std::string& rutaCreditos,
                          const std::string& rutaCancionCreditos)
{
    bool ok = cargador.cargarTodo(
        &catalogo,
        rutaArtistas,
        rutaAlbums,
        rutaCanciones,
        rutaCreditos,
        rutaCancionCreditos
        );

    if (!ok)
    {
        cout << "Error: no se pudieron cargar los datos en el Sistema." << endl;
        return false;
    }
    return true;
}

void Sistema::agregarUsuario(Usuario* usuario)
{
    if (usuario == nullptr) return;

    if (cantidadUsuarios == capacidadUsuarios)
        aumentarCapacidadUsuarios();

    listaUsuarios[cantidadUsuarios] = usuario;
    cantidadUsuarios = cantidadUsuarios + 1;
}

int Sistema::obtenerCantidadUsuarios() const
{
    return cantidadUsuarios;
}

Usuario* Sistema::obtenerUsuarioEn(int indice) const
{
    if (indice < 0 || indice >= cantidadUsuarios) return nullptr;
    return listaUsuarios[indice];
}

Usuario* Sistema::buscarUsuarioPorNickname(const std::string& nick) const
{
    for (int i = 0; i < cantidadUsuarios; ++i)
    {
        if (listaUsuarios[i] != nullptr)
        {
            if (listaUsuarios[i]->getNickname() == nick)
                return listaUsuarios[i];
        }
    }
    return nullptr;
}

void Sistema::reproducirParaUsuario(const std::string& nick, int idCancion)
{
    Usuario* u = buscarUsuarioPorNickname(nick);
    if (u == nullptr)
    {
        cout << "Error: usuario '" << nick << "' no encontrado." << endl;
        return;
    }

    Cancion* c = catalogo.buscarCancionPorId(idCancion);
    Album*   a = catalogo.buscarAlbumPorCancionId(idCancion);

    if (c == nullptr || a == nullptr)
    {
        cout << "Error: cancion ID " << idCancion << " no encontrada." << endl;
        return;
    }

    if (u->esPremium())
    {
        cout << endl << "=== Reproduccion (Plan: premium) ===" << endl;
        planPremium.reproducirCancion(u, c, a);
    }
    else
    {
        cout << endl << "=== Reproduccion (Plan: estandar) ===" << endl;
        planEstandar.reproducirCancion(u, c, a);
    }
}

Catalogo* Sistema::obtenerCatalogo()
{
    return &catalogo;
}

void Sistema::agregarMensajeEstandar(MensajePublicitario* mensaje)
{
    planEstandar.agregarMensaje(mensaje);
}

void Sistema::cargarMensajesEstandarPorDefecto()
{
    static MensajePublicitario m1(1, "Prueba Premium 30 dias en 320 kbps.", "AAA");
    static MensajePublicitario m2(2, "Descubre playlists para estudiar.", "B");
    static MensajePublicitario m3(3, "Activa alertas de nuevos lanzamientos.", "C");

    planEstandar.agregarMensaje(&m1);
    planEstandar.agregarMensaje(&m2);
    planEstandar.agregarMensaje(&m3);
}

// archivo -> memoria
static string tipoMemoriaDesdeArchivo(const string& tipoArchivo)
{
    if (tipoArchivo == "plan premium")  return "premium";
    if (tipoArchivo == "premium")       return "premium";
    if (tipoArchivo == "plan estandar") return "estandar";
    if (tipoArchivo == "estandar")      return "estandar";
    return "estandar";
}

// memoria -> archivo
static string tipoArchivoDesdeMemoria(const string& tipoMembresia)
{
    if (tipoMembresia == "premium") return "plan premium";
    return "plan estandar";
}

bool Sistema::registrarUsuarioEnArchivo(const std::string& nombreUsuario,
                                        const std::string& password,
                                        const std::string& tipoMembresia,
                                        const std::string& ciudad,
                                        const std::string& pais,
                                        int fechaInscripcion)
{
    string tipoGuardar = (tipoMembresia == "premium") ? "plan premium" : "plan estandar";

    ofstream out(rutaArchivoUsuarios.c_str(), ios::app);
    if (!out.is_open())
    {
        cout << "Error: no se pudo abrir " << rutaArchivoUsuarios << " para escribir." << endl;
        return false;
    }

    // nombreUsuario;password;tipo;ciudad;pais;fecha
    out << nombreUsuario << ';' << password << ';' << tipoGuardar << ';'
        << ciudad << ';' << pais << ';' << fechaInscripcion << '\n';
    out.close();

    string tipoMem = (tipoMembresia == "premium") ? "premium" : "estandar";
    Usuario* u = new Usuario(nombreUsuario, tipoMem, ciudad, pais, fechaInscripcion);
    agregarUsuario(u);

    cout << "Usuario '" << nombreUsuario << "' registrado correctamente." << endl;
    return true;
}

bool Sistema::iniciarSesionDesdeArchivo(const std::string& nombreUsuario,
                                        const std::string& password)
{
    ifstream archivo(rutaArchivoUsuarios.c_str());
    if (!archivo.is_open())
    {
        cout << "[ERROR] No se pudo abrir " << rutaArchivoUsuarios << " para lectura." << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty()) continue;

        string campoNombre, campoPass, campoTipo, campoCiudad, campoPais, campoFecha;
        stringstream ss(linea);

        getline(ss, campoNombre, ';');
        getline(ss, campoPass,   ';');
        getline(ss, campoTipo,   ';');
        getline(ss, campoCiudad, ';');
        getline(ss, campoPais,   ';');
        getline(ss, campoFecha,  ';');

        if (campoNombre == nombreUsuario)
        {
            if (campoPass != password)
            {
                cout << "[ERROR] Contrasena incorrecta." << endl;
                archivo.close();
                return false;
            }

            int fecha = atoi(campoFecha.c_str());
            string tipoMem = tipoMemoriaDesdeArchivo(campoTipo);

            Usuario* u = buscarUsuarioPorNickname(nombreUsuario);
            if (u == nullptr)
            {
                Usuario* nuevo = new Usuario(campoNombre, tipoMem, campoCiudad, campoPais, fecha);
                agregarUsuario(nuevo);
            }
            else
            {
                u->setTipoMembresia(tipoMem);
            }

            archivo.close();
            cout << "Inicio de sesion exitoso. Bienvenido, " << nombreUsuario << "!" << endl;
            return true;
        }
    }

    archivo.close();
    cout << "El usuario '" << nombreUsuario << "' no se encuentra registrado." << endl;
    return false;
}

bool Sistema::cambiarPlanDeUsuarioEnArchivo(const std::string& nombreUsuario,
                                            const std::string& nuevoTipoMembresia)
{
    ifstream entrada(rutaArchivoUsuarios.c_str());
    if (!entrada.is_open())
    {
        cout << "[ERROR] No se pudo abrir " << rutaArchivoUsuarios << " para lectura." << endl;
        return false;
    }

    string rutaTemp = rutaArchivoUsuarios + ".tmp";
    ofstream salida(rutaTemp.c_str());
    if (!salida.is_open())
    {
        cout << "[ERROR] No se pudo abrir archivo temporal para escritura." << endl;
        entrada.close();
        return false;
    }

    string linea;
    bool actualizado = false;

    while (getline(entrada, linea))
    {
        if (linea.empty()) { salida << '\n'; continue; }

        string campoNombre, campoPass, campoTipo, campoCiudad, campoPais, campoFecha;
        stringstream ss(linea);

        getline(ss, campoNombre, ';');
        getline(ss, campoPass,   ';');
        getline(ss, campoTipo,   ';');
        getline(ss, campoCiudad, ';');
        getline(ss, campoPais,   ';');
        getline(ss, campoFecha,  ';');

        if (campoNombre == nombreUsuario)
        {
            campoTipo = (nuevoTipoMembresia == "premium") ? "plan premium" : "plan estandar";
            actualizado = true;
        }

        salida << campoNombre << ';' << campoPass << ';' << campoTipo << ';'
               << campoCiudad << ';' << campoPais << ';' << campoFecha << '\n';
    }

    entrada.close();
    salida.close();

    remove(rutaArchivoUsuarios.c_str());
    rename(rutaTemp.c_str(), rutaArchivoUsuarios.c_str());

    if (actualizado)
    {
        Usuario* u = buscarUsuarioPorNickname(nombreUsuario);
        if (u != nullptr)
        {
            u->setTipoMembresia((nuevoTipoMembresia == "premium") ? "premium" : "estandar");
        }
        cout << "Plan actualizado correctamente para '" << nombreUsuario << "'." << endl;
    }
    else
    {
        cout << "No se encontro el usuario '" << nombreUsuario << "' para cambiar su plan." << endl;
    }

    return actualizado;
}


void Sistema::mostrarMetricas(int iteraciones) const
{
    cout << endl << "   METRICAS   " << endl;
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria consumida: " << calcularMemoriaTotal() << " bytes" << endl;
}

size_t Sistema::calcularMemoriaTotal() const
{
    size_t memoria = 0;

    memoria = memoria + sizeof(Sistema);

    memoria = memoria + sizeof(Usuario*) * (size_t)capacidadUsuarios;

    for (int i = 0; i < cantidadUsuarios; ++i)
    {
        if (listaUsuarios[i] != nullptr)
        {
            memoria = memoria + sizeof(Usuario);
        }
    }

    memoria = memoria + sizeof(Catalogo);
    memoria = memoria + sizeof(CargarCatalogo);
    memoria = memoria + sizeof(PlanEstandar);
    memoria = memoria + sizeof(PlanPremium);

    return memoria;
}
