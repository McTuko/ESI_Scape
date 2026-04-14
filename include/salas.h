#ifndef SALAS_H
#define SALAS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/conexiones.h"
#include "../include/partida.h"



#define MAX_NOMBRE_SALA 31
#define MAX_TIPO_SALA 8
#define MAX_DESC_SALA 151
#define ARCHIVO_SALAS "ficheros/Salas.txt"

// Estructura salas
typedef struct
{
    int id;
    char nombre[MAX_NOMBRE_SALA];
    char tipo[MAX_TIPO_SALA];      // "INICIAL", "NORMAL", "SALIDA"
    char desc[MAX_DESC_SALA];
} t_sala;

typedef struct
{
    t_sala *sala;
    int num_salas;
} v_salas;

// Gestión ficheros
int cargarSalas(v_salas *salas);
int guardarSalas(v_salas salas);

// Demás
void entrarSala(int, int, v_conexiones, t_partida*);
void freeSalas(v_salas *salas);
int buscarSalaPorId(v_salas salas, int id);
void mostrarSala(t_sala sala);

// PRUEBAS
void imprimirSalas(v_salas salas);

#endif