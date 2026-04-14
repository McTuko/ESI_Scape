/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pruebas.h"

void inicializarPartida(t_prueba *partida) {
    // 1. Atributos básicos del héroe
    partida->id_jugador = 1;
    partida->id_sala = 1; // Comienza en la Gran Sala
    partida->datos = 0;

    // 2. Creación de Salas (3 Estancias)
    partida->salas.num_salas = 3;
    partida->salas.sala = (t_sala *)malloc(sizeof(t_sala) * partida->salas.num_salas);

    // Sala 1: El Torreón
    partida->salas.sala[0].id = 1;
    strcpy(partida->salas.sala[0].nombre, "Torreon del Destino");
    strcpy(partida->salas.sala[0].desc, "Un lugar frio y humedo custodiado por el codigo.");
    
    // Sala 2: La Armería
    partida->salas.sala[1].id = 2;
    strcpy(partida->salas.sala[1].nombre, "Armeria Real");
    strcpy(partida->salas.sala[1].desc, "Donde se forjan los punteros mas afilados.");

    // Sala 3: El Trono
    partida->salas.sala[2].id = 3;
    strcpy(partida->salas.sala[2].nombre, "Trono de Adriano");
    strcpy(partida->salas.sala[2].desc, "El centro del poder absoluto.");

    // 3. Creación de Objetos (Ítems)
    partida->items.num_items = 2;
    partida->items.item = (t_item *)malloc(sizeof(t_item) * partida->items.num_items);

    // Ítem 1: La Espada de C
    strcpy(partida->items.item[0].id, "IT01");
    strcpy(partida->items.item[0].nombre, "Espada de C");
    strcpy(partida->items.item[0].desc, "Brilla con un aura de gestion de memoria.");
    partida->items.item[0].localizacion = 2; // Está en la Armería

    // Ítem 2: El Gato de Oro
    strcpy(partida->items.item[1].id, "IT02");
    strcpy(partida->items.item[1].nombre, "Gato de Oro");
    strcpy(partida->items.item[1].desc, "Una efigie sagrada del Lord Gatito.");
    partida->items.item[1].localizacion = 3; // Está en el Trono

    // 4. Creación de Conexiones (Caminos entre salas)
    partida->conx.num_conexiones = 2;
    partida->conx.conexiones = (t_conexion *)malloc(sizeof(t_conexion) * partida->conx.num_conexiones);

    // Conexión: Torreón -> Armería
    strcpy(partida->conx.conexiones[0].id_cnx, "CX01");
    partida->conx.conexiones[0].id_org = 1;
    partida->conx.conexiones[0].id_dst = 2;
    partida->conx.conexiones[0].estado = 1; // Abierta (Abierta)

    // Conexión: Armería -> Trono
    strcpy(partida->conx.conexiones[1].id_cnx, "CX02");
    partida->conx.conexiones[1].id_org = 2;
    partida->conx.conexiones[1].id_dst = 3;
    partida->conx.conexiones[1].estado = 0; // Bloqueada (Requiere llave)

    // 5. Inicializar Jugadores (Espacio para el soberano)
    partida->jugadores.num_jugadores = 1;
    partida->jugadores.jugadores = (t_jugador *)malloc(sizeof(t_jugador));
    partida->jugadores.jugadores[0].id_jugador = 1;
    strcpy(partida->jugadores.jugadores[0].nomb_jugador, "Lord Adriano");
}*/