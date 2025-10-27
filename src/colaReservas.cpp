#include "../include/colaReservas.h"

struct nododoble{
  TReserva reserva;
  nododoble* sig;
  nododoble* ant;
};

struct rep_colaReservas {
  int cantidad;
  nododoble* inicio;
  nododoble* final;
};

TColaReservas crearTColaReservas(){
    TColaReservas nuevo = new rep_colaReservas;
    nuevo->inicio = NULL;
    nuevo->final  = NULL;
    nuevo->cantidad = 0;   
    return nuevo;
}
void liberarTColaReservas(TColaReservas &colaReservas){
  if (colaReservas == NULL) return;
    
  if (colaReservas->inicio != NULL) {
        // Guardar el siguiente antes de borrar
    nododoble* siguiente = colaReservas->inicio->sig;
        // Liberar el nodo actual
    liberarTReserva(colaReservas->inicio->reserva);
    delete colaReservas->inicio;
    colaReservas->cantidad--;
        // Actualizar inicio al siguiente
    colaReservas->inicio = siguiente;
        // Llamada recursiva para el resto de la cola
    liberarTColaReservas(colaReservas);
  } else {
        // Ya no hay más nodos, liberar la estructura
    delete colaReservas;
    colaReservas = NULL;
  }
}

void encolarTColaReservas(TColaReservas &colaReservas, TReserva reserva){
    nododoble* n = new nododoble;
    n->reserva = reserva;
    n->sig = NULL;
    n->ant = NULL;
    
    if (colaReservas->inicio == NULL) {      // cola vacía
      colaReservas->cantidad = 1;  
      colaReservas->inicio = n;
      colaReservas->final  = n;
    } else {                                 // encolar al final
      colaReservas->cantidad++;
      n->ant = colaReservas->final;
      colaReservas->final->sig = n;
      colaReservas->final = n;
    }
}

void imprimirDesde(nododoble* p) {
  if (p == NULL) return;
  imprimirTReserva(p->reserva);
  imprimirDesde(p->sig);
}

void imprimirTColaReservas(TColaReservas colaReservas) {
  if (colaReservas == NULL || colaReservas->inicio == NULL) {
    printf("Cola de Reservas:\n");
    return;
  }
  printf("Cola de Reservas:\n");
  imprimirDesde(colaReservas->inicio);
}

nat cantidadTColaReservas(TColaReservas colaReservas){
    return colaReservas->cantidad;
}

TReserva frenteTColaReservas(TColaReservas colaReservas) {
    return colaReservas->inicio->reserva;
}

void desencolarTColaReservas(TColaReservas &colaReservas) {
    nododoble* eliminador = colaReservas->inicio;

    // avanzar inicio
    colaReservas->inicio = eliminador->sig;

    if (colaReservas->inicio == NULL) {
        // la cola quedó vacía
        colaReservas->final = NULL;
    } else {
        // hay más nodos; cortar el vínculo hacia atrás
        colaReservas->inicio->ant = NULL;
    }

    liberarTReserva(eliminador->reserva);
    delete eliminador;
    colaReservas->cantidad--;
}
void liberarTColaReservasSoloEstructura(TColaReservas &cola){
    if (cola == NULL) return;

    nododoble *cur = cola->inicio;
    while (cur != NULL) {
        nododoble *next = cur->sig;
        liberarTReservaSoloEstructura(cur->reserva);
        delete cur;
        cur = next;
    }
    cola->inicio = cola->final = NULL;
    cola->cantidad = 0;
    delete cola;
    cola = NULL;
}



TReserva extraerFrenteTColaReservas(TColaReservas &colaReservas) {
    nododoble* eliminador = colaReservas->inicio;

    // avanzar inicio
    colaReservas->inicio = eliminador->sig;

    if (colaReservas->inicio == NULL) {
        // la cola quedó vacía
        colaReservas->final = NULL;
    } else {
        // hay más nodos; cortar el vínculo hacia atrás
        colaReservas->inicio->ant = NULL;
    }
    TReserva laReserva = eliminador->reserva;
    delete eliminador;
    colaReservas->cantidad--;

  return laReserva;
}
