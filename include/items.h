#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_ITEM 5
#define MAX_NOMBRE_ITEM 16
#define MAX_DESC_I 51
#define ARCHIVO_ITEMS "ficheros/Objetos.txt"

typedef struct {
    char id[MAX_ID_ITEM];            // OB01
    char nombre[MAX_NOMBRE_ITEM];    // 15 + '\0'
    char desc[MAX_DESC_I];           // 50 + '\0'
    int localizacion;                // id sala o -1 inventario
} t_item;

typedef struct {
    t_item *item;
    int num_items;
} v_items;

/* Gestión de fichero */
int cargarItems(v_items *items);
int guardarItems(v_items items);

/* Mostrar */
void mostrarItemsSala(v_items *items, int sala);

/* Acciones */
int cogerItem(v_items *items, int sala, const char *id);
int soltarItem(v_items *items, int sala, const char *id);

/* Utilidades */
int buscarItem(v_items *items, const char *id);
void liberarItems(v_items *items);

#endif