#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>

#define MAX_NOMBRE_ITEM 16
#define MAX_DESC_I 51

typedef struct {
    char id[5];                 // OB01
    char nombre[MAX_NOMBRE_ITEM];
    char desc[MAX_DESC_I];
    int localizacion;           // id sala o -1 inventario
} t_item;

typedef struct {
    t_item *item;
    int num_items;
} v_items;

// Carga desde fichero
void cargarItems(v_items *items);

// Mostrar
void mostrarItemsSala(v_items *items, int sala);
void mostrarInventario(v_items *items);

// Acciones
int cogerItem(v_items *items, int sala, const char *id);
int soltarItem(v_items *items, int sala, const char *id);

// Utilidades
int buscarItem(v_items *items, const char *id);

#endif