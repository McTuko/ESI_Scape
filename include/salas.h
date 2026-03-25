#ifndef SALAS_H
#define SALAS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


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


typedef struct
{
    char id_cnx[3];
    int id_org;
    int id_dst;
    int estado;
    char cond[4];
} t_conexion;

typedef struct
{
    t_conexion *conexion;
    int num_conexiones;
} v_conexiones;


void describirSala(t_sala);                 //Variables para cuando los objetos han sido recogidos
void entrarSala(t_sala, t_conexion);
int comprobarConexion(t_conexion, int);

void cargarSalas(v_salas*);
void guardarSalas(v_salas);
void cargarConexiones(v_conexiones*);
void guardarConexiones(v_conexiones);

void pruebaSalas();
void pruebaConexiones();


#endif


//Separa en tokens separados por -
//registro[i].edad = atoi(strtok(linea,"-"));
//strcpy(registro[i].nombre, strtok(NULL,"-"));
