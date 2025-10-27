#include "../include/socio.h"

struct rep_socio {
    int ciSocio;
    char nombreSocio[MAX_NOMBRE_SOCIO];
    char apellidoSocio[MAX_APELLIDO_SOCIO];
    TFecha fechaAlta;
    struct rep_generos{
        int genfavs[MAX_GENEROS_FAVORITOS];
        int tope;
    }generos;
};
 
TSocio crearTSocio(int ci, const char nombre[MAX_NOMBRE_SOCIO], const char apellido[MAX_APELLIDO_SOCIO], nat diaAlta, nat mesAlta, nat anioAlta){
    TSocio nuevoSocio = new rep_socio;
    nuevoSocio->ciSocio = ci;
    strcpy(nuevoSocio->nombreSocio,nombre);
    strcpy(nuevoSocio->apellidoSocio,apellido);
    nuevoSocio->fechaAlta = crearTFecha(diaAlta,mesAlta,anioAlta);
    nuevoSocio->generos.tope=0;
    return nuevoSocio;
}
void imprimirGenerosDelSocio(TSocio socio){
    for (int i=0;i<socio ->generos.tope;i++){
        printf("%d ",socio->generos.genfavs[i]);
    };
    printf("\n");
};
void imprimirTSocio(TSocio socio){
    printf("Socio %d: %s %s\n", socio->ciSocio,socio->nombreSocio,socio->apellidoSocio);
    printf("Fecha de alta: " );
    imprimirTFecha(socio->fechaAlta);
    printf("Géneros favoritos: ");
    imprimirGenerosDelSocio(socio);
}

void liberarTSocio(TSocio &socio){
    if (socio != NULL){
    liberarTFecha(socio->fechaAlta);
    delete socio;
    socio = NULL;
    }
}

int ciTSocio(TSocio socio){
    int copiaCi = socio->ciSocio;
    return copiaCi;
}

char* nombreTSocio(TSocio socio){
    char* copiaNombre = socio->nombreSocio; 
    return copiaNombre;
}

char* apellidoTSocio(TSocio socio){
    char* copiaapellido = socio->apellidoSocio; 
    return copiaapellido;
}

TFecha fechaAltaTSocio(TSocio socio){
    TFecha copia = socio->fechaAlta;
    return copia;
}

void agregarGeneroFavoritoTSocio(TSocio &socio, int idGenero){
    int i=0;
    while ((i<socio->generos.tope) && (i!=MAX_GENEROS_FAVORITOS)){
        i++;
    }
    socio->generos.genfavs[i]= idGenero;
    socio->generos.tope++;
}

bool tieneGeneroFavoritoTSocio(TSocio socio, int idGenero){
    int i = 0;
    while ((i<socio->generos.tope) && (socio->generos.genfavs[i]!= idGenero)){
        i++;
    }
    
    return i<socio->generos.tope;
}

int cantidadGenerosFavoritosTSocio(TSocio socio){

    return socio->generos.tope;
}

TSocio copiarTSocio(TSocio socio){

    TSocio copiaSocio = new rep_socio;
    // opia los datos basicos del socio
    copiaSocio->ciSocio = socio->ciSocio;
    strcpy(copiaSocio->nombreSocio,socio->nombreSocio);
    strcpy(copiaSocio->apellidoSocio,socio->apellidoSocio);
    // Copia la fecha de alta
    TFecha copiaFechaAlta = copiarTFecha(socio->fechaAlta);
    copiaSocio->fechaAlta = copiaFechaAlta;

    // Copia los generos favoritos
    copiaSocio->generos.tope = socio->generos.tope;
    for(int i=0; i<socio->generos.tope;i++){
        copiaSocio->generos.genfavs[i] = socio->generos.genfavs[i];
    }
 
    return copiaSocio;
}
