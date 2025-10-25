#include "cargar_catalogo.h"
#include <cstdio>
#include <cstring>
using namespace std;

CargarCatalogo::CargarCatalogo()
{
}

CargarCatalogo::~CargarCatalogo()
{
}

bool CargarCatalogo::leerLinea(FILE* archivo, char* buffer, int longitud)
{
    if (fgets(buffer, longitud, archivo) == nullptr)
    {
        return false;
    }

    int n = (int)strlen(buffer);

    if (n > 0 && (buffer[n - 1] == '\n' || buffer[n - 1] == '\r'))
    {
        buffer[n - 1] = '\0';
        n = n - 1;
        if (n > 0 && buffer[n - 1] == '\r')
        {
            buffer[n - 1] = '\0';
        }
    }

    return true;
}

char* CargarCatalogo::obtenerCampo(char* &cursor)
{
    if (cursor == nullptr)
    {
        return nullptr;
    }

    char* inicio = cursor;
    char* separador = strchr(cursor, ';');

    if (separador == nullptr)
    {
        cursor = nullptr;
        return inicio;
    }
    else
    {
        *separador = '\0';
        cursor = separador + 1;
        return inicio;
    }
}

int CargarCatalogo::convertirEntero(const char* texto)
{
    if (texto == nullptr || *texto == '\0')
    {
        return 0;
    }

    return atoi(texto);
}

float CargarCatalogo::convertirFlotante(const char* texto)
{
    if (texto == nullptr || *texto == '\0')
    {
        return 0.0f;
    }

    return (float)atof(texto);
}

Artista* CargarCatalogo::buscarArtistaPorId(Catalogo* catalogo, int idArtista)
{
    return catalogo->buscarArtistaPorId(idArtista);
}

Album* CargarCatalogo::buscarAlbumGlobalPorId(Catalogo* catalogo, int idAlbum)
{
    return catalogo->buscarAlbumPorId(idAlbum);
}

Cancion* CargarCatalogo::buscarCancionGlobalPorId(Catalogo* catalogo, int idCancion)
{
    return catalogo->buscarCancionPorId(idCancion);
}

Credito* CargarCatalogo::buscarCreditoPorId(Credito** lista, int cantidad, int idCredito)
{
    for (int i = 0; i < cantidad; ++i)
    {
        if (lista[i] != nullptr && lista[i]->getId() == idCredito)
        {
            return lista[i];
        }
    }

    return nullptr;
}

bool CargarCatalogo::cargarTodo(
    Catalogo* catalogo,
    const string& rutaArtistas,
    const string& rutaAlbums,
    const string& rutaCanciones,
    const string& rutaCreditos,
    const string& rutaCancionCreditos
    )
{
    char linea[MAX_LINEA];

    // Cargar artistas
    FILE* archivoArtistas = fopen(rutaArtistas.c_str(), "r");
    if (archivoArtistas == nullptr) return false;

    leerLinea(archivoArtistas, linea, MAX_LINEA);

    while (leerLinea(archivoArtistas, linea, MAX_LINEA))
    {
        char* cursor = linea;
        char* campoId = obtenerCampo(cursor);
        char* campoEdad = obtenerCampo(cursor);
        char* campoNombre = obtenerCampo(cursor);
        char* campoPais = obtenerCampo(cursor);
        char* campoSeguidores = obtenerCampo(cursor);
        char* campoPosicion = obtenerCampo(cursor);

        int id = convertirEntero(campoId);
        int edad = convertirEntero(campoEdad);
        int seguidores = convertirEntero(campoSeguidores);
        int posicion = convertirEntero(campoPosicion);
        string nombre = (campoNombre ? campoNombre : "");
        string pais = (campoPais ? campoPais : "");

        Artista* nuevoArtista = new Artista(id, edad, nombre, pais);
        nuevoArtista->setSeguidores(seguidores);
        nuevoArtista->setPosicion(posicion);
        catalogo->agregarArtista(nuevoArtista);
    }

    fclose(archivoArtistas);

    //Cargar álbumes
    FILE* archivoAlbums = fopen(rutaAlbums.c_str(), "r");
    if (archivoAlbums == nullptr) return false;

    leerLinea(archivoAlbums, linea, MAX_LINEA);

    while (leerLinea(archivoAlbums, linea, MAX_LINEA))
    {
        char* cursor = linea;
        char* campoId = obtenerCampo(cursor);
        char* campoIdArtista = obtenerCampo(cursor);
        char* campoNombre = obtenerCampo(cursor);
        char* campoFecha = obtenerCampo(cursor);
        char* campoSello = obtenerCampo(cursor);
        char* campoPortada = obtenerCampo(cursor);
        char* campoPuntuacion = obtenerCampo(cursor);
        char* campoGenero1 = obtenerCampo(cursor);
        char* campoGenero2 = obtenerCampo(cursor);
        char* campoGenero3 = obtenerCampo(cursor);
        char* campoGenero4 = obtenerCampo(cursor);

        int idAlbum = convertirEntero(campoId);
        int idArtista = convertirEntero(campoIdArtista);
        int fecha = convertirEntero(campoFecha);
        int puntuacion = convertirEntero(campoPuntuacion);
        string nombre = (campoNombre ? campoNombre : "");
        string sello = (campoSello ? campoSello : "");
        string portada = (campoPortada ? campoPortada : "");
        string genero1 = (campoGenero1 ? campoGenero1 : "");
        string genero2 = (campoGenero2 ? campoGenero2 : "");
        string genero3 = (campoGenero3 ? campoGenero3 : "");
        string genero4 = (campoGenero4 ? campoGenero4 : "");

        Artista* artista = buscarArtistaPorId(catalogo, idArtista);
        if (artista != nullptr)
        {
            Album* nuevoAlbum = new Album(idAlbum, nombre, fecha, sello, portada, puntuacion, genero1, genero2, genero3, genero4);
            artista->agregarAlbum(nuevoAlbum);
        }
    }

    fclose(archivoAlbums);

    //Cargar canciones
    FILE* archivoCanciones = fopen(rutaCanciones.c_str(), "r");
    if (archivoCanciones == nullptr) return false;

    leerLinea(archivoCanciones, linea, MAX_LINEA);

    while (leerLinea(archivoCanciones, linea, MAX_LINEA))
    {
        char* cursor = linea;
        char* campoIdCancion = obtenerCampo(cursor);
        char* campoIdAlbum = obtenerCampo(cursor);
        char* campoDuracion = obtenerCampo(cursor);
        char* campoNombre = obtenerCampo(cursor);
        char* campoRuta128 = obtenerCampo(cursor);
        char* campoRuta320 = obtenerCampo(cursor);

        int idCancion = convertirEntero(campoIdCancion);
        int idAlbum = convertirEntero(campoIdAlbum);
        float duracion = convertirFlotante(campoDuracion);
        string nombre = (campoNombre ? campoNombre : "");
        string ruta128 = (campoRuta128 ? campoRuta128 : "");
        string ruta320 = (campoRuta320 ? campoRuta320 : "");

        Album* album = buscarAlbumGlobalPorId(catalogo, idAlbum);
        if (album != nullptr)
        {
            Cancion* nuevaCancion = new Cancion(idCancion, duracion, nombre, ruta128, ruta320);
            album->agregarCancion(nuevaCancion);
        }
    }

    fclose(archivoCanciones);

    //Cargar créditos
    Credito** listaCreditos = nullptr;
    int cantidadCreditos = 0;
    int capacidadCreditos = 0;

    auto aumentarCapacidadCreditos = [&]()
    {
        int nuevaCapacidad = (capacidadCreditos == 0) ? 4 : capacidadCreditos * 2;
        Credito** nuevoArreglo = new Credito*[nuevaCapacidad];
        for (int i = 0; i < cantidadCreditos; ++i)
        {
            nuevoArreglo[i] = listaCreditos[i];
        }
        delete[] listaCreditos;
        listaCreditos = nuevoArreglo;
        capacidadCreditos = nuevaCapacidad;
    };

    FILE* archivoCreditos = fopen(rutaCreditos.c_str(), "r");
    if (archivoCreditos == nullptr) return false;

    leerLinea(archivoCreditos, linea, MAX_LINEA);

    while (leerLinea(archivoCreditos, linea, MAX_LINEA))
    {
        if (cantidadCreditos == capacidadCreditos)
        {
            aumentarCapacidadCreditos();
        }

        char* cursor = linea;
        char* campoId = obtenerCampo(cursor);
        char* campoNombre = obtenerCampo(cursor);
        char* campoApellido = obtenerCampo(cursor);
        char* campoCategoria = obtenerCampo(cursor);
        char* campoAfiliacion = obtenerCampo(cursor);

        int id = convertirEntero(campoId);
        string nombre = (campoNombre ? campoNombre : "");
        string apellido = (campoApellido ? campoApellido : "");
        string categoria = (campoCategoria ? campoCategoria : "");
        string afiliacion = (campoAfiliacion ? campoAfiliacion : "");

        listaCreditos[cantidadCreditos] = new Credito(id, nombre, apellido, categoria, afiliacion);
        cantidadCreditos = cantidadCreditos + 1;
    }

    fclose(archivoCreditos);

    //Relación canción–créditos
    FILE* archivoRelacion = fopen(rutaCancionCreditos.c_str(), "r");
    if (archivoRelacion == nullptr) return false;

    leerLinea(archivoRelacion, linea, MAX_LINEA);

    while (leerLinea(archivoRelacion, linea, MAX_LINEA))
    {
        char* cursor = linea;
        char* campoIdCancion = obtenerCampo(cursor);
        char* campoIdCredito = obtenerCampo(cursor);

        int idCancion = convertirEntero(campoIdCancion);
        int idCredito = convertirEntero(campoIdCredito);

        Cancion* cancion = buscarCancionGlobalPorId(catalogo, idCancion);
        Credito* credito = buscarCreditoPorId(listaCreditos, cantidadCreditos, idCredito);

        if (cancion != nullptr && credito != nullptr)
        {
            cancion->agregarCredito(credito);
        }
    }

    fclose(archivoRelacion);

    return true;
}
