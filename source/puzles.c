#include "puzles.h"
#include <stdio.h>
#include <string.h>

int hayPuzleSala(t_puzle *puzles, int n, int sala) {
    for (int i = 0; i < n; i++) {
        if (puzles[i].sala == sala && !puzles[i].resuelto)
            return i;
    }
    return -1;
}

void mostrarPuzle(t_puzle *p) {
    printf("Puzle: %s\n", p->nombre);
    printf("%s\n", p->descripcion);
}

int resolverPuzle(t_puzle *p, char *respuesta) {
    if (strcmp(p->solucion, respuesta) == 0) {
        p->resuelto = 1;
        return 1;
    }
    return 0;
}