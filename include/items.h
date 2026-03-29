#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>

#define MAX_NOMBRE 16
#define MAX_DESC 51

typedef struct {
    char id[5];                 // OB01
    char nombre[MAX_NOMBRE];
    char desc[MAX_DESC];
    int localizacion;           // id sala o -1 inventario
} t_item;

typedef struct {
    t_item *item;
    int num_items;
} v_items;

// Carga desde fichero
void cargarObjetos(v_items *items);

// Mostrar
void mostrarObjetosSala(t_item *items, int n, int sala);
void mostrarInventario(t_item *items, int n);

// Acciones
int cogerObjeto(t_item *items, int n, int sala, const char *id);
int soltarObjeto(t_item *items, int n, int sala, const char *id);

// Utilidades
int buscarObjeto(t_item *items, int n, const char *id);

#endif