#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jugadores.h"
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/items.h"
#include "../include/puzles.h"
#include "../include/partida.h"
#include "../include/menu.h"


/* ========================= PORTADA ========================= */

void portada()
{
    // Texto azul
    printf("\033[34m\n");
    printf("::::::::::  ::::::::  :::::::::::               ::::::::::  ::::::::   ::::::::      :::     :::::::::  ::::::::::\n");
    printf(":+:        :+:    :+:     :+:                   :-       :+    :+ :+    :+   :+ :+   :+    :+ :+:\n");
    printf("+:+        :+            :+                   :+        :+        :+         :+   :+  :+    :+ :+:\n");
    printf("+#++:++#   +#++:++#++     :+     +#++:++#++    +#++:++#   +#++:++#++ :+        +#++:++#++: +#++:++#+  +#++:++#\n");
    printf("+#+               :+     :+                   :+               :+ :+        :+     :+ :+        :+:\n");
    printf("#+#        #+#    :+     :+                   :+        #+#    :+ #+#    :+ #+#     :+ #+#        #+:\n");
    printf("##########  ########  ###########               ##########  ########   ########  ###     ### ###        ##########\n");
    printf("\033[0m");

    // Texto blanco
    printf("\033[37m");
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("\033[0m");
}


/* ========================= MAIN ========================= */

int main(void)
{
    v_jugadores jugadores;
    v_salas salas;
    v_conexiones conexiones;
    v_items items;
    t_puzle *puzles = NULL;
    int num_puzles = 0;

    t_partida partida;
    int pos_jugador;
    int opcion_principal;
    int sala_inicial;

    /* Carga inicial de datos */
    if (!cargarJugadores(&jugadores))
    {
        printf("Error al cargar Jugadores.txt\n");
        return 1;
    }

    if (!cargarSalas(&salas))
    {
        printf("Error al cargar Salas.txt\n");
        liberarJugadores(&jugadores);
        return 1;
    }

    if (!cargarConexiones(&conexiones))
    {
        printf("Error al cargar Conexiones.txt\n");
        liberarJugadores(&jugadores);
        liberarSalas(&salas);
        return 1;
    }

    if (!cargarItems(&items))
    {
        printf("Error al cargar Objetos.txt\n");
        liberarJugadores(&jugadores);
        liberarSalas(&salas);
        liberarConexiones(&conexiones);
        return 1;
    }

    num_puzles = cargarPuzles(ARCHIVO_PUZLES, &puzles);
    if (num_puzles == 0 && puzles == NULL)
    {
        printf("Error al cargar Puzles.txt\n");
        liberarJugadores(&jugadores);
        liberarSalas(&salas);
        liberarConexiones(&conexiones);
        liberarItems(&items);
        return 1;
    }

    printf("Bienvenido al juego\n");
    printf("ESI ESCAPE\n");

    /* Mostrar portada */
    portada();

    /* Login o registro */
    pos_jugador = loginORegistro(&jugadores);
    if (pos_jugador == -1)
    {
        printf("No se pudo iniciar sesion.\n");
        liberarJugadores(&jugadores);
        liberarSalas(&salas);
        liberarConexiones(&conexiones);
        liberarItems(&items);
        liberarPuzles(&puzles);
        return 1;
    }

    /* Menu principal */
    do
    {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Nueva partida\n");
        printf("2. Cargar partida\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion_principal);
        limpiarBuffer();

        switch (opcion_principal)
        {
            case 1:
                sala_inicial = buscarSalaInicial(salas);
                if (sala_inicial == -1)
                {
                    printf("No se ha encontrado una sala inicial.\n");
                    break;
                }

                inicializarEstadoNuevaPartida(&partida,
                                              jugadores.jugadores[pos_jugador].id_jugador,
                                              sala_inicial,
                                              items,
                                              conexiones,
                                              puzles,
                                              num_puzles);

                reconstruirInventarioJugadorDesdeItems(&jugadores.jugadores[pos_jugador], items);

                menuPartida(&partida,
                            &jugadores.jugadores[pos_jugador],
                            salas,
                            &conexiones,
                            &items,
                            puzles,
                            num_puzles);

                liberarPartida(&partida);
                break;

            case 2:
                if (!cargarPartida(&partida))
                {
                    printf("No se pudo cargar la partida.\n");
                    break;
                }

                if (partida.id_jugador != jugadores.jugadores[pos_jugador].id_jugador)
                {
                    printf("La partida guardada pertenece a otro jugador.\n");
                    liberarPartida(&partida);
                    break;
                }

                aplicarEstadoPartida(partida,
                                     &items,
                                     &conexiones,
                                     puzles,
                                     num_puzles,
                                     &jugadores.jugadores[pos_jugador]);

                menuPartida(&partida,
                            &jugadores.jugadores[pos_jugador],
                            salas,
                            &conexiones,
                            &items,
                            puzles,
                            num_puzles);

                liberarPartida(&partida);
                break;

            case 3:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion_principal != 3);

    /* Guardar y liberar recursos */
    guardarJugadores(jugadores);

    liberarJugadores(&jugadores);
    liberarSalas(&salas);
    liberarConexiones(&conexiones);
    liberarItems(&items);
    liberarPuzles(&puzles);

    return 0;
}
