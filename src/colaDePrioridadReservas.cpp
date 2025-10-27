#include "../include/colaDePrioridadReservas.h"

// La cola de prioridad debe implementarse con un HEAP.

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests:
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado.
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el.
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando,
// se debe seguir el filtrado hacia la rama izquierda.

struct rep_colaDePrioridadReservas {

};

/* El tiempo de ejecución en el peor caso es O(N). */
TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N) {
    return NULL;
}

/* Se pide que el tiempo de ejecución en el peor caso sea O(n*log n), siendo 'n' la cantidad de
elementos de 'cp'. Sin embargo, existe una solución que lo hace en O(n). */
void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {

}

/* El tiempo de ejecución en el peor caso es O(N), siendo 'N' el parámetro
pasado en crearCP. */
void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {

}

/* El tiempo de ejecución en el peor caso es O(log N) siendp 'N' el parámetro pasado en crearCP. */
void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva) {

}

/* El tiempo de ejecución en el peor caso es O(1). */
bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return false;
}

/* El tiempo de ejecución en el peor caso es O(1). */
TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return NULL;
}

/* El tiempo de ejecución en el peor caso es O(log N), siendo 'N' el parámetro
pasado en crearCP. */
void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {

}

/* El tiempo de ejecución en el peor caso es O(1). */
bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    return false;
}

/* El tiempo de ejecución en el peor caso es O(1). */
nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    return 0;
}

TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return NULL;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp) {

}


