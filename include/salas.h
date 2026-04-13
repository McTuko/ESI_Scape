#ifndef SALAS_H
#define SALAS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/conexiones.h"
typedef struct t_partida t_partida;

// Estructura salas
typedef struct
{
    int id;
    char nombre[30];
    char tipo;
    char desc[150];
} t_sala;

typedef struct
{
    t_sala *sala;
    int num_salas;
} v_salas;

// Gestión ficheros
void cargarSalas(v_salas*);
void guardarSalas(v_salas);

//Demás
void entrarSala(int, int, v_conexiones, *t_partida);
void freeSalas(v_salas*);

// PRUEBAS============================================================================================
void inicializarSalas();
void imprimirSalas(v_salas);


#endif
