#include "../include/puzles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cargar puzles desde fichero
int cargarPuzles(const char *nombreFichero, t_puzle **puzles) {
    FILE *f = fopen(nombreFichero, "r");
    if (f == NULL) {
        printf("Error: no se pudo abrir el fichero de puzles\n");
        return 0;
    }

    char linea[300];
    int i = 0;
    *puzles = NULL;

    while (fgets(linea, sizeof(linea), f)) {
        *puzles = realloc(*puzles, (i + 1) * sizeof(t_puzle));
        if (*puzles == NULL) {
            printf("Error de memoria\n");
            fclose(f);
            return 0;
        }

        char *token = strtok(linea, "-");
        if (token == NULL) continue;
        strcpy((*puzles)[i].id, token);

        token = strtok(NULL, "-");
        if (token == NULL) continue;
        strcpy((*puzles)[i].nombre, token);

        token = strtok(NULL, "-");
        if (token == NULL) continue;
        (*puzles)[i].sala = atoi(token);

        token = strtok(NULL, "-");
        if (token == NULL) continue;
        strcpy((*puzles)[i].tipo, token);

        token = strtok(NULL, "-");
        if (token == NULL) continue;
        strcpy((*puzles)[i].descripcion, token);

        token = strtok(NULL, "-\n");
        if (token == NULL) continue;
        strcpy((*puzles)[i].solucion, token);

        // Inicialmente no resuelto
        (*puzles)[i].resuelto = 0;

        i++;
    }

    fclose(f);
    return i;
}


// Devuelve la posición de un puzle no resuelto en la sala (-1 si no hay)
int hayPuzleSala(t_puzle *puzles, int n, int sala) {
    for (int i = 0; i < n; i++) {
        if (puzles[i].sala == sala && puzles[i].resuelto == 0)
            return i;
    }
    return -1;
}


// Mostrar información del puzle
void mostrarPuzle(t_puzle *p) {
    printf("Puzle: %s\n", p->nombre);
    printf("%s\n", p->descripcion);
}


// Resolver puzle
int resolverPuzle(t_puzle *p, const char *respuesta) {
    if (strcmp(p->solucion, respuesta) == 0) {
        p->resuelto = 1;
        return 1;
    }
    return 0;
}