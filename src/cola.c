#include <stdio.h>
#include <stdlib.h>


#include "cola.h"


void inicializarCola(Cola* c) {

    c->frente = NULL;

    c->final = NULL;
}

int colaVacia(Cola* c) {

    return c->frente == NULL;
}

void enqueue(Cola* c, char dato) {

    NodoCola* nuevo = (NodoCola*) malloc(sizeof(NodoCola));

    if(nuevo == NULL) {

        printf("error de memoria\n");
        exit(1);
    }

    nuevo->dato = dato;

    nuevo->siguiente = NULL;

    if(colaVacia(c)) {

        c->frente = nuevo;

        c->final = nuevo;
    }

    else {

        c->final->siguiente = nuevo;

        c->final = nuevo;
    }
}

char dequeue(Cola* c) {

    if(colaVacia(c)) {

        printf("error, cola vacia\n");
        exit(1);
    }

    NodoCola* aux = c->frente;

    char dato = aux->dato;

    c->frente = aux->siguiente;

    if(c->frente == NULL) {

        c->final = NULL;
    }

    free(aux);

    return dato;
}


void mostrarCola(Cola* c) {

    NodoCola* aux = c->frente;

    while(aux != NULL) {

        printf("%c ", aux->dato);

        aux = aux->siguiente;
    }

    printf("\n");
}

void liberarCola(Cola* c) {

    while(!colaVacia(c)) {

        dequeue(c);
    }
}