
#include "../include/prestamo.h"

struct rep_prestamo {
  TSocio socio;
  TLibro libro;
  TFecha fechaRetiro;
  TFecha fechaDevolucion;
};

TPrestamo crearTPrestamo(TSocio socio, TLibro libro, TFecha fechaRetiro){
  TPrestamo nuevoPrestamo = new rep_prestamo;
  nuevoPrestamo->socio = socio;
  nuevoPrestamo->libro = libro;
  nuevoPrestamo->fechaRetiro = fechaRetiro;
  nuevoPrestamo->fechaDevolucion = NULL;
  return nuevoPrestamo;
}
 
void imprimirTPrestamo(TPrestamo prestamo){
  printf("Préstamo de libro %s a %s %s.\n",tituloTLibro(prestamo->libro),nombreTSocio(prestamo->socio), apellidoTSocio(prestamo->socio));
  imprimirTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolucion != NULL){
    imprimirTFecha(prestamo->fechaDevolucion);
  } else {
    printf("No retornado\n");
  }
}

void liberarTPrestamo(TPrestamo &prestamo){
  if (prestamo != NULL){
  liberarTSocio(prestamo->socio);
  liberarTLibro(prestamo->libro);
  liberarTFecha(prestamo->fechaRetiro);
  liberarTFecha(prestamo->fechaDevolucion);
  delete prestamo;
  prestamo = NULL;
  }

}

TSocio socioTPrestamo(TPrestamo prestamo){
  return prestamo->socio;
}
 
TFecha fechaRetiroTPrestamo(TPrestamo prestamo){
  return prestamo->fechaRetiro;
}

TFecha fechaDevolucionTPrestamo(TPrestamo prestamo){
  TFecha fechaDevolucion = NULL;
  if (prestamo->fechaDevolucion != NULL){
    fechaDevolucion = prestamo->fechaDevolucion;
  }
  return fechaDevolucion;
}

TLibro libroTPrestamo(TPrestamo prestamo){
  return prestamo->libro;
}

bool fueRetornadoTPrestamo(TPrestamo prestamo){
  bool fueRetornado;
  fueRetornado = false;
  if (prestamo->fechaDevolucion != NULL){
    fueRetornado = true;
  }
  return fueRetornado;
}

void actualizarFechaDevolucionTPrestamo(TPrestamo prestamo, TFecha fechaDevolucion){
  if (prestamo->fechaDevolucion != NULL){
    liberarTFecha(prestamo->fechaDevolucion);
  }
  prestamo->fechaDevolucion = fechaDevolucion;
}

TPrestamo copiarTPrestamo(TPrestamo prestamo){
  TPrestamo copiaPrestamo = new rep_prestamo;
  copiaPrestamo->socio = copiarTSocio(prestamo->socio);
  copiaPrestamo->libro = copiarTLibro(prestamo->libro);
  copiaPrestamo->fechaRetiro = copiarTFecha(prestamo->fechaRetiro);
  if (prestamo->fechaDevolucion != NULL){
    copiaPrestamo->fechaDevolucion = copiarTFecha(prestamo->fechaDevolucion);
  } else {  
    copiaPrestamo->fechaDevolucion = NULL;
  }
  return copiaPrestamo;
}

void liberarTPrestamoSoloEstructura(TPrestamo &prestamo){
  if (prestamo != NULL) {
      liberarTFecha(prestamo->fechaRetiro);
      liberarTFecha(prestamo->fechaDevolucion);
      delete prestamo;
      prestamo = NULL;
  }
}