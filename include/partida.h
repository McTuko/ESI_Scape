#ifndef PARTIDA_H
#define PARTIDA_H
#include <stdlib.h>
#include <string.h>
#include "../include/items.h"
#include "../include/conexiones.h"
#include "../include/puzles.h"

typedef struct {
    int id_jugador;
    int id_sala;
    char id_item[5];
    int localizacion_item[20];      // id sala o -1 inventario
    int id_conexión;                // estructura dinamica a parte para objetos y conexiones
    int bool;                       // tiene datos guardados
} t_partida;

#endif