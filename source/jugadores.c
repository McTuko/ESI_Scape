#include "jugadores.h"
#include <stdlib.h>
#include <string.h>

int cargarJugadores(Jugador jugadores[], int max_jugadores) {
    FILE *f;
    char linea[200];
    int i = 0;

    f = fopen(ARCHIVO_JUGADORES, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    while (fgets(linea, sizeof(linea), f) != NULL && i < max_jugadores) {
        char *token;

        /* 1. ID del jugador */
        token = strtok(linea, "-");
        if (token == NULL) {
            continue;
        }
        jugadores[i].id_jugador = atoi(token);

        /* 2. Nombre completo */
        token = strtok(NULL, "-");
        if (token == NULL) {
            continue;
        }
        strcpy(jugadores[i].nomb_jugador, token);

        /* 3. Nombre de usuario */
        token = strtok(NULL, "-");
        if (token == NULL) {
            continue;
        }
        strcpy(jugadores[i].jugador, token);

        /* 4. Contraseña */
        token = strtok(NULL, "-");
        if (token == NULL) {
            continue;
        }
        strcpy(jugadores[i].contrasena, token);

        /* 5. Inventario */
        token = strtok(NULL, "-\n");
        jugadores[i].num_objetos = 0;

        if (token != NULL) {
            char *obj = strtok(token, ",");

            while (obj != NULL && jugadores[i].num_objetos < MAX_OBJ) {
                jugadores[i].inventario[jugadores[i].num_objetos] = atoi(obj);
                jugadores[i].num_objetos++;
                obj = strtok(NULL, ",");
            }
        }

        i++;
    }

    fclose(f);
    return i;
}

int guardarJugadores(Jugador jugadores[], int num_jugadores) {
    FILE *f;
    int i, j;

    f = fopen(ARCHIVO_JUGADORES, "w");
    if (f == NULL) {
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    for (i = 0; i < num_jugadores; i++) {
        fprintf(f, "%02d-%s-%s-%s-",
                jugadores[i].id_jugador,
                jugadores[i].nomb_jugador,
                jugadores[i].jugador,
                jugadores[i].contrasena);

        for (j = 0; j < jugadores[i].num_objetos; j++) {
            fprintf(f, "%d", jugadores[i].inventario[j]);

            if (j < jugadores[i].num_objetos - 1) {
                fprintf(f, ",");
            }
        }

        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}