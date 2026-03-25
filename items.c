#include "items.h"
#include <stdlib.h>
#include <string.h>

int buscarObjeto(t_item *items, int n, char *id) {
    for (int i = 0; i < n; i++) {
        if (strcmp(items[i].id, id) == 0)
            return i;
    }
    return -1;
}

void mostrarObjetosSala(t_item *items, int n, int sala) {
    for (int i = 0; i < n; i++) {
        if (items[i].localizacion == sala) {
            printf("%s - %s\n", items[i].id, items[i].nombre);
        }
    }
}

void mostrarInventario(t_item *items, int n) {
    printf("Inventario:\n");
    for (int i = 0; i < n; i++) {
        if (items[i].localizacion == -1) {
            printf("%s - %s\n", items[i].id, items[i].nombre);
        }
    }
}

int cogerObjeto(t_item *items, int n, int sala, char *id) {
    int pos = buscarObjeto(items, n, id);

    if (pos == -1) return 0;

    if (items[pos].localizacion != sala) return 0;

    items[pos].localizacion = -1;
    return 1;
}

int soltarObjeto(t_item *items, int n, int sala, char *id) {
    int pos = buscarObjeto(items, n, id);

    if (pos == -1) return 0;

    if (items[pos].localizacion != -1) return 0;

    items[pos].localizacion = sala;
    return 1;
}