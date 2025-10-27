#include "../include/biblioteca.h"
#include <assert.h>

struct rep_biblioteca {
  TABBLibros libros;
  TLSESocios socios;
  TLDEPrestamos prestamos;
  TAGGeneros generos;
  TColaReservas reservas;
};

TBiblioteca crearTBiblioteca() {
    // reservar memoria para la biblioteca
    TBiblioteca biblioteca = new rep_biblioteca;

    // inicializar cada componente con su función correspondiente
    biblioteca->libros = crearTABBLibrosVacio();
    biblioteca->socios = crearTLSESociosVacia();
    biblioteca->prestamos = crearTLDEPrestamosVacia();
    biblioteca->generos = crearTAGGeneros();
    biblioteca->reservas = crearTColaReservas();

    return biblioteca;
}

void liberarTBiblioteca(TBiblioteca &biblioteca) {
    if (biblioteca == NULL) return;

    // 1) Estructuras que REFERENCIAN socio/libro → SOLO estructura
    liberarTLDEPrestamosSoloEstructura(biblioteca->prestamos);
    liberarTColaReservasSoloEstructura(biblioteca->reservas);

    // 2) Dueños reales
    liberarTLSESocios(biblioteca->socios);
    liberarTABBLibros(biblioteca->libros);
    liberarTColaReservas(biblioteca->reservas);
    // 3) Resto
    liberarTAGGeneros(biblioteca->generos);

    delete biblioteca;
    biblioteca = NULL;
}

void agregarLibroTBiblioteca(TBiblioteca biblioteca, TLibro libro){ //listo
  insertarLibroTABBLibros(biblioteca->libros,libro);
}

void agregarSocioTBiblioteca(TBiblioteca biblioteca, TSocio socio){ //listo
  insertarTLSESocios(biblioteca->socios,socio);
}

void imprimirSociosTBiblioteca(TBiblioteca biblioteca){ // listo
  imprimirTLSESocios(biblioteca->socios);
}

void imprimirLibrosTBiblioteca(TBiblioteca biblioteca){ // listo
  imprimirTABBLibros(biblioteca->libros);
}

void prestarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo){
  TSocio socio = obtenerSocioTLSESocios(biblioteca->socios, ciSocio);
  TLibro libro = obtenerLibroTABBLibros(biblioteca->libros, isbnLibro); // O(l)
  TPrestamo prestamo = crearTPrestamo(socio, libro, fechaPrestamo);
  insertarTLDEPrestamos(biblioteca->prestamos,prestamo);
}



bool disponibleLibroTBiblioteca(TBiblioteca biblioteca, int isbnLibro) {
    // Si el libro no existe en el ABB, no está disponible.
    if (!existeLibroTABBLibros(biblioteca->libros, isbnLibro)) return false;     // O(l)

    // 1) Préstamos NO retornados (activos). El filtro crea COPIAS profundas.
    TLDEPrestamos activos = filtrarPrestamosTLDEPrestamos(biblioteca->prestamos, /*criterio=*/1);

    // 2) Recorrer la lista filtrada (con copias)
    nat k = cantidadTLDEPrestamos(activos);                                      // O(1)
    for (nat i = 1; i <= k; i++) {                                               // O(p) iteraciones
        TPrestamo pr = obtenerNesimoTLDEPrestamos(activos, (int)i);              // O(p) -> total O(p^2)
        TLibro lib = libroTPrestamo(pr);                                         // O(1)
        if (isbnTLibro(lib) == isbnLibro) {
            liberarTLDEPrestamos(activos);   // IMPORTANTE: lista filtrada -> liberar COMPLETO
            return false;                    // hay un préstamo activo de ese ISBN
        }
    }

    // 3) No hay préstamos activos con ese ISBN
    liberarTLDEPrestamos(activos);           // liberar COMPLETO (eran copias)
    return true;
}



void imprimirPrestamosTBiblioteca(TBiblioteca biblioteca){
  imprimirTLDEPrestamos(biblioteca->prestamos);
}

void reservarLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro){  
  encolarTColaReservas(biblioteca->reservas,crearTReserva(obtenerSocioTLSESocios(biblioteca->socios,ciSocio),obtenerLibroTABBLibros(biblioteca->libros,isbnLibro)));
}

void imprimirReservasTBiblioteca(TBiblioteca biblioteca){
  imprimirTColaReservas(biblioteca->reservas);
}

void devolverLibroTBiblioteca(TBiblioteca biblioteca, int ciSocio, int isbnLibro, TFecha fechaPrestamo, TFecha fechaDevolucion){
    const nat n = cantidadTLDEPrestamos(biblioteca->prestamos);
    for (nat i = 1; i <= n; i++) {
        TPrestamo pr = obtenerNesimoTLDEPrestamos(biblioteca->prestamos, (int)i);

        if (!fueRetornadoTPrestamo(pr) &&
            ciTSocio(socioTPrestamo(pr)) == ciSocio &&
            isbnTLibro(libroTPrestamo(pr)) == isbnLibro &&
            compararTFechas(fechaRetiroTPrestamo(pr), fechaPrestamo) == 0) {
            actualizarFechaDevolucionTPrestamo(pr, fechaDevolucion);
            return;
        }
    }
}

void agregarGeneroABiblioteca(TBiblioteca biblioteca, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE]){
  insertarGeneroTAGGeneros(biblioteca->generos,idGeneroPadre,idGenero,nombreGenero);
}

TABBLibros obtenerLibrosDeGenero(TBiblioteca biblioteca, int idGenero) {
    // 1) Obtener conjunto de géneros: incluye idGenero y sus subgéneros
    TConjuntoGeneros conjunto = obtenerConjuntoGeneros(biblioteca->generos, idGenero);

    // 2) Crear árbol ABB resultado vacío
    TABBLibros resultado = crearTABBLibrosVacio();

    // 3) Recorrer todos los géneros posibles dentro del conjunto
    int maxG = cantMaxTConjuntoGeneros(conjunto);
    for (int g = 0; g < maxG; g++) {
        if (perteneceTConjuntoGeneros(conjunto, g)) {
            // Filtrar libros de este género
            TABBLibros filtrados = filtradoPorGeneroTABBLibros(biblioteca->libros, g);

            // Copiar cada libro filtrado al árbol resultado
            int n = cantidadTABBLibros(filtrados);
            for (int i = 1; i <= n; i++) {
                TLibro libro = obtenerNesimoLibroTABBLibros(filtrados, i);
                insertarLibroTABBLibros(resultado, copiarTLibro(libro));
            }

            // Liberar árbol temporal filtrado
            liberarTABBLibros(filtrados);
        }
    }

    // 4) Liberar conjunto auxiliar de géneros
    liberarTConjuntoGeneros(conjunto);

    // 5) Devolver árbol final con todos los libros correspondientes
    return resultado;
}


