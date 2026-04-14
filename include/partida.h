#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_OBJ 5
#define MAX_ID_CNX_PARTIDA 5
#define MAX_ID_PUZLE 4
#define MAX_ESTADO_CNX 11
#define ARCHIVO_PARTIDA "ficheros/Partida.txt"

/* ================== ESTRUCTURAS ================== */

typedef struct
{
    char id_obj[MAX_ID_OBJ];
    int localizacion;   // id sala o -1 inventario
} t_estado_objeto;

typedef struct
{
    char id_cnx[MAX_ID_CNX_PARTIDA];
    char estado[MAX_ESTADO_CNX];   // "Activa" o "Bloqueada"
} t_estado_conexion;

typedef struct
{
    char id_puzle[MAX_ID_PUZLE];
    int resuelto;   // 1 resuelto, 0 pendiente
} t_estado_puzle;

/* IMPORTANTE para compatibilidad con salas.h */
typedef struct t_partida
{
    int id_jugador;
    int id_sala;

    t_estado_objeto *objetos;
    int num_objetos;

    t_estado_conexion *conexiones;
    int num_conexiones;

    t_estado_puzle *puzles;
    int num_puzles;

    int datos;
} t_partida;

/* ================== FUNCIONES ================== */

/* Memoria */
void inicializarPartida(t_partida *p);
void liberarPartida(t_partida *p);

/* Fichero */
int cargarPartida(t_partida *p);
int guardarPartida(t_partida p);

/* Utilidades */
int buscarObjetoPartida(t_partida p, const char *id);
int buscarConexionPartida(t_partida p, const char *id);
int buscarPuzlePartida(t_partida p, const char *id);

int actualizarObjetoPartida(t_partida *p, const char *id, int loc);
int actualizarConexionPartida(t_partida *p, const char *id, const char *estado);
int actualizarPuzlePartida(t_partida *p, const char *id, int resuelto);

void imprimirPartida(t_partida p);

#endif