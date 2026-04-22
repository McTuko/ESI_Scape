#include "../include/jugadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Funciones auxiliares para probar el programa */
void mostrarJugadorLocal(t_jugador j);
void listarJugadoresLocal(v_jugadores v);
void liberarJugadoresLocal(v_jugadores *v);
void anadirJugadorManual(v_jugadores *v);

int main() {
    v_jugadores v;
    int opcion;
    int cargados;

    v.jugadores = NULL;
    v.num_jugadores = 0;

    do {
        printf("\n=============================\n");
        printf("   MENU PRUEBA JUGADORES\n");
        printf("=============================\n");
        printf("1. Cargar jugadores desde archivo\n");
        printf("2. Mostrar jugadores cargados\n");
        printf("3. Anadir jugador manualmente en memoria\n");
        printf("4. Guardar jugadores en archivo\n");
        printf("5. Liberar memoria\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar(); /* limpiar '\n' del buffer */

        switch (opcion) {
            case 1:
                liberarJugadoresLocal(&v); /* por si ya había algo cargado */
                cargados = cargarJugadores(&v);
                if (cargados >= 0) {
                    printf("Se han cargado %d jugadores.\n", cargados);
                } else {
                    printf("No se pudieron cargar los jugadores.\n");
                }
                break;

            case 2:
                listarJugadoresLocal(v);
                break;

            case 3:
                anadirJugadorManual(&v);
                break;

            case 4:
                if (guardarJugadores(v)) {
                    printf("Jugadores guardados correctamente en %s\n", ARCHIVO_JUGADORES);
                } else {
                    printf("Error al guardar jugadores.\n");
                }
                break;

            case 5:
                liberarJugadoresLocal(&v);
                printf("Memoria liberada.\n");
                break;

            case 0:
                liberarJugadoresLocal(&v);
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 0);

    return 0;
}

/* Muestra un jugador */
void mostrarJugadorLocal(t_jugador j) {
    int i;

    printf("\n-------------------------\n");
    printf("ID: %02d\n", j.id_jugador);
    printf("Nombre: %s\n", j.nomb_jugador);
    printf("Usuario: %s\n", j.jugador);
    printf("Contrasena: %s\n", j.contrasena);
    printf("Inventario: ");

    if (j.num_objetos == 0) {
        printf("sin objetos");
    } else {
        for (i = 0; i < j.num_objetos; i++) {
            printf("%d", j.inventario[i]);
            if (i < j.num_objetos - 1) {
                printf(", ");
            }
        }
    }

    printf("\n");
}

/* Lista todos los jugadores */
void listarJugadoresLocal(v_jugadores v) {
    int i;

    if (v.num_jugadores == 0) {
        printf("No hay jugadores cargados.\n");
        return;
    }

    printf("\n===== LISTA DE JUGADORES =====\n");
    for (i = 0; i < v.num_jugadores; i++) {
        mostrarJugadorLocal(v.jugadores[i]);
    }
}

/* Libera la memoria reservada */
void liberarJugadoresLocal(v_jugadores *v) {
    if (v->jugadores != NULL) {
        free(v->jugadores);
        v->jugadores = NULL;
    }
    v->num_jugadores = 0;
}

/* Añade un jugador manualmente al vector dinámico */
void anadirJugadorManual(v_jugadores *v) {
    t_jugador nuevo;
    t_jugador *temp;
    int i;

    printf("Introduce ID del jugador: ");
    scanf("%d", &nuevo.id_jugador);
    getchar();

    printf("Introduce nombre completo: ");
    fgets(nuevo.nomb_jugador, MAX_NOMBRE, stdin);
    nuevo.nomb_jugador[strcspn(nuevo.nomb_jugador, "\n")] = '\0';

    printf("Introduce nombre de usuario: ");
    fgets(nuevo.jugador, MAX_USER, stdin);
    nuevo.jugador[strcspn(nuevo.jugador, "\n")] = '\0';

    printf("Introduce contrasena: ");
    fgets(nuevo.contrasena, MAX_PASS, stdin);
    nuevo.contrasena[strcspn(nuevo.contrasena, "\n")] = '\0';

    printf("Cuantos objetos tiene? ");
    scanf("%d", &nuevo.num_objetos);

    if (nuevo.num_objetos < 0) {
        nuevo.num_objetos = 0;
    }
    if (nuevo.num_objetos > MAX_OBJ) {
        nuevo.num_objetos = MAX_OBJ;
    }

    for (i = 0; i < nuevo.num_objetos; i++) {
        printf("Introduce ID del objeto %d: ", i + 1);
        scanf("%d", &nuevo.inventario[i]);
    }
    getchar();

    temp = realloc(v->jugadores, (v->num_jugadores + 1) * sizeof(t_jugador));
    if (temp == NULL) {
        printf("Error al reservar memoria.\n");
        return;
    }

    v->jugadores = temp;
    v->jugadores[v->num_jugadores] = nuevo;
    v->num_jugadores++;

    printf("Jugador anadido correctamente en memoria.\n");
}