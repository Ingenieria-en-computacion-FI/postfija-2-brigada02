#ifndef PILA_H
#define PILA_H

typedef struct NodoPila {
    float dato;
    struct NodoPila* siguiente;
} NodoPila;

typedef struct {
    NodoPila* tope;
} Pila;

void inicializarPila(Pila* p);

void push(Pila* p, float dato);

float pop(Pila* p);

float peek(Pila* p);

int pilaVacia(Pila* p);

void liberarPila(Pila* p);

#endif