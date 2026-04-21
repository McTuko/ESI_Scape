#ifndef CONEXIONES_H
#define CONEXIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_CNX 4
#define MAX_ESTADO 11
#define MAX_COND 10
#define ARCHIVO_CONEXIONES "../ficheros/conexiones.txt"

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


// Gestión ficheros
int cargarConexiones(v_conexiones*);
int guardarConexiones(v_conexiones);

// Demás
void liberarConexiones(v_conexiones*);
int buscarConexion(int id_origen, int id_destino, v_conexiones);
int existeConexion(int id_origen, int id_destino, v_conexiones);
int conexionEstaActiva(int id_origen, int id_destino, v_conexiones);
int desbloquearConexion(const char *id_cnx, v_conexiones*);

// Validación
int estadoValido(const char *estado);
int conexionValida(t_conexion);

//Dejo este para pruebas
void imprimirConexiones(v_conexiones);


#endif