#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"
#include "postfija.h"

int main() {

    FILE* archivo = fopen("entrada.txt", "r");

    if(archivo == NULL) {

        printf("No se pudo abrir el archivo\n");

        return 1;
    }

    float variables[26] = {0};

    char linea[100];

    char variable;

    float valor;

    char expresion[100];

    while(fgets(linea, sizeof(linea), archivo)) {

        if(strchr(linea, '=')) {

            sscanf(linea, " %c = %f", &variable, &valor);

            variables[variable - 'a'] = valor;
        }

        else if(strlen(linea) > 1) {

            sscanf(linea, "%s", expresion);
        }
    }

    fclose(archivo);

    if(!parentesisBalanceados(expresion)) {

        printf("error, parentesis no balanceados\n");

        return 1;
    }

    Cola* postfija = infijaAPostfija(expresion);

    printf("expresion infija:\n");

    printf("%s\n\n", expresion);

    printf("expresion postfija:\n");

    mostrarCola(postfija);

    printf("\n");

    float resultado = evaluarPostfija(postfija, variables);

    printf("resultado:\n");

    printf("%.2f\n", resultado);

    liberarCola(postfija);

    free(postfija);

    return 0;
}