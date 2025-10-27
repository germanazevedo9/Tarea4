#include "../include/ldePrestamos.h"

struct nodoDoble{
    TPrestamo prestamo;
    nodoDoble* sig;
    nodoDoble* ant;
};

struct rep_ldePrestamos {
    nodoDoble* inicio;
    nodoDoble* final;
};

TLDEPrestamos crearTLDEPrestamosVacia(){
    TLDEPrestamos ldePrestamos = new rep_ldePrestamos;
    ldePrestamos->inicio = NULL;
    ldePrestamos->final = NULL;
    return ldePrestamos;
}

void insertarTLDEPrestamos(TLDEPrestamos &ldePrestamos, TPrestamo prestamo){
    if (ldePrestamos->inicio == NULL) {
    nodoDoble* nuevo = new nodoDoble;
    nuevo->prestamo = prestamo;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    ldePrestamos->inicio = nuevo;
    ldePrestamos->final = nuevo;
    return;
    }
    if (compararTFechas(fechaRetiroTPrestamo(prestamo), fechaRetiroTPrestamo(ldePrestamos->final->prestamo)) >= 0) {
        nodoDoble* nuevo = new nodoDoble;
        nuevo->prestamo = prestamo;
        nuevo->sig = NULL;
        nuevo->ant = ldePrestamos->final;
        ldePrestamos->final->sig = nuevo;
        ldePrestamos->final = nuevo;
        return;
    }
    if (compararTFechas(fechaRetiroTPrestamo(prestamo), fechaRetiroTPrestamo(ldePrestamos->inicio->prestamo)) < 0) {
        nodoDoble* nuevo = new nodoDoble;
        nuevo->prestamo = prestamo;
        nuevo->sig = ldePrestamos->inicio;
        nuevo->ant = NULL;
        ldePrestamos->inicio->ant = nuevo;
        ldePrestamos->inicio = nuevo;
        return;
    }
    nodoDoble* actual = ldePrestamos->inicio;
    while (actual != NULL && compararTFechas(fechaRetiroTPrestamo(prestamo), fechaRetiroTPrestamo(actual->prestamo)) >= 0) {
        actual = actual->sig;
    }  
    nodoDoble* nuevo = new nodoDoble;
    nuevo->prestamo = prestamo;
    nuevo->sig = actual;
    nuevo->ant = actual->ant;
    actual->ant->sig = nuevo;
    actual->ant = nuevo;
    return;
}

void liberarTLDEPrestamos(TLDEPrestamos &ldePrestamos){
    if (ldePrestamos == NULL) return; // Si ya está liberada, no hacer nada
    nodoDoble* actual = ldePrestamos->inicio;
    while (actual != NULL) {
        nodoDoble* siguiente = actual->sig;
        liberarTPrestamo(actual->prestamo); // Libera el préstamo
        delete actual; // Libera el nodo
        actual = siguiente;
    }
    delete ldePrestamos; // Libera la estructura principal
    ldePrestamos = NULL;
}

void imprimirTLDEPrestamos(TLDEPrestamos ldePrestamos){
    printf("LDE Préstamos:\n");
    if (ldePrestamos == NULL) return;
    nodoDoble* actual = ldePrestamos->inicio;
    while (actual != NULL) {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->sig;
    }
}

void imprimirInvertidoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    printf("LDE Préstamos:\n");
    if (ldePrestamos == NULL) return;
    nodoDoble* actual = ldePrestamos->final;
    while (actual != NULL) {
        imprimirTPrestamo(actual->prestamo);
        actual = actual->ant;
    }
}

nat cantidadRec(nodoDoble* nodo) {
    if (nodo == NULL) return 0;
    return 1 + cantidadRec(nodo->sig);
}

nat cantidadTLDEPrestamos(TLDEPrestamos ldePrestamos){
    if (ldePrestamos == NULL) return 0;
    return cantidadRec(ldePrestamos->inicio);
}

TPrestamo obtenerPrimeroTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->inicio->prestamo;
}

TPrestamo obtenerUltimoTLDEPrestamos(TLDEPrestamos ldePrestamos){
    return ldePrestamos->final->prestamo;
}

TPrestamo obtenerNesimoTLDEPrestamos(TLDEPrestamos &ldePrestamos, int n){
    nat x;
    x=n;
    if (x==1) return ldePrestamos->inicio->prestamo;
    if (x==cantidadTLDEPrestamos(ldePrestamos)) return ldePrestamos->final->prestamo;
    nodoDoble* actual = ldePrestamos->inicio;
    int contador = 1;
    while (actual != NULL && contador < n) {
        actual = actual->sig;
        contador++;
    }
    if (actual != NULL) return actual->prestamo;
    return NULL; // Si n es mayor que la cantidad de préstamos, retornar NULL
}

// criterio = 0 -> prestamos retornados
// criterio = 1 -> prestamos no retornados
TLDEPrestamos filtrarPrestamosTLDEPrestamos(TLDEPrestamos &ldePrestamos, int criterio){
    TLDEPrestamos filtrada = crearTLDEPrestamosVacia();
    nodoDoble* actual = ldePrestamos->inicio;
    if(criterio == 0){
        while(actual != NULL){
            if(fueRetornadoTPrestamo(actual->prestamo)){
                TPrestamo prestamoCopia = copiarTPrestamo(actual->prestamo);
                insertarTLDEPrestamos(filtrada, prestamoCopia);
            
            }
            actual = actual->sig;
        }
    }
    if(criterio == 1){
        while(actual != NULL){
            if(!fueRetornadoTPrestamo(actual->prestamo)){
                TPrestamo prestamoCopia = copiarTPrestamo(actual->prestamo);
                insertarTLDEPrestamos(filtrada, prestamoCopia);
            }
            actual = actual->sig;
        }
    }
    return filtrada;
}

void liberarTLDEPrestamosSoloEstructura(TLDEPrestamos &ldePrestamos) {
    if (ldePrestamos == NULL || ldePrestamos->inicio == NULL) {
        delete ldePrestamos;
        ldePrestamos = NULL;
        return;
    }

    nodoDoble *nodo = ldePrestamos->inicio;
    ldePrestamos->inicio = nodo->sig;  // Avanza al siguiente

    liberarTPrestamoSoloEstructura(nodo->prestamo);
    delete nodo;

    liberarTLDEPrestamosSoloEstructura(ldePrestamos);  // Llamada recursiva
}