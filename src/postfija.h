#ifndef POSTFIJA_H
#define POSTFIJA_H

#include "cola.h"

int esOperador(char c);

int precedencia(char op);

int asociatividadDerecha(char op);

int parentesisBalanceados(char* expresion);

Cola* infijaAPostfija(char* expresion);

float evaluarPostfija(Cola* postfija, float variables[]);

#endif