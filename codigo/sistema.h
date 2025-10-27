#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "catalogo.h"
#include "cargar_catalogo.h"
#include "usuario.h"
#include "plan_estandar.h"
#include "plan_premium.h"
#include "mensaje_publicitario.h"

    class Sistema
{
private:
    Catalogo         catalogo;
    CargarCatalogo   cargador;

    Usuario**        listaUsuarios;
    int              cantidadUsuarios;
    int              capacidadUsuarios;

    PlanEstandar     planEstandar;
    PlanPremium      planPremium;

    std::string      rutaArchivoUsuarios;

    void             aumentarCapacidadUsuarios();

public:
    Sistema();
    ~Sistema();

    bool      cargarDatos(const std::string& rutaArtistas,
                     const std::string& rutaAlbums,
                     const std::string& rutaCanciones,
                     const std::string& rutaCreditos,
                     const std::string& rutaCancionCreditos);

    void      agregarUsuario(Usuario* usuario);
    int       obtenerCantidadUsuarios() const;
    Usuario*  obtenerUsuarioEn(int indice) const;
    Usuario*  buscarUsuarioPorNickname(const std::string& nick) const;

    void      reproducirParaUsuario(const std::string& nick, int idCancion);
    Catalogo* obtenerCatalogo();

    void      agregarMensajeEstandar(MensajePublicitario* mensaje);
    void      cargarMensajesEstandarPorDefecto();

    void      setRutaArchivoUsuarios(const std::string& ruta);

    bool      registrarUsuarioEnArchivo(const std::string& nombreUsuario,
                                   const std::string& password,
                                   const std::string& tipoMembresia,
                                   const std::string& ciudad,
                                   const std::string& pais,
                                   int fechaInscripcion);

    bool      iniciarSesionDesdeArchivo(const std::string& nombreUsuario,
                                   const std::string& password);

    bool      cambiarPlanDeUsuarioEnArchivo(const std::string& nombreUsuario,
                                       const std::string& nuevoTipoMembresia);

    // ======= MÉTRICAS =======
    void      mostrarMetricas(int iteraciones) const;
    size_t    calcularMemoriaTotal() const;
};

#endif
