#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "postfija.h"
#include "pila.h"

int esOperador(char c) {

    return c == '+' ||
           c == '-' ||
           c == '*' ||
           c == '/' ||
           c == '^';
}

int precedencia(char op) {

    switch(op) {

        case '^':
            return 3;

        case '*':
        case '/':
            return 2;

        case '+':
        case '-':
            return 1;

        default:
            return 0;
    }
}

int asociatividadDerecha(char op) {

    return op == '^';
}

int parentesisBalanceados(char* expresion) {

    Pila pila;

    inicializarPila(&pila);

    int i = 0;

    while(expresion[i] != '\0') {

        if(expresion[i] == '(') {

            push(&pila, '(');
        }

        else if(expresion[i] == ')') {

            if(pilaVacia(&pila)) {

                return 0;
            }

            pop(&pila);
        }

        i++;
    }

    int balanceados = pilaVacia(&pila);

    liberarPila(&pila);

    return balanceados;
}

Cola* infijaAPostfija(char* expresion) {

    Cola* salida = (Cola*) malloc(sizeof(Cola));

    if(salida == NULL) {

        printf("error de memoria\n");

        exit(1);
    }

    inicializarCola(salida);

    Pila operadores;

    inicializarPila(&operadores);

    int i = 0;

    while(expresion[i] != '\0') {

        char c = expresion[i];

        if(isalpha(c) || isdigit(c)) {

            enqueue(salida, c);
        }

        else if(c == '(') {

            push(&operadores, c);
        }

        else if(c == ')') {

            while(!pilaVacia(&operadores) &&
                  peek(&operadores) != '(') {

                enqueue(salida, (char) pop(&operadores));
            }

            pop(&operadores);
        }

        else if(esOperador(c)) {

            while(!pilaVacia(&operadores) &&
                  esOperador(peek(&operadores)) &&

                  (
                    precedencia(peek(&operadores))
                    > precedencia(c)

                    ||

                    (
                      precedencia(peek(&operadores))
                      == precedencia(c)

                      &&

                      !asociatividadDerecha(c)
                    )
                  )
            ) {

                enqueue(salida, (char) pop(&operadores));
            }

            push(&operadores, c);
        }

        i++;
    }

    while(!pilaVacia(&operadores)) {

        enqueue(salida, (char) pop(&operadores));
    }

    liberarPila(&operadores);

    return salida;
}

float evaluarPostfija(Cola* postfija, float variables[]) {

    Pila operandos;

    inicializarPila(&operandos);

    NodoCola* aux = postfija->frente;

    while(aux != NULL) {

        char c = aux->dato;

        if(isalpha(c)) {

            push(&operandos, variables[c - 'a']);
        }

        else if(isdigit(c)) {

            push(&operandos, c - '0');
        }

        else if(esOperador(c)) {

            float b = pop(&operandos);

            float a = pop(&operandos);

            switch(c) {

                case '+':

                    push(&operandos, a + b);

                    break;

                case '-':

                    push(&operandos, a - b);

                    break;

                case '*':

                    push(&operandos, a * b);

                    break;

                case '/':

                    if(b == 0) {

                        printf("error, division entre cero\n");

                        exit(1);
                    }

                    push(&operandos, a / b);

                    break;

                case '^':

                    push(&operandos, pow(a, b));

                    break;
            }
        }

        aux = aux->siguiente;
    }

    float resultado = pop(&operandos);

    liberarPila(&operandos);

    return resultado;
}