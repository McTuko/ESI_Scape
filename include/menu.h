#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jugadores.h"
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/items.h"
#include "../include/puzles.h"
#include "../include/partida.h"

#define MAX_RESPUESTA 100

/* ========================= LOGIN / REGISTRO ========================= */

int loginORegistro(v_jugadores *jugadores);
int registrarNuevoJugador(v_jugadores *jugadores);

/* ========================= PARTIDA NUEVA / CARGADA ========================= */

int buscarSalaInicial(v_salas salas);
void inicializarEstadoNuevaPartida(t_partida *partida,
                                    int id_jugador,
                                    int id_sala_inicial,
                                    v_items items,
                                    v_conexiones conx,
                                    t_puzle *puzles,
                                    int num_puzles);

void aplicarEstadoPartida(t_partida partida,
                           v_items *items,
                           v_conexiones *conx,
                           t_puzle *puzles,
                           int num_puzles,
                           t_jugador *jugador_actual);

void reconstruirInventarioJugadorDesdeItems(t_jugador *jugador, v_items items);

/* ========================= VISUALIZACION ========================= */

void mostrarInventarioJugadorActual(t_jugador jugador, v_items items);
void mostrarSalidasDesdeSala(int sala_actual, v_conexiones conx);
int esSalaSalida(v_salas salas, int id_sala);

/* ========================= ACCIONES ========================= */

int jugadorCogeObjeto(t_partida *partida,
                      t_jugador *jugador,
                      v_items *items,
                      int sala_actual,
                      const char *id_obj);

int jugadorSueltaObjeto(t_partida *partida,
                        t_jugador *jugador,
                        v_items *items,
                        int sala_actual,
                        const char *id_obj);

int usarObjetoEnConexion(t_partida *partida,
                          t_jugador jugador,
                          v_conexiones *conx,
                          int sala_actual,
                          const char *id_obj);

int resolverPuzleOConexion(t_partida *partida,
                            v_conexiones *conx,
                            t_puzle *puzles,
                            int num_puzles,
                            int sala_actual);

/* ========================= MENU DE PARTIDA ========================= */

void menuPartida(t_partida *partida,
                 t_jugador *jugador_actual,
                 v_salas salas,
                 v_conexiones *conx,
                 v_items *items,
                 t_puzle *puzles,
                 int num_puzles);

/* ========================= AUX GENERALES ========================= */

void limpiarBuffer(void);

#endif