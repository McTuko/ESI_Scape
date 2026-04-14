#include "../include/puzles.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void eliminarSaltoLinea(char *cadena){
    if (cadena != NULL)cadena[strcspn(cadena, "\n")] = '\0';
}

// Cargar puzles desde fichero
int cargarPuzles(const char *nombreFichero, t_puzle **puzles){
    FILE *f = fopen(nombreFichero, "r");
    char linea[300];
    int i = 0;

    *puzles = NULL;

    if (f == NULL){printf("Error: no se pudo abrir el fichero de puzles\n");return 0;}

    while (fgets(linea, sizeof(linea), f) != NULL){
        t_puzle *temp;
        char *token;

        eliminarSaltoLinea(linea);

        if (strlen(linea) == 0)continue;

        temp = realloc(*puzles, (i + 1) * sizeof(t_puzle));
        if (temp == NULL){
            printf("Error de memoria\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        *puzles = temp;

        token = strtok(linea, "-");
        if (token == NULL){
            printf("Error de formato en id del puzle\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        strncpy((*puzles)[i].id, token, MAX_ID_PUZLE - 1);
        (*puzles)[i].id[MAX_ID_PUZLE - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en nombre del puzle\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        strncpy((*puzles)[i].nombre, token, MAX_NOMBRE_P - 1);
        (*puzles)[i].nombre[MAX_NOMBRE_P - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en sala del puzle\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        (*puzles)[i].sala = atoi(token);

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en tipo del puzle\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        strncpy((*puzles)[i].tipo, token, MAX_TIPO_P - 1);
        (*puzles)[i].tipo[MAX_TIPO_P - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en descripcion del puzle\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        strncpy((*puzles)[i].descripcion, token, MAX_DESC_P - 1);
        (*puzles)[i].descripcion[MAX_DESC_P - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en solucion del puzle\n");
            free(*puzles);
            *puzles = NULL;
            fclose(f);
            return 0;
        }
        strncpy((*puzles)[i].solucion, token, MAX_SOL - 1);
        (*puzles)[i].solucion[MAX_SOL - 1] = '\0';

        (*puzles)[i].resuelto = 0;

        i++;
    }
    fclose(f);
    return i;
}

// Devuelve la posición de un puzle no resuelto en la sala
int hayPuzleSala(t_puzle *puzles, int n, int sala){
    int i;
    for (i = 0; i < n; i++){
        if (puzles[i].sala == sala && puzles[i].resuelto == 0) return i;
    }
    return -1;
}

// Buscar puzle por identificador
int buscarPuzlePorId(t_puzle *puzles, int n, const char *id){
    int i;

    for (i = 0; i < n; i++){
        if (strcmp(puzles[i].id, id) == 0) return i;
    }
    return -1;
}

// Mostrar información del puzle
void mostrarPuzle(t_puzle *p){
    printf("Puzle: %s\n", p->nombre);
    printf("%s\n", p->descripcion);
}

// Resolver puzle
int resolverPuzle(t_puzle *p, const char *respuesta){
    if (strcmp(p->solucion, respuesta) == 0){
        p->resuelto = 1;
        return 1;
    }
    return 0;
}

// Liberar memoria
void liberarPuzles(t_puzle **puzles){
    free(*puzles);
    *puzles = NULL;
}