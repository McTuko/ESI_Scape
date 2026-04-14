#include "../include/partida.h"


/* ================== AUX ================== */

static void eliminarSaltoLinea(char *cad){
    if (cad != NULL){
        cad[strcspn(cad, "\n")] = '\0';
    }
}


/* ================== MEMORIA ================== */

void inicializarPartida(t_partida *p){
    p->id_jugador = 0;
    p->id_sala = 0;

    p->objetos = NULL;
    p->num_objetos = 0;

    p->conexiones = NULL;
    p->num_conexiones = 0;

    p->puzles = NULL;
    p->num_puzles = 0;

    p->datos = 0;
}


void liberarPartida(t_partida *p){
    free(p->objetos);
    free(p->conexiones);
    free(p->puzles);

    p->objetos = NULL;
    p->conexiones = NULL;
    p->puzles = NULL;

    p->num_objetos = 0;
    p->num_conexiones = 0;
    p->num_puzles = 0;
}


/* ================== CARGAR ================== */

int cargarPartida(t_partida *p){
    FILE *f = fopen(ARCHIVO_PARTIDA, "r");
    char linea[250];

    inicializarPartida(p);

    if (f == NULL){
        printf("Error: Archivo nulo\n");
        return 0;
    }

    while (fgets(linea, 250, f) != NULL){
        eliminarSaltoLinea(linea);

        if (strncmp(linea, "JUGADOR:", 8) == 0){
            p->id_jugador = atoi(linea + 8);
        }
        else if (strncmp(linea, "SALA:", 5) == 0){
            p->id_sala = atoi(linea + 5);
        }
        else if (strncmp(linea, "OBJETO:", 7) == 0){
            t_estado_objeto *temp;
            char *token;

            temp = realloc(p->objetos, (p->num_objetos + 1) * sizeof(t_estado_objeto));
            if (temp == NULL){
                printf("Error memoria\n");
                liberarPartida(p);
                fclose(f);
                return 0;
            }
            p->objetos = temp;

            token = strtok(linea + 7, "-");
            strcpy(p->objetos[p->num_objetos].id_obj, token);

            token = strtok(NULL, "-");

            if (strcmp(token, "Inventario") == 0)
                p->objetos[p->num_objetos].localizacion = -1;
            else
                p->objetos[p->num_objetos].localizacion = atoi(token);

            p->num_objetos++;
        }
        else if (strncmp(linea, "CONEXION:", 9) == 0){
            t_estado_conexion *temp;
            char *token;

            temp = realloc(p->conexiones, (p->num_conexiones + 1) * sizeof(t_estado_conexion));
            if (temp == NULL){
                printf("Error memoria\n");
                liberarPartida(p);
                fclose(f);
                return 0;
            }
            p->conexiones = temp;

            token = strtok(linea + 9, "-");
            strcpy(p->conexiones[p->num_conexiones].id_cnx, token);

            token = strtok(NULL, "-");
            strcpy(p->conexiones[p->num_conexiones].estado, token);

            p->num_conexiones++;
        }
        else if (strncmp(linea, "PUZLE:", 6) == 0){
            t_estado_puzle *temp;
            char *token;

            temp = realloc(p->puzles, (p->num_puzles + 1) * sizeof(t_estado_puzle));
            if (temp == NULL){
                printf("Error memoria\n");
                liberarPartida(p);
                fclose(f);
                return 0;
            }
            p->puzles = temp;

            token = strtok(linea + 6, "-");
            strcpy(p->puzles[p->num_puzles].id_puzle, token);

            token = strtok(NULL, "-");

            if (strcmp(token, "Resuelto") == 0)
                p->puzles[p->num_puzles].resuelto = 1;
            else
                p->puzles[p->num_puzles].resuelto = 0;

            p->num_puzles++;
        }
    }
    fclose(f);
    p->datos = 1;
    return 1;
}


/* ================== GUARDAR ================== */

int guardarPartida(t_partida p){
    FILE *f = fopen(ARCHIVO_PARTIDA, "w");

    if (f == NULL){
        printf("Error: Archivo nulo\n");
        return 0;
    }

    fprintf(f, "JUGADOR: %02d\n", p.id_jugador);
    fprintf(f, "SALA: %02d\n", p.id_sala);

    for (int i = 0; i < p.num_objetos; i++){
        if (p.objetos[i].localizacion == -1)
            fprintf(f, "OBJETO: %s-Inventario\n", p.objetos[i].id_obj);
        else
            fprintf(f, "OBJETO: %s-%02d\n",
                    p.objetos[i].id_obj,
                    p.objetos[i].localizacion);
    }

    for (int i = 0; i < p.num_conexiones; i++){
        fprintf(f, "CONEXION: %s-%s\n",
                p.conexiones[i].id_cnx,
                p.conexiones[i].estado);
    }

    for (int i = 0; i < p.num_puzles; i++){
        fprintf(f, "PUZLE: %s-%s\n",
                p.puzles[i].id_puzle,
                p.puzles[i].resuelto ? "Resuelto" : "Pendiente");
    }

    fclose(f);
    return 1;
}


/* ================== BUSCAR ================== */

int buscarObjetoPartida(t_partida p, const char *id){
    for (int i = 0; i < p.num_objetos; i++)
        if (strcmp(p.objetos[i].id_obj, id) == 0)
            return i;
    return -1;
}

int buscarConexionPartida(t_partida p, const char *id){
    for (int i = 0; i < p.num_conexiones; i++)
        if (strcmp(p.conexiones[i].id_cnx, id) == 0)
            return i;
    return -1;
}

int buscarPuzlePartida(t_partida p, const char *id){
    for (int i = 0; i < p.num_puzles; i++)
        if (strcmp(p.puzles[i].id_puzle, id) == 0)
            return i;
    return -1;
}


/* ================== ACTUALIZAR ================== */

int actualizarObjetoPartida(t_partida *p, const char *id, int loc){
    int pos = buscarObjetoPartida(*p, id);

    if (pos != -1){
        p->objetos[pos].localizacion = loc;
        return 1;
    }

    p->objetos = realloc(p->objetos, (p->num_objetos + 1) * sizeof(t_estado_objeto));
    strcpy(p->objetos[p->num_objetos].id_obj, id);
    p->objetos[p->num_objetos].localizacion = loc;
    p->num_objetos++;

    return 1;
}

int actualizarConexionPartida(t_partida *p, const char *id, const char *estado){
    int pos = buscarConexionPartida(*p, id);

    if (pos != -1){
        strcpy(p->conexiones[pos].estado, estado);
        return 1;
    }

    p->conexiones = realloc(p->conexiones, (p->num_conexiones + 1) * sizeof(t_estado_conexion));
    strcpy(p->conexiones[p->num_conexiones].id_cnx, id);
    strcpy(p->conexiones[p->num_conexiones].estado, estado);
    p->num_conexiones++;

    return 1;
}

int actualizarPuzlePartida(t_partida *p, const char *id, int resuelto){
    int pos = buscarPuzlePartida(*p, id);

    if (pos != -1){
        p->puzles[pos].resuelto = resuelto;
        return 1;
    }

    p->puzles = realloc(p->puzles, (p->num_puzles + 1) * sizeof(t_estado_puzle));
    strcpy(p->puzles[p->num_puzles].id_puzle, id);
    p->puzles[p->num_puzles].resuelto = resuelto;
    p->num_puzles++;

    return 1;
}


/* ================== PRINT ================== */

void imprimirPartida(t_partida p){
    printf("Jugador: %d\n", p.id_jugador);
    printf("Sala: %d\n", p.id_sala);

    for (int i = 0; i < p.num_objetos; i++)
        printf("OBJ %s -> %d\n", p.objetos[i].id_obj, p.objetos[i].localizacion);

    for (int i = 0; i < p.num_conexiones; i++)
        printf("CNX %s -> %s\n", p.conexiones[i].id_cnx, p.conexiones[i].estado);

    for (int i = 0; i < p.num_puzles; i++)
        printf("PZL %s -> %d\n", p.puzles[i].id_puzle, p.puzles[i].resuelto);
}