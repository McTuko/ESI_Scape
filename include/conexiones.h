#ifndef CONEXIONES_H
#define CONEXIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_CNX 4
#define MAX_ESTADO 11
#define MAX_COND 10
#define ARCHIVO_CONEXIONES "ficheros/Conexiones.txt"

typedef struct
{
    char id_cnx[MAX_ID_CNX + 1];   // Ej: C01
    int id_org;                    // Id sala origen
    int id_dst;                    // Id sala destino
    char estado[MAX_ESTADO + 1];   // "Activa" o "Bloqueada"
    char cond[MAX_COND + 1];       // "0", "OB01", "P01", etc.
} t_conexion;

typedef struct
{
    t_conexion *conexiones;
    int num_conexiones;
} v_conexiones;

/* Gestión de memoria */
void inicializarVectorConexiones(v_conexiones *v);
void liberarConexiones(v_conexiones *v);

/* Gestión de fichero */
int cargarConexiones(v_conexiones *v);
int guardarConexiones(v_conexiones v);

/* Utilidades */
void imprimirConexiones(v_conexiones v);
int buscarConexion(int id_origen, int id_destino, v_conexiones v);
int existeConexion(int id_origen, int id_destino, v_conexiones v);
int conexionEstaActiva(int id_origen, int id_destino, v_conexiones v);
int desbloquearConexion(const char *id_cnx, v_conexiones *v);

/* Validación */
int estadoValido(const char *estado);
int conexionValida(t_conexion c);

//Dejo este para pruebas
void imprimirConexiones(v_conexiones);
#endif