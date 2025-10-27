#include "../include/fecha.h"

struct rep_fecha {
    /************ Parte 2.1 ************/
    /*Escriba el código a continuación */
    nat dia, mes, anio;
    /****** Fin de parte Parte 2.1 *****/
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    /************ Parte 3.1 ************/
    /*Escriba el código a continuación */
    TFecha nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    /****** Fin de parte Parte 3.1 *****/
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    /************ Parte 3.3 ************/
    if (fecha != NULL){/*Escriba el código a continuación */
    delete fecha;
    fecha = NULL;
    }
    /****** Fin de parte Parte 3.3 *****/
}
void imprimirTFecha(TFecha fecha) {
    /************ Parte 3.5 ************/
    /*Escriba el código a continuación */
    printf("%u/%u/%u\n", fecha->dia, fecha->mes, fecha->anio);

    /****** Fin de parte Parte 3.5 *****/
}

TFecha copiarTFecha(TFecha fecha) {
    /************ Parte 3.9 ************/
    /*Escriba el código a continuación */
    /*Recuerde que las funciones auxiliares
     deben declararse antes de ser utilizadas*/
    TFecha copia = new rep_fecha;
    copia->dia = fecha->dia;
    copia->mes = fecha->mes;
    copia->anio = fecha->anio;
 
    return copia;
    /****** Fin de parte Parte 3.9 *****/
}
/*31 dias: enero,marzo,mayo,julio,agosto,octubre,diciembre
30 dias:abril,junio,septiembre,noviembre*/
static nat diasMes(nat mes, nat anio){
    nat x ;
    if(((anio % 4 == 0) || (anio % 400 == 0)) && (anio % 100 != 0)){
        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                x = 31;
                break;
            case 4: case 6: case 9: case 11:
                x=30;
                break;
            case 2:
                x=29;
                break;
        };
    } else {
        switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            x = 31;
            break;
        case 4: case 6: case 9: case 11:
            x=30;
            break;
        case 2:
            x=28;
            break;
        };
    }
    return x;
};
void aumentarTFecha(TFecha &fecha, nat dias) {
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
    /****** Fin de parte Parte 3.10 *****/
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res ;
    /************ Parte 3.11 ************/
    /*Escriba el código a continuación */
    int fecha1_mayor_que_fecha2 =
    ((fecha1->anio > fecha2->anio) ||
    (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) ||
    (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia));
    switch (fecha1_mayor_que_fecha2)
    {
    case true:
        res =1;
        break;
    case false:
        if(fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia == fecha2->dia){
            res = 0;
        } else{
            res = -1;
        }
        break;
    }
    return res;
}

    /****** Fin de parte Parte 3.11 *****/
