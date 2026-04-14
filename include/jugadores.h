#ifndef JUGADORES_H
#define JUGADORES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 21
#define MAX_USER 11
#define MAX_PASS 9
#define MAX_ID_OBJ 5
#define ARCHIVO_JUGADORES "ficheros/Jugadores.txt"

typedef struct {
    int id_jugador;
    char nomb_jugador[MAX_NOMBRE];
    char jugador[MAX_USER];
    char contrasena[MAX_PASS];
    char **inventario;
    int num_objetos;
} t_jugador;

typedef struct {
    t_jugador *jugadores;
    int num_jugadores;
} v_jugadores;

/* Gestión de fichero */
int cargarJugadores(v_jugadores *v);
int guardarJugadores(v_jugadores v);
int insertarJugadorArchivo(t_jugador j);

/* Gestión de jugadores */
int altaJugador(v_jugadores *v, t_jugador nuevo);
int generarNuevoIdJugador(v_jugadores v);

/* Búsquedas */
int buscarJugadorPorId(v_jugadores v, int id_jugador);
int buscarJugadorPorUsername(v_jugadores v, const char usuario[]);
int existeJugadorPorUsername(v_jugadores v, const char usuario[]);
int existeJugadorPorId(v_jugadores v, int id_jugador);

/* Visualización */
void mostrarJugador(t_jugador j);
void listarJugadores(v_jugadores v);

/* Memoria */
void liberarJugadores(v_jugadores *v);

/* Gestion de objetos */
int agregarObjetoAJugador(t_jugador *j, const char *id_obj);
int quitarObjetoAJugador(t_jugador *j, const char *id_obj);
int tieneObjetoJugador(t_jugador j, const char *id_obj);
#endif

/*
Cambios realizados:
- Añadido struct t_jugador con inventario dinámico y num_objetos
- Modificado struct t_jugador para usar inventario con memoria dinámica
- Añadido struct v_jugadores
- Modificado struct v_jugadores para gestionar el conteo de jugadores dinámicamente
- Añadidas funciones de gestión de fichero: cargarJugadores, guardarJugadores, insertarJugadorArchivo
- Modificada la gestión de fichero con memoria dinámica para cargar/guardar inventarios
- Añadidas funciones de gestión de jugadores: altaJugador, generarNuevoIdJugador
- Añadidas funciones de búsqueda: buscarJugadorPorId, buscarJugadorPorUsername, existeJugadorPorUsername, existeJugadorPorId
- Añadidas funciones de visualización: mostrarJugador, listarJugadores
- Añadida función de liberación de memoria: liberarJugadores
- Añadidas funciones de gestión de objetos: agregarObjetoAJugador, quitarObjetoAJugador, tieneObjetoJugador
- Modificada la gestión de inventario para usar memoria dinámica al añadir/quitar objetos
*/