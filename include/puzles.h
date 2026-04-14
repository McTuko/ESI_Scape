#ifndef PUZLES_H
#define PUZLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_PUZLE 4
#define MAX_NOMBRE_P 16
#define MAX_TIPO_P 10
#define MAX_DESC_P 151
#define MAX_SOL 51
#define ARCHIVO_PUZLES "ficheros/Puzles.txt"

typedef struct {
    char id[MAX_ID_PUZLE];      // P01 + '\0'
    char nombre[MAX_NOMBRE_P];  // 15 + '\0'
    int sala;                   // id de la sala
    char tipo[MAX_TIPO_P];      // "Codigo" o "Palabra"
    char descripcion[MAX_DESC_P];
    char solucion[MAX_SOL];
    int resuelto;
} t_puzle;

/* Carga */
int cargarPuzles(const char *nombreFichero, t_puzle **puzles);

/* Utilidades */
int hayPuzleSala(t_puzle *puzles, int n, int sala);
int buscarPuzlePorId(t_puzle *puzles, int n, const char *id);
void mostrarPuzle(t_puzle *p);

/* Acciones */
int resolverPuzle(t_puzle *p, const char *respuesta);

/* Memoria */
void liberarPuzles(t_puzle **puzles);

#endif