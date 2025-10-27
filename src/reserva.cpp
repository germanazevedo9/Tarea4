
#include "../include/reserva.h"

struct rep_reserva {
  TSocio socio;
  TLibro libro;
};

TReserva crearTReserva(TSocio socio, TLibro libro){
  TReserva reserva = new rep_reserva;
  reserva->libro=libro;
  reserva->socio=socio;
  return reserva;
}

void imprimirTReserva(TReserva reserva){
  printf("Reserva de libro %s por %s %s.\n",tituloTLibro(reserva->libro),nombreTSocio(reserva->socio),apellidoTSocio(reserva->socio));
}

void liberarTReserva(TReserva &reserva){
  if(reserva!=NULL){
    liberarTLibro(reserva->libro);
    liberarTSocio(reserva->socio);
    delete reserva;
    reserva=NULL;
  }

}

TSocio socioTReserva(TReserva reserva){
  return reserva->socio;
}

TLibro libroTReserva(TReserva reserva){
  return reserva->libro;
}

TReserva copiarTReserva(TReserva reserva){
  TReserva copiaReserva = new rep_reserva;
  copiaReserva->libro=copiarTLibro(reserva->libro);
  copiaReserva->socio=copiarTSocio(reserva->socio);

  return copiaReserva;
}

void liberarTReservaSoloEstructura(TReserva &reserva) {
  delete reserva;
  reserva =NULL;
}
