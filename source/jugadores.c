#include "../include/jugadores.h"
#include <stdlib.h>
#include <string.h>


int cargarJugadores(v_jugadores *v) {
    FILE *f;
    char linea[200];

    v->jugadores = NULL;
    v->num_jugadores = 0;

    f = fopen(ARCHIVO_JUGADORES, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    while (fgets(linea, sizeof(linea), f) != NULL) {
        char *token;
        t_jugador *temp;
        temp = realloc(v->jugadores, (v->num_jugadores + 1) * sizeof(t_jugador));
        if (temp == NULL) {
            printf("Error de memoria\n");
            free(v->jugadores);
            v->jugadores = NULL;
            v->num_jugadores = 0;
            fclose(f);
            return 0;
        }

        v->jugadores = temp;


        token = strtok(linea, "-");
        if (token == NULL) continue;
        v->jugadores[v->num_jugadores].id_jugador = atoi(token);


        token = strtok(NULL, "-");
        if (token == NULL) continue;
        strcpy(v->jugadores[v->num_jugadores].nomb_jugador, token);

        /* Usuario */
        token = strtok(NULL, "-");
        if (token == NULL) continue;
        strcpy(v->jugadores[v->num_jugadores].jugador, token);

        /* Contraseña */
        token = strtok(NULL, "-");
        if (token == NULL) continue;
        strcpy(v->jugadores[v->num_jugadores].contrasena, token);


        token = strtok(NULL, "-\n");
        v->jugadores[v->num_jugadores].num_objetos = 0;

        if (token != NULL) {
            char *obj = strtok(token, ",");

            while (obj != NULL &&
                   v->jugadores[v->num_jugadores].num_objetos < MAX_OBJ) {

                v->jugadores[v->num_jugadores]
                    .inventario[v->jugadores[v->num_jugadores].num_objetos] = atoi(obj);

                v->jugadores[v->num_jugadores].num_objetos++;
                obj = strtok(NULL, ",");
            }
        }

        v->num_jugadores++;
    }

    fclose(f);
    return v->num_jugadores;
}



int guardarJugadores(v_jugadores v) {
    FILE *f;
    int i, j;

    f = fopen(ARCHIVO_JUGADORES, "w");
    if (f == NULL) {
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    for (i = 0; i < v.num_jugadores; i++) {
        fprintf(f, "%02d-%s-%s-%s-",
                v.jugadores[i].id_jugador,
                v.jugadores[i].nomb_jugador,
                v.jugadores[i].jugador,
                v.jugadores[i].contrasena);

        for (j = 0; j < v.jugadores[i].num_objetos; j++) {
            fprintf(f, "%d", v.jugadores[i].inventario[j]);

            if (j < v.jugadores[i].num_objetos - 1) {
                fprintf(f, ",");
            }
        }

        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}