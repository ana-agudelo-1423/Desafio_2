#ifndef CARGADOR_CATALOGO_H
#define CARGADOR_CATALOGO_H

#include <string>
#include "catalogo.h"
#include "artista.h"
#include "album.h"
#include "cancion.h"
#include "credito.h"

class CargarCatalogo
{
private:
    static const int MAX_LINEA = 1024;

    static bool leerLinea(FILE* archivo, char* buffer, int longitud);
    static char* obtenerCampo(char* &cursor);
    static int convertirEntero(const char* texto);
    static float convertirFlotante(const char* texto);

    static Artista* buscarArtistaPorId(Catalogo* catalogo, int idArtista);
    static Album* buscarAlbumGlobalPorId(Catalogo* catalogo, int idAlbum);
    static Cancion* buscarCancionGlobalPorId(Catalogo* catalogo, int idCancion);
    static Credito* buscarCreditoPorId(Credito** lista, int cantidad, int idCredito);

public:
    CargarCatalogo();
    ~CargarCatalogo();

    bool cargarTodo(
        Catalogo* catalogo,
        const std::string& rutaArtistas,
        const std::string& rutaAlbums,
        const std::string& rutaCanciones,
        const std::string& rutaCreditos,
        const std::string& rutaCancionCreditos
        );
};

#endif
