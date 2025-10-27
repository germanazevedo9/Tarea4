#include "../include/libro.h"

struct rep_libro {
    int isbn;
    char titulo[MAX_TITULO];
    char nombre_autor[MAX_NOMBRE_AUTOR];
    char apellido_autor[MAX_APELLIDO_AUTOR];
    char descripcion[MAX_DESCRIPCION];
    int ID;
    TFecha fecha;
};

// Crea y retorna un elemento de tipo TLibro con los valores dados
TLibro crearTLibro(int isbn, const char titulo[MAX_TITULO], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], const char descripcion[MAX_DESCRIPCION], int idGeneroLibro, TFecha fechaEdicion){
    TLibro nuevolibro = new rep_libro;
    nuevolibro->isbn = isbn;
    strcpy(nuevolibro->titulo,titulo);
    strcpy(nuevolibro->nombre_autor,nombreAutor);
    strcpy(nuevolibro->apellido_autor,apellidoAutor);
    strcpy(nuevolibro->descripcion,descripcion);
    nuevolibro->ID = idGeneroLibro;
    nuevolibro->fecha = fechaEdicion;
    return nuevolibro;
}

// Libera la memoria asignada para el libro 'l'
// Debe liberar también la memoria de la fecha asociada
void liberarTLibro(TLibro &l){
    if (l != NULL){
        liberarTFecha(l->fecha);
        delete l;
        l = NULL;
    }
}

// Retorna el isbn del libro 'l'
int isbnTLibro(TLibro l){
    int x = l->isbn;
    return x;
}

// Retorna el titulo del libro 'l'
// El titulo retornado comparte memoria con el parámetro. 
char* tituloTLibro(TLibro l){
    char* a = l->titulo;
    return a;
}

// Retorna la descripción del libro 'l'
// La descripción retornada comparte memoria con el parámetro. 
char* descripcionTLibro(TLibro l){
    char* a = l->descripcion;
    return a; 
}

// Retorna el nombre del autor del libro 'l'
// El nombre retornado comparte memoria con el parámetro. 
char* nombreAutorTLibro(TLibro l){
    char* a = l->nombre_autor;
    return a;
}

// Retorna el apellido del autor del libro 'l'
// El apellido retornado comparte memoria con el parámetro. 
char* apellidoAutorTLibro(TLibro l){
    char* a = l->apellido_autor;
    return a;
}

// Retorna el id del género del libro 'l'
int idGeneroTLibro(TLibro l){
    int x = l->ID; 
    return x;
}

// Retorna la fecha de edición del libro 'l'.
// La fecha retornada comparte memoria con el parámetro. 
TFecha fechaEdicionTLibro(TLibro l){
    TFecha t = l->fecha;
    return t;
}

// Imprime la información del libro 'l' en el siguiente formato:
// Libro <isbn> 
// Título: <título>
// Autor: <nombre autor> <apellido autor>
// Descripción: <descripcion>
// Género: <id género>
// Fecha de edición: <fecha de edición>
void imprimirTLibro(TLibro l){
    printf("Libro %d\n", l->isbn);
    printf("Título: %s\n", l->titulo);
    printf("Autor: %s %s\n", l->nombre_autor, l->apellido_autor);
    printf("Descripción: %s\n", l->descripcion);
    printf("Género: %u\n", l->ID); 
    printf("Fecha de edición: ");
    imprimirTFecha(l->fecha);
}

// Retorna una copia del libro 'l' que no comparte memoria con el parámetro.
TLibro copiarTLibro(TLibro l){
    TFecha copiaFecha = copiarTFecha(l->fecha);
    TLibro copial = crearTLibro(l->isbn,l->titulo,l->nombre_autor,l->apellido_autor,l->descripcion,l->ID,copiaFecha);
    return copial;
}
