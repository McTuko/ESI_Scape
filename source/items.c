#include "../include/items.h"
#include <stdlib.h>
#include <string.h>

int buscarObjeto(t_item *items, int n, const char *id) {
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

int cogerObjeto(t_item *items, int n, int sala, const char *id) {
    int pos = buscarObjeto(items, n, id);

    if (pos == -1) return 0;
    if (items[pos].localizacion != sala) return 0;

    items[pos].localizacion = -1;
    return 1;
}

int soltarObjeto(t_item *items, int n, int sala, const char *id) {
    int pos = buscarObjeto(items, n, id);

    if (pos == -1) return 0;
    if (items[pos].localizacion != -1) return 0;

    items[pos].localizacion = sala;
    return 1;
}

void cargarObjetos(v_items *items)
{
    FILE *f = fopen("../ficheros/items.txt", "r");
    if(f == NULL) {
        printf("Error: Archivo nulo\n");
        return;
    }

    char linea[250];
    int i = 0;
    items->item = NULL;

    while(fgets(linea, 250, f) != NULL){
        items->item = realloc(items->item, (i+1) * sizeof(t_item));

        char *token = strtok(linea, "-");
        strcpy(items->item[i].id, token);

        token = strtok(NULL, "-");
        strcpy(items->item[i].nombre, token);

        token = strtok(NULL, "-");
        strcpy(items->item[i].desc, token);

        token = strtok(NULL, "-\n");

        if (strcmp(token, "Inventario") == 0)
            items->item[i].localizacion = -1;
        else
            items->item[i].localizacion = atoi(token);

        i++;
    }

    items->num_items = i;
    fclose(f);
}