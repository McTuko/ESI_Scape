#ifndef SALAS_H
#define SALAS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/partida.h"
#include "../include/conexiones.h"

#define ARCHIVO_SALAS "../ficheros/salas.txt"
#define MAX_NOMBRE_SALA 30
#define MAX_TIPO_SALA 7
#define MAX_DESC_SALA 150

// Estructura salas
typedef struct
{
    int id;
    char nombre[MAX_NOMBRE_SALA + 1];
    char tipo[MAX_TIPO_SALA + 1];
    char desc[MAX_DESC_SALA + 1];
} t_sala;

typedef struct
{
    t_sala *sala;
    int num_salas;
} v_salas;

// Gestión ficheros
int cargarSalas(v_salas*);
int guardarSalas(v_salas);

// Demás
void entrarSala(int, int, v_conexiones, t_partida*);
void liberarSalas(v_salas*);
void mostrarSala(t_sala);
int buscarSalaPorId(v_salas, int);

// PRUEBAS============================================================================================
void inicializarSalas();
void imprimirSalas(v_salas);


#endif
