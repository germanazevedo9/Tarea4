#include "../include/tablaReserva.h"

// Se debe implementar mediante una tabla de dispersión abierta (hash)

struct rep_tablaTablaReserva {
    TColaDePrioridadReservas *colaDeReservaDeLibros;
    int maxElementos;
    int maxColas;
};


TTablaReserva crearTTablaReserva(int max, int N){
    TTablaReserva tabla = new rep_tablaTablaReserva;
    tabla->maxElementos = max;
    tabla->maxColas=N;
    tabla->colaDeReservaDeLibros = new TColaDePrioridadReservas[max + 1];
    for(int i=0;i<=max;i++){
        tabla->colaDeReservaDeLibros[i] = NULL;
    }
    return tabla;
}

void liberarTTablaReserva(TTablaReserva &tabla) {
    for (int i = 0; i <= tabla->maxElementos; i++) {
        TColaDePrioridadReservas cola = tabla->colaDeReservaDeLibros[i];
        if (cola != NULL ) {
            liberarTColaDePrioridadReservas(cola);
        }
    }
    delete[] tabla->colaDeReservaDeLibros;
    delete tabla;
}


void insertarTTablaReserva(TTablaReserva &tabla, int isbn, TReserva reserva){
    int indice = isbn % (tabla->maxElementos + 1);
    if(tabla->colaDeReservaDeLibros[indice]==NULL){
        tabla->colaDeReservaDeLibros[indice] = crearTColaDePrioridadReservas(tabla->maxColas);
    }
    insertarTColaDePrioridadReservas(tabla->colaDeReservaDeLibros[indice],reserva);
}


bool perteneceTTablaReserva(TTablaReserva tabla, int ciSocio, int isbnLibro) {
    int indice = isbnLibro % (tabla->maxElementos +1);
    if (tabla->colaDeReservaDeLibros[indice] == NULL) return false;
    return estaTColaDePrioridadReservas(tabla->colaDeReservaDeLibros[indice],ciSocio,isbnLibro);
}


TColaDePrioridadReservas obtenerReservaTTablaReserva(TTablaReserva tabla, int isbn){
    int indice = isbn % (tabla->maxElementos + 1);
    return tabla->colaDeReservaDeLibros[indice];
}

TReserva obtenerSigReservaTTablaReserva(TTablaReserva tabla, int isbn){
    return prioritarioTColaDePrioridadReservas(obtenerReservaTTablaReserva(tabla,isbn));
}

