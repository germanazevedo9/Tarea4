
#include "../include/agGeneros.h"
#include <assert.h>


struct rep_agGeneros {
  // Completar
  int idGenero;
  char nombreGenero[MAX_NOMBRE];
  rep_agGeneros* primerHijo;
  rep_agGeneros* siguienteHermano;
};

TAGGeneros crearTAGGeneros(){
  TAGGeneros nuevo = new rep_agGeneros;
  nuevo->idGenero = -1;
  strcpy(nuevo->nombreGenero, "");
  nuevo->primerHijo = NULL;
  nuevo->siguienteHermano = NULL;
  return nuevo;
}

void insertarGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGeneroPadre, int idGenero, const char nombreGenero[MAX_NOMBRE] ){
  if (arbolGeneros==NULL) return;
  if (idGeneroPadre == -1 || arbolGeneros->idGenero ==-1){
    arbolGeneros->idGenero = idGenero;
    strcpy(arbolGeneros->nombreGenero,nombreGenero);
  }
  else{
    if(arbolGeneros->idGenero != idGeneroPadre){
      insertarGeneroTAGGeneros(arbolGeneros->primerHijo,idGeneroPadre,idGenero,nombreGenero);
      insertarGeneroTAGGeneros(arbolGeneros->siguienteHermano,idGeneroPadre,idGenero,nombreGenero);

    }
    else{
      TAGGeneros nuevoHijo =crearTAGGeneros();
      nuevoHijo->idGenero = idGenero;
      strcpy(nuevoHijo->nombreGenero, nombreGenero);
      nuevoHijo->siguienteHermano= arbolGeneros->primerHijo;
      arbolGeneros->primerHijo=nuevoHijo;
    }
  }
}

void imprimirAux(TAGGeneros arbolGeneros, int nivel) {
    if (arbolGeneros == NULL || arbolGeneros->idGenero == -1) return;

    // Imprimir la sangría según el nivel
    for(int i = 0; i < nivel; i++) {
        printf("    "); // 4 espacios por nivel
    }

    // Imprimir el nodo actual con el formato correcto (espacio-guión-espacio)
    printf("%d - %s\n", arbolGeneros->idGenero, arbolGeneros->nombreGenero);

    // Recursión para los hijos (aumentando el nivel de sangría)
    imprimirAux(arbolGeneros->primerHijo, nivel + 1);
    
    // Recursión para los hermanos (manteniendo el mismo nivel de sangría)
    imprimirAux(arbolGeneros->siguienteHermano, nivel);
}

void imprimirTAGGeneros(TAGGeneros arbolGeneros) {
    if (arbolGeneros == NULL) return;
    printf("Árbol de géneros:\n");
    imprimirAux(arbolGeneros, 0);
}
void liberarTAGGeneros(TAGGeneros &arbolGeneros){
  if (arbolGeneros == NULL) return;
  TAGGeneros hijo = arbolGeneros->primerHijo;
  while (hijo != NULL) {
    TAGGeneros siguiente = hijo->siguienteHermano;
    liberarTAGGeneros(hijo);
    hijo = siguiente;
  }

  delete arbolGeneros;
  arbolGeneros = NULL;
}

bool existeGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
    if (arbolGeneros == NULL || arbolGeneros->idGenero == -1)
        return false;
    if (arbolGeneros->idGenero == idGenero)
        return true;
    // Buscar en los hijos
    if (existeGeneroTAGGeneros(arbolGeneros->primerHijo, idGenero))
        return true;
    // Buscar en los hermanos
    return existeGeneroTAGGeneros(arbolGeneros->siguienteHermano, idGenero);
}

nat alturaTAGGeneros(TAGGeneros arbolGeneros) {
    if (arbolGeneros == NULL || arbolGeneros->idGenero == -1)
        return 0;

    // Función recursiva para calcular la altura máxima entre los hijos
    nat alturaMaxHijos = 0;
    TAGGeneros hijo = arbolGeneros->primerHijo;
    while (hijo != NULL) {
        nat alturaHijo = alturaTAGGeneros(hijo);
        if (alturaHijo > alturaMaxHijos)
            alturaMaxHijos = alturaHijo;
        hijo = hijo->siguienteHermano;
    }
    return alturaMaxHijos + 1;
}

nat cantidadTAGGeneros(TAGGeneros arbolGeneros) {
  if (arbolGeneros == NULL || arbolGeneros->idGenero == -1)
    return 0;
  // Cuenta el nodo actual + los géneros en los hijos + los géneros en los hermanos
  return 1 + cantidadTAGGeneros(arbolGeneros->primerHijo) + cantidadTAGGeneros(arbolGeneros->siguienteHermano);  
}

void removerGeneroTAGGeneros(TAGGeneros &arbolGeneros, int idGenero) {
  if (arbolGeneros == NULL || arbolGeneros->idGenero == -1) return;

  // Caso especial: si el primer hijo es el que queremos eliminar
  TAGGeneros actual = arbolGeneros->primerHijo;
  TAGGeneros anterior = NULL;
  while (actual != NULL) {
    if (actual->idGenero == idGenero) {
      if (anterior == NULL) {
        // El primer hijo es el que se elimina
        arbolGeneros->primerHijo = actual->siguienteHermano;
      } else {
        // Un hijo intermedio o final
        anterior->siguienteHermano = actual->siguienteHermano;
      }
      liberarTAGGeneros(actual);
      return;
    }
    anterior = actual;
    actual = actual->siguienteHermano;
  }

  // Recursivamente en los hijos
  actual = arbolGeneros->primerHijo;
  while (actual != NULL) {
    removerGeneroTAGGeneros(actual, idGenero);
    actual = actual->siguienteHermano;
  }
}

char* nombreGeneroTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
    if (arbolGeneros == NULL || arbolGeneros->idGenero == -1)
        return NULL;

    if (arbolGeneros->idGenero == idGenero) {
        return arbolGeneros->nombreGenero;
    }

    // Buscar en el primer hijo (subárbol)
    char* res = nombreGeneroTAGGeneros(arbolGeneros->primerHijo, idGenero);
    if (res != NULL) return res;

    // Buscar en el siguiente hermano
    return nombreGeneroTAGGeneros(arbolGeneros->siguienteHermano, idGenero);
}

// TAGGeneros encontrandoSubArbol(TAGGeneros arbolGeneros, int idGenero){
//   if (arbolGeneros==NULL) return;
//   if(arbolGeneros->idGenero!=idGenero){
//     encontrandoSubArbol(arbolGeneros->primerHijo,idGenero);
//     encontrandoSubArbol(arbolGeneros->siguienteHermano,idGenero);
//   }
//   else {
//     return arbolGeneros;
//   }
// }
TAGGeneros obtenerSubarbolTAGGeneros(TAGGeneros arbolGeneros, int idGenero) {
    if (arbolGeneros == NULL || arbolGeneros->idGenero == -1)
        return NULL;
    if (arbolGeneros->idGenero == idGenero)
        return arbolGeneros;

    TAGGeneros res = obtenerSubarbolTAGGeneros(arbolGeneros->primerHijo, idGenero);
    if (res != NULL) return res;

    return obtenerSubarbolTAGGeneros(arbolGeneros->siguienteHermano, idGenero);
}

int obtenerMaxTAGGeneros(TAGGeneros arbolGeneros) {
    if (arbolGeneros == NULL || arbolGeneros->idGenero == -1)
        return -1; // Si el árbol está vacío, retorna -1

    int maxId = arbolGeneros->idGenero;

    int maxHijo = obtenerMaxTAGGeneros(arbolGeneros->primerHijo);
    int maxHermano = obtenerMaxTAGGeneros(arbolGeneros->siguienteHermano);

    if (maxHijo > maxId) maxId = maxHijo;
    if (maxHermano > maxId) maxId = maxHermano;

    return maxId;
}



// Función auxiliar recursiva para llenar el conjunto con todos los ids del subárbol
void llenarConjunto(TAGGeneros arbol, TConjuntoGeneros &conj) {
    if (arbol == NULL || arbol->idGenero == -1) return;
    insertarTConjuntoGeneros(conj, arbol->idGenero);
    llenarConjunto(arbol->primerHijo, conj);
    llenarConjunto(arbol->siguienteHermano, conj);
}

TConjuntoGeneros obtenerConjuntoGeneros(TAGGeneros arbolGeneros, int idGenero) {
    TAGGeneros subarbol = obtenerSubarbolTAGGeneros(arbolGeneros, idGenero);
    int maxId = obtenerMaxTAGGeneros(subarbol);
    TConjuntoGeneros conjunto = crearTConjuntoGeneros(maxId + 1);
    llenarConjunto(subarbol, conjunto);
    return conjunto;
}