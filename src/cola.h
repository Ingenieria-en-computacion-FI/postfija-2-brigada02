#ifndef COLA_H
#define COLA_H

typedef struct NodoCola {

    char dato;

    struct NodoCola* siguiente;

} NodoCola;

typedef struct {

    NodoCola* frente;

    NodoCola* final;

} Cola;

void inicializarCola(Cola* c);

void enqueue(Cola* c, char dato);

char dequeue(Cola* c);

int colaVacia(Cola* c);

void mostrarCola(Cola* c);

void liberarCola(Cola* c);

#endif