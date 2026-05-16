#include <stdio.h>
#include <stdlib.h>

#include "pila.h"

void inicializarPila(Pila* p) {

    p->tope = NULL;
}

int pilaVacia(Pila* p) {

    return p->tope == NULL;
}

void push(Pila* p, float dato) {

    NodoPila* nuevo = (NodoPila*) malloc(sizeof(NodoPila));

    if(nuevo == NULL) {

        printf("error de memoria\n");
        exit(1);
    }

    nuevo->dato = dato;

    nuevo->siguiente = p->tope;

    p->tope = nuevo;
}

float pop(Pila* p) {

    if(pilaVacia(p)) {

        printf("error, pila vacia\n");
        exit(1);
    }

    NodoPila* aux = p->tope;

    float dato = aux->dato;

    p->tope = aux->siguiente;

    free(aux);

    return dato;
}

float peek(Pila* p) {

    if(pilaVacia(p)) {

        printf("error, pila vacia\n");
        exit(1);
    }

    return p->tope->dato;
}

void liberarPila(Pila* p) {

    while(!pilaVacia(p)) {

        pop(p);
    }
}