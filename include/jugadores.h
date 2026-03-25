#ifndef JUGADORES_H
#define JUGADORES_H

#include <stdio.h>

#define MAX_NOMBRE 21
#define MAX_USER 11
#define MAX_PASS 9
#define MAX_OBJ 50
#define ARCHIVO_JUGADORES "Jugadores.txt"

typedef struct {
    int id_jugador;
    char nomb_jugador[MAX_NOMBRE];
    char jugador[MAX_USER];
    char contrasena[MAX_PASS];
    int inventario[MAX_OBJ];
    int num_objetos;
} t_jugador;

typedef struct {
    t_jugador *jugadores;
    int num_jugadores;
} v_jugadores;


int cargarJugadores(v_jugadores *v);

int guardarJugadores(v_jugadores v);

int insertarJugadorArchivo(t_jugador j);


int altaJugador(v_jugadores *v, t_jugador nuevo);

int generarNuevoIdJugador(v_jugadores v);

int buscarJugadorPorId(v_jugadores v, int id_jugador);

int buscarJugadorPorUsername(v_jugadores v, const char usuario[]);

int existeJugadorPorUsername(v_jugadores v, const char usuario[]);

int existeJugadorPorId(v_jugadores v, int id_jugador);

int consultarJugadorPorId(v_jugadores v, int id_jugador);

void mostrarJugador(t_jugador j);

void listarJugadores(v_jugadores v);

void liberarJugadores(v_jugadores *v);

#endif