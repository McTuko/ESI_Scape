#ifndef JUGADORES_H
#define JUGADORES_H

#include <stdio.h>

#define MAX_JUGADORES 100
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
} Jugador;





int cargarJugadores(Jugador jugadores[], int max_jugadores);

int guardarJugadores(Jugador jugadores[], int num_jugadores);

int insertarJugadorArchivo(Jugador j);

int altaJugador(Jugador jugadores[], int *num_jugadores, Jugador nuevo);

int generarNuevoIdJugador(Jugador jugadores[], int num_jugadores);

int buscarJugadorPorId(Jugador jugadores[], int num_jugadores, int id_jugador);

int buscarJugadorPorUsername(Jugador jugadores[], int num_jugadores, const char usuario[]);

int existeJugadorPorUsername(Jugador jugadores[], int num_jugadores, const char usuario[]);

int existeJugadorPorId(Jugador jugadores[], int num_jugadores, int id_jugador);

void mostrarJugador(Jugador j);

void listarJugadores(Jugador jugadores[], int num_jugadores);

int consultarJugadorPorId(Jugador jugadores[], int num_jugadores, int id_jugador);




#endif