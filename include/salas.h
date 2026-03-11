#ifndef SALAS_H
#define SALAS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void describirSala(t_sala);                 //Variables para cuando los objetos han sido recogidos
void entrarSala(t_sala, t_conexion);
int comprobarConexion(t_conexion, int);

void cargarSalas(FILE, t_sala*);
void guardarSalas(FILE*, t_sala);
void cargarConexiones(FILE, t_conexion*);
void guardarConexiones(FILE*, t_conexion);


typedef struct
{
    int id;
    char nombre[30];
    char tipo;
    char desc[150];
} t_sala;

typedef struct
{
    t_sala* sala;              //hacer vector dinamico
    int num_salas;
} v_salas;


typedef struct
{
    char id_cnx[3];
    int id_otg;
    int id_dst;
    int estado;
    char cond[4];
} t_conexion;

typedef struct
{
    t_conexion* conexion;      //hacer vector dinamico
    int num_conexiones;
} v_conexiones;



#endif


//Separa en tokens separados por -
//registro[i].edad = atoi(strtok(linea,"-"));
//strcpy(registro[i].nombre, strtok(NULL,"-"));
