
#include "../include/lseSocios.h"

struct rep_lseSocios {
	TSocio socio;
	rep_lseSocios* sig;
};

TLSESocios crearTLSESociosVacia(){
	TLSESocios lseSocios = new rep_lseSocios;
	lseSocios->socio = NULL;
	lseSocios->sig = NULL;
	return lseSocios;
}

bool esVaciaTLSESocios(TLSESocios lseSocios){
	return (lseSocios->socio == NULL && lseSocios->sig == NULL);
}

void imprimirTLSESocios(TLSESocios lseSocios){
	printf("Lista de Socios:\n");
	while (lseSocios != NULL && lseSocios->socio != NULL) {
		imprimirTSocio(lseSocios->socio);
		lseSocios = lseSocios->sig;
	}
}

void liberarTLSESocios(TLSESocios &lseSocios){
    if (lseSocios->sig != NULL) {
		liberarTLSESocios(lseSocios->sig);                         
    }
	if(lseSocios->socio != NULL){
		liberarTSocio(lseSocios->socio);
	}
	delete lseSocios;
    lseSocios = NULL;                     
}

void insertarTLSESocios(TLSESocios &lseSocios, TSocio socio) {
    // Si la lista (puntero) es NULL, crear primer nodo
    if (lseSocios == NULL) {
        lseSocios = new rep_lseSocios;
        lseSocios->socio = socio;
        lseSocios->sig   = NULL;
        return;
    }

    // Si usan un nodo cabecera “vacío”
    if (lseSocios->socio == NULL) {
        lseSocios->socio = socio;
        lseSocios->sig   = NULL;
        return;
    }

    // Si la fecha nueva es >= a la del nodo actual, avanzar (empates van después)
    if (compararTFechas(fechaAltaTSocio(socio),
                        fechaAltaTSocio(lseSocios->socio)) >= 0) {
        if (lseSocios->sig == NULL) {
            TLSESocios nuevo = new rep_lseSocios;
            nuevo->socio = socio;
            nuevo->sig   = NULL;
            lseSocios->sig = nuevo;   // <- ENLAZAR y listo (¡no borrar!)
        } else {
            insertarTLSESocios(lseSocios->sig, socio);
        }
    } else {
        // Insertar antes del actual: “empujar” el actual hacia adelante
        TLSESocios nuevo = new rep_lseSocios;
        nuevo->socio = lseSocios->socio;
        nuevo->sig   = lseSocios->sig;

        lseSocios->socio = socio;
        lseSocios->sig   = nuevo;     // <- ENLAZAR y listo (¡no borrar!)
    }
}

bool existeSocioTLSESocios(TLSESocios lseSocios, int ci){
	if (esVaciaTLSESocios(lseSocios)){return false;}
	while((lseSocios->sig != NULL)  && (ciTSocio(lseSocios->socio) != ci)){
		lseSocios = lseSocios->sig;
	}
	return (ciTSocio(lseSocios->socio) == ci);
}

TSocio obtenerSocioTLSESocios(TLSESocios lseSocios, int ci){
	while(ciTSocio(lseSocios->socio) != ci){
		lseSocios = lseSocios->sig;
	}
    return lseSocios->socio;
}

nat cantidadTLSESocios(TLSESocios lseSocios){
	if (lseSocios == NULL){return 0;}
	else return (1 + cantidadTLSESocios(lseSocios->sig));
}


TSocio obtenerNesimoTLSESocios(TLSESocios lseSocios, int n){
	nat x = n;
	if ((cantidadTLSESocios(lseSocios) < x)|| (n < 1)){return NULL;}
	int i=1;
	while (i<n){
		lseSocios = lseSocios->sig;
		i++;
	}
	return lseSocios->socio;
}



void removerSocioTLSESocios(TLSESocios &lseSocios, int ci){
    // Se asume lseSocios != NULL (tu código siempre crea la "cabeza")
    TLSESocios actual   = lseSocios;
    TLSESocios anterior = NULL;

    // Buscar el nodo a borrar (ojo si socio es NULL en cabeza vacía)
    while (actual != NULL && ciTSocio(actual->socio) != ci) {
        anterior = actual;
        actual   = actual->sig;
    }
    if (actual == NULL) return; // por si acaso

    if (anterior == NULL) { // borrar en la cabeza
        if (actual->sig == NULL) {
            // Era el único elemento: dejamos la cabeza "vacía"
            liberarTSocio(actual->socio);
            actual->sig   = NULL;
        } else {
            // Hay más nodos: movemos datos del siguiente a la cabeza y borramos el siguiente
            TLSESocios siguiente = actual->sig;

            // liberar socio previo de la cabeza
            liberarTSocio(actual->socio);

            // mover campos del siguiente
            actual->socio = siguiente->socio; // NO liberar: pasa a ser de 'actual'
            actual->sig   = siguiente->sig;

            delete siguiente; // liberamos solo el nodo, no el socio movido
        }
    } else {
        // borrar en medio/fin
        anterior->sig = actual->sig;
        liberarTSocio(actual->socio);
        delete actual;
    }
}