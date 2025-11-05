#include "../include/colaDePrioridadReservas.h"

// La cola de prioridad debe implementarse con un HEAP.

// NOTA IMPORTANTE: Para evitar diferencias con las salidas esperadas de los tests:
// * El filtrado ascendente debe parar cuando se encuentra un elemento igual o más prioritario que el elemento filtrado.
// * El filtrado descendente debe parar cuando los hijos del elemento filtrado sean igual o menos prioritarios que el.
// * Si se dan empates de prioridad entre los hijos durante el filtrado descendente y corresponde continuar filtrando,
// se debe seguir el filtrado hacia la rama izquierda.

struct rep_colaDePrioridadReservas {
    TReserva *colaDePrioridad;
    int maxReservas;
    int topeCola;
};

TColaDePrioridadReservas crearTColaDePrioridadReservas(nat N) {
    TColaDePrioridadReservas cp = new rep_colaDePrioridadReservas;
    cp->maxReservas = N;
    cp->topeCola = 0;  // cola vacía
    // Reservar espacio para N elementos (base 1)
    cp->colaDePrioridad = new TReserva[N + 1];

    // Inicializar a NULL
    for (int i = 0; i <= cp->maxReservas; i++) {
        cp->colaDePrioridad[i] = NULL;
    }

    return cp;
}

void liberarTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    // Liberar todas las reservas activas
    for (int i = 1; i <= cp->topeCola; i++) {
        liberarTReserva(cp->colaDePrioridad[i]);
        cp->colaDePrioridad[i] = NULL;
    }

    // Liberar el arreglo del heap
    delete[] cp->colaDePrioridad;

    // Liberar la estructura principal
    delete cp;

    // Dejar el puntero nulo por seguridad
    cp = NULL;
}


bool estaVaciaTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return cp->topeCola == 0;
};

void insertarTColaDePrioridadReservas(TColaDePrioridadReservas &cp, TReserva reserva) {
    // 1. hay espacio?
    if (cp->topeCola == cp->maxReservas) return;

    // 2. insertar al final
    cp->topeCola++;                      // pasa de 0→1, 1→2, etc.
    int pos = cp->topeCola;
    cp->colaDePrioridad[pos] =  reserva;

    // 3. heapify up (para MIN-HEAP, base 1)
    bool seguir = true;
    while (pos > 1 && seguir) {          // importante: > 1, no >= 1
        int padre = pos / 2;

        TSocio socioHijo  = socioTReserva(cp->colaDePrioridad[pos]);
        TSocio socioPadre = socioTReserva(cp->colaDePrioridad[padre]);
        int rangoHijo  = rangoTSocio(socioHijo);
        int rangoPadre = rangoTSocio(socioPadre);

        if (rangoHijo < rangoPadre) {
            // swap
            TReserva tmp = cp->colaDePrioridad[pos];
            cp->colaDePrioridad[pos] = cp->colaDePrioridad[padre];
            cp->colaDePrioridad[padre] = tmp;

            pos = padre;  // seguir subiendo
        } else {
            seguir = false;
        }
    }
}


void eliminarPrioritarioTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (estaVaciaTColaDePrioridadReservas(cp)) return;

    // 1. Guardar la reserva prioritaria y reemplazar con el último elemento
    TReserva reservaEliminada = cp->colaDePrioridad[1];
    cp->colaDePrioridad[1] = cp->colaDePrioridad[cp->topeCola];
    cp->topeCola--;

    // 2. Liberar la reserva eliminada (ahora ya no forma parte del heap)
    liberarTReserva(reservaEliminada);

    // 3. Reestructurar el montículo (heapify hacia abajo)
    int i = 1;
    bool enPosicion = false;

    while (!enPosicion && (2 * i <= cp->topeCola)) {
        int hijoIzq = 2 * i;
        int hijoDer = hijoIzq + 1;
        int hijoMenor = hijoIzq;

        // Encontrar el hijo con menor rango (mayor prioridad)
        if (hijoDer <= cp->topeCola) {
            TSocio socioIzq = socioTReserva(cp->colaDePrioridad[hijoIzq]);
            TSocio socioDer = socioTReserva(cp->colaDePrioridad[hijoDer]);
            int rangoIzq = rangoTSocio(socioIzq);
            int rangoDer = rangoTSocio(socioDer);

            if (rangoDer < rangoIzq) {
                hijoMenor = hijoDer;
            }
        }

        // Comparar con el padre actual
        TSocio socioPadre = socioTReserva(cp->colaDePrioridad[i]);
        TSocio socioHijo = socioTReserva(cp->colaDePrioridad[hijoMenor]);
        int rangoPadre = rangoTSocio(socioPadre);
        int rangoHijo = rangoTSocio(socioHijo);

        // Si el hijo tiene mayor prioridad (menor rango), intercambiar
        if (rangoHijo < rangoPadre) {
            TReserva temp = cp->colaDePrioridad[i];
            cp->colaDePrioridad[i] = cp->colaDePrioridad[hijoMenor];
            cp->colaDePrioridad[hijoMenor] = temp;
            i = hijoMenor; // continuar bajando
        } else {
            enPosicion = true; // ya está en la posición correcta
        }
    }
}


TReserva prioritarioTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    return cp->colaDePrioridad[1];
};

bool estaTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    for(int i=1;i<=cp->topeCola;i++){
        TSocio socioAComparar = socioTReserva(cp->colaDePrioridad[i]);
        TLibro libroAComparar = libroTReserva(cp->colaDePrioridad[i]);
        int ci = ciTSocio(socioAComparar);
        int isbn = isbnTLibro(libroAComparar);
        if(ci==ciSocio && isbn==isbnLibro) return true;
    }
    return false;
}

nat prioridadTColaDePrioridadReservas(TColaDePrioridadReservas cp, int ciSocio, int isbnLibro) {
    int i = 1;
    bool encontrado = false;
    nat prioridad = 0; // valor por defecto si no se encuentra

    while (i <= cp->topeCola && !encontrado) {
        TSocio socioAComparar = socioTReserva(cp->colaDePrioridad[i]);
        TLibro libroAComparar = libroTReserva(cp->colaDePrioridad[i]);
        
        int ci = ciTSocio(socioAComparar);
        int isbn = isbnTLibro(libroAComparar);
        
        if (ci == ciSocio && isbn == isbnLibro) {
            prioridad = rangoTSocio(socioAComparar);
            encontrado = true;  // para cortar el bucle
        } else {
            i++;
        }
    }

    return prioridad;
}
void insertarInvertido(TColaDePrioridadReservas &cp, TReserva reserva) {
    // 1. hay espacio?
    if (cp->topeCola == cp->maxReservas) return;

    // 2. insertar al final
    cp->topeCola++;                      // pasa de 0→1, 1→2, etc.
    int pos = cp->topeCola;
    cp->colaDePrioridad[pos] = reserva;


    bool seguir = true;
    while (pos > 1 && seguir) {          // importante: > 1, no >= 1
        int padre = pos / 2;

        TSocio socioHijo  = socioTReserva(cp->colaDePrioridad[pos]);
        TSocio socioPadre = socioTReserva(cp->colaDePrioridad[padre]);
        int rangoHijo  = rangoTSocio(socioHijo);
        int rangoPadre = rangoTSocio(socioPadre);

        if (rangoHijo > rangoPadre) {
            // swap
            TReserva tmp = cp->colaDePrioridad[pos];
            cp->colaDePrioridad[pos] = cp->colaDePrioridad[padre];
            cp->colaDePrioridad[padre] = tmp;

            pos = padre;  // seguir subiendo
        } else {
            seguir = false;
        }
    }
}

void invertirPrioridadTColaDePrioridadReservas(TColaDePrioridadReservas &cp) {
    if (cp->topeCola <= 1) return;
    
    TColaDePrioridadReservas invertido = crearTColaDePrioridadReservas(cp->maxReservas);
    
    TSocio socioPrioritario = socioTReserva(cp->colaDePrioridad[1]);
    TSocio socioSiguiente= socioTReserva(cp->colaDePrioridad[2]);
    int rangoPrioritario  = rangoTSocio(socioPrioritario);
    int rangoSiguiente = rangoTSocio(socioSiguiente);
    int i = cp->topeCola;
    if (rangoPrioritario<rangoSiguiente) {
        while (i >= 1) {
            insertarInvertido(invertido, copiarTReserva(cp->colaDePrioridad[i]));
            i--;
        }
    } else {        
        while (i >= 1) {
            insertarTColaDePrioridadReservas(invertido, copiarTReserva(cp->colaDePrioridad[i]));
            i--;
        }
    }
    liberarTColaDePrioridadReservas(cp);
    cp=invertido;
}


TColaDePrioridadReservas copiarTColaDePrioridadReservas(TColaDePrioridadReservas cp) {
    TColaDePrioridadReservas copiaCola = crearTColaDePrioridadReservas(cp->maxReservas);
    
    // Copiar el tope
    copiaCola->topeCola = cp->topeCola;
    
    // Copiar cada reserva individualmente
    for (int i = 1; i <= cp->topeCola; i++) {
        copiaCola->colaDePrioridad[i] = copiarTReserva(cp->colaDePrioridad[i]);
    }
    
    return copiaCola;
}

void imprimirTColaDePrioridad(TColaDePrioridadReservas cp) {
    for(int i=1;i<=cp->topeCola;i++){
        imprimirTReserva(cp->colaDePrioridad[i]);
    }
}


