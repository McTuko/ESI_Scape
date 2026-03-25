#include "../include/items.h"
#include <stdlib.h>
#include <string.h>

int buscarObjeto(t_item *items, int n, int *id) {
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

int cogerObjeto(t_item *items, int n, int sala, int *id) {
    int pos = buscarObjeto(items, n, id);

    if (pos == -1) return 0;

    if (items[pos].localizacion != sala) return 0;

    items[pos].localizacion = -1;
    return 1;
}

int soltarObjeto(t_item *items, int n, int sala, int *id) {
    int pos = buscarObjeto(items, n, id);

    if (pos == -1) return 0;

    if (items[pos].localizacion != -1) return 0;

    items[pos].localizacion = sala;
    return 1;
}

void cargarObjeto(v_items *items)
{
    FILE *f = fopen("../ficheros/items.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}
    char linea[250];
    int i=0;
    items->item = NULL;

    while(fgets(linea, 250, f) != NULL){
        items->item = realloc(items->item, (i+1) * sizeof(t_item));

        items->item[i].id = atoi(strtok(linea,"-"));
        strcpy(items->item[i].nombre, strtok(NULL,"-"));
        items->item[i].localizacion = (strtok(NULL, "-"))[0];       //[0] porque devuelve puntero (vector)
        strcpy(items->item[i].desc, strtok(NULL,"-"));
        i++;
    }
    items->num_items = i;
    
    fclose(f);
}