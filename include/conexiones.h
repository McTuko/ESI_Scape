#ifndef CONEXIONES_H
#define CONEXIONES_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Estructura conexiones
typedef struct
{
    char id_cnx[5];
    int id_org;
    int id_dst;
    int estado;
    char cond[50];
} t_conexion;

typedef struct
{
    t_conexion *conexion;
    int num_conexiones;
} v_conexiones;

// Gestión ficheros
void cargarConexiones(v_conexiones*);
void guardarConexiones(v_conexiones);

// Demás
int comprobarConexion(t_conexion, int);

// PRUEBAS===================================================================
void inicializarConexiones();
void imprimirConexiones(v_conexiones);


#endif