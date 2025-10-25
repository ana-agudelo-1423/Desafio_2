#ifndef SISTEMA_H
#define SISTEMA_H

#include "catalogo.h"
#include "usuario.h"
#include "mensaje_publicitario.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

class Sistema {
private:
    Catalogo* catalogo;
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

    MensajePublicitario** mensajesPublicitarios;
    int cantidadMensajes;
    int capacidadMensajes;

    void aumentarCapacidadUsuarios();
    void aumentarCapacidadMensajes();
    void cargarUsuariosDesdeArchivo();
    void cargarMensajesDesdeArchivo();
    void guardarUsuariosEnArchivo();
    void guardarMensajesEnArchivo();
    void cargarArtistasDesdeArchivo();
    void cargarAlbumesDesdeArchivo();
    void cargarCancionesDesdeArchivo();
    void cargarCreditosDesdeArchivo();
    void cargarAlbumesEjemplo();

public:
    Sistema();
    ~Sistema();

    void cargarDatos();
    void guardarDatos();
    void cargarCatalogo();

    void agregarUsuario(Usuario* usuario);
    Usuario* buscarUsuario(const string& nick) const;
    void agregarMensajePublicitario(MensajePublicitario* mensaje);
    MensajePublicitario* obtenerMensajeAleatorio() const;
    void mostrarEstadisticasMensajes() const;

    void reproduccionAleatoria(Usuario* usuarioActual);
    Cancion* buscarCancionPorId(int id) const;
    Album* buscarAlbumPorCancionId(int id) const;
    Artista* buscarArtistaPorCancionId(int id) const;

    void mostrarMetricas(int iteraciones) const;
    size_t calcularMemoriaTotal() const;
    Catalogo* getCatalogo() const;
};

#endif
