#include "../include/conjuntoGeneros.h"

struct rep_conjuntogeneros{
  // Completar
  bool* presentes;   // arreglo de tamaño cantMax, indica si el id está en el conjunto
  int cantMax;       // cantidad máxima de elementos
  int cardinal;      // cantidad actual de elementos en el conjunto
};

TConjuntoGeneros crearTConjuntoGeneros(int cantMax){
  if (cantMax <= 0) return NULL;
  TConjuntoGeneros c = new rep_conjuntogeneros;
  c->cantMax = cantMax;
  c->cardinal = 0;
  c->presentes = new bool[cantMax];
  for (int i = 0; i < cantMax; i++) {
    c->presentes[i] = false;
  }
  return c;
}


void insertarTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (c == NULL) return;
  if (id < 0 || id >= c->cantMax) return;
  if (!c->presentes[id]) {
    c->presentes[id] = true;
    c->cardinal++;
  }
}

void imprimirTConjuntoGeneros(TConjuntoGeneros c){
  int impresos = 0;
  for (int i = 0; i < c->cantMax && impresos < c->cardinal; i++) {
    if (c->presentes[i]) {
      if (impresos > 0) printf(" ");
      printf("%d", i);
      impresos++;
    }
  }
  printf("\n");
}

void liberarTConjuntoGeneros(TConjuntoGeneros &c){
  delete[] c->presentes;
  delete c;
  c=NULL;
}

bool esVacioTConjuntoGeneros(TConjuntoGeneros c){
  return c->cardinal == 0;
}

int cardinalTConjuntoGeneros(TConjuntoGeneros c){
  return c->cardinal;
}

int cantMaxTConjuntoGeneros(TConjuntoGeneros c){
  return c->cantMax;
}

bool perteneceTConjuntoGeneros(TConjuntoGeneros c, int id){
  if (c == NULL) return false;
  if (id < 0 || id >= c->cantMax) return false;
  return c->presentes[id];
}

void borrarDeTConjuntoGeneros(TConjuntoGeneros &c, int id){
  if (c == NULL) return;
  if (id < 0 || id >= c->cantMax) return;
  if (!c->presentes[id]) return;
  c->presentes[id] = false;
  c->cardinal--;
}

TConjuntoGeneros unionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros res = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->presentes[i] || c2->presentes[i]) {
      insertarTConjuntoGeneros(res, i);
    }
  }
  return res;
}

TConjuntoGeneros interseccionTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros res = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->presentes[i] && c2->presentes[i]) {
      insertarTConjuntoGeneros(res, i);
    }
  }
  return res;
}

TConjuntoGeneros diferenciaTConjuntoGeneros(TConjuntoGeneros c1, TConjuntoGeneros c2){
  TConjuntoGeneros res = crearTConjuntoGeneros(c1->cantMax);
  for (int i = 0; i < c1->cantMax; i++) {
    if (c1->presentes[i] && !c2->presentes[i]) {
      insertarTConjuntoGeneros(res, i);
    }
  }
  return res;
}
