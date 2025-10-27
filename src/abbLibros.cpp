
#include "../include/abbLibros.h"

struct rep_abbLibros {
    TLibro libro;
    rep_abbLibros *izq;
    rep_abbLibros *der;
};

TABBLibros crearTABBLibrosVacio(){
    return NULL;
}

void insertarLibroTABBLibros(TABBLibros &abbLibros, TLibro libro){
    if (abbLibros == NULL) {
        abbLibros = new rep_abbLibros;
        abbLibros->libro = libro; 
        abbLibros->izq = NULL;
        abbLibros->der = NULL;
    } else if (isbnTLibro(libro) < isbnTLibro(abbLibros->libro)) {
        insertarLibroTABBLibros(abbLibros->izq, libro);
    } else {
        insertarLibroTABBLibros(abbLibros->der, libro);
    }
}

void imprimirTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) return;
    imprimirTABBLibros(abbLibros->izq);
    imprimirTLibro(abbLibros->libro);
    imprimirTABBLibros(abbLibros->der);
}

void liberarTABBLibros(TABBLibros &abbLibros){
    if (abbLibros == NULL) return;
    liberarTABBLibros(abbLibros->izq);
    liberarTABBLibros(abbLibros->der);
    liberarTLibro(abbLibros->libro);
    delete abbLibros;
    abbLibros = NULL;
}

bool existeLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if (abbLibros == NULL) return false;
    if (isbn == isbnTLibro(abbLibros->libro)) {
        return true;
    } else if (isbn < isbnTLibro(abbLibros->libro)) {
        return existeLibroTABBLibros(abbLibros->izq, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        return existeLibroTABBLibros(abbLibros->der, isbn);
    }
    return false;
}

TLibro obtenerLibroTABBLibros(TABBLibros abbLibros, int isbn){
    if (abbLibros == NULL) return NULL;
    if (isbn == isbnTLibro(abbLibros->libro)) {
        return abbLibros->libro;
    } else if (isbn < isbnTLibro(abbLibros->libro)) {
        return obtenerLibroTABBLibros(abbLibros->izq, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        return obtenerLibroTABBLibros(abbLibros->der, isbn);
    }
    return NULL;
}

nat alturaTABBLibros(TABBLibros abbLibros){
    if (abbLibros == NULL) return 0;
    nat alturaIzq = alturaTABBLibros(abbLibros->izq);
    nat alturaDer = alturaTABBLibros(abbLibros->der);
    if (alturaIzq > alturaDer) {
        return alturaIzq + 1;
    } else {
        return alturaDer + 1;
    }
    return 0;
}

TLibro maxISBNLibroTABBLibros(TABBLibros abbLibros){
    if (abbLibros->der != NULL) {
         return maxISBNLibroTABBLibros(abbLibros->der);
    } else {
        return abbLibros->libro;
    }
}

void removerLibroTABBLibros(TABBLibros &abbLibros, int isbn){
    if (abbLibros == NULL) return;
    if(isbn < isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->izq, isbn);
    } else if (isbn > isbnTLibro(abbLibros->libro)) {
        removerLibroTABBLibros(abbLibros->der, isbn);
    } else { // isbn == isbnTLibro(abbLibros->libro)
        if (abbLibros->izq == NULL && abbLibros->der == NULL) { // Caso 1: No tiene hijos
            liberarTLibro(abbLibros->libro);
            delete abbLibros;
            abbLibros = NULL;
        } else if (abbLibros->izq == NULL) { // Caso 2: Solo tiene hijo derecho
            TABBLibros temp = abbLibros;
            abbLibros = abbLibros->der;
            liberarTLibro(temp->libro);
            delete temp;
        } else if (abbLibros->der == NULL) { // Caso 2: Solo tiene hijo izquierdo
            TABBLibros temp = abbLibros;
            abbLibros = abbLibros->izq;
            liberarTLibro(temp->libro);
            delete temp;
        } else { // Caso 3: Tiene ambos hijos
            liberarTLibro(abbLibros->libro);
            abbLibros->libro = copiarTLibro(maxISBNLibroTABBLibros(abbLibros->izq));
            removerLibroTABBLibros(abbLibros->izq, isbnTLibro(abbLibros->libro));
        }
    }
}

int cantidadTABBLibros(TABBLibros abbLibros){
    if(abbLibros == NULL) return 0;
    else {
        return 1 + cantidadTABBLibros(abbLibros->izq) + cantidadTABBLibros(abbLibros->der);
    } 
}


void obtenerNesimoLibroTABBLibrosAux(TABBLibros abbLibros, int n, int &k, TLibro &res){
    if (k != n) {
        if (abbLibros->izq != NULL) {
            obtenerNesimoLibroTABBLibrosAux(abbLibros->izq, n, k, res);
        }
        k++;
        if (k == n) {
            res = abbLibros->libro;
        }
        if (abbLibros->der != NULL) {
            obtenerNesimoLibroTABBLibrosAux(abbLibros->der, n, k, res);
        }
    }
}

TLibro obtenerNesimoLibroTABBLibros(TABBLibros abbLibros, int n){
    if(n==cantidadTABBLibros(abbLibros)){
        return maxISBNLibroTABBLibros(abbLibros);
    }
    else if (n==1){
        if (abbLibros->izq == NULL) {
            return abbLibros->libro;
        } else {
            return obtenerNesimoLibroTABBLibros(abbLibros->izq, n);
        }
    } else {
        int k = 0;
        TLibro res = NULL;
        obtenerNesimoLibroTABBLibrosAux(abbLibros, n, k, res);
        return res;
    }
}


TABBLibros filtradoPorGeneroTABBLibros(TABBLibros abbLibros, int genero) {
    if (abbLibros == NULL) {
        return NULL;
    }
    
    TABBLibros izqFiltrado = filtradoPorGeneroTABBLibros(abbLibros->izq, genero);
    TABBLibros derFiltrado = filtradoPorGeneroTABBLibros(abbLibros->der, genero);
    
    if (idGeneroTLibro(abbLibros->libro) == genero) {
        TABBLibros nuevoNodo = new rep_abbLibros;
        nuevoNodo->libro = copiarTLibro(abbLibros->libro);
        nuevoNodo->izq = izqFiltrado;
        nuevoNodo->der = derFiltrado;
        return nuevoNodo;
    } else {
        if (izqFiltrado != NULL) {
            if (derFiltrado != NULL) {
                // Encontró en ambos subárboles, unirlos
                TABBLibros temp = izqFiltrado;
                while (temp->der != NULL) {
                    temp = temp->der;
                }
                temp->der = derFiltrado;
                return izqFiltrado;
            } else {
                return izqFiltrado;
            }
        } else {
            return derFiltrado;
        }
    }

}