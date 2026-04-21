#include "../include/jugadores.h"


static void eliminarSaltoLinea(char *cadena){
    if (cadena != NULL) cadena[strcspn(cadena, "\n")] = '\0';
}

static void inicializarJugador(t_jugador *j){
    j->id_jugador = 0;
    j->nomb_jugador[0] = '\0';
    j->jugador[0] = '\0';
    j->contrasena[0] = '\0';
    j->inventario = NULL;
    j->num_objetos = 0;
}

static void liberarJugador(t_jugador *j){
    int i;

    if (j->inventario != NULL){
        for (i = 0; i < j->num_objetos; i++){
            free(j->inventario[i]);
        }
        free(j->inventario);
    }

    j->inventario = NULL;
    j->num_objetos = 0;
}

static int copiarJugador(t_jugador *destino, t_jugador origen){
    int i;

    inicializarJugador(destino);

    destino->id_jugador = origen.id_jugador;
    strcpy(destino->nomb_jugador, origen.nomb_jugador);
    strcpy(destino->jugador, origen.jugador);
    strcpy(destino->contrasena, origen.contrasena);

    for (i = 0; i < origen.num_objetos; i++){
        if (!agregarObjetoAJugador(destino, origen.inventario[i])){
            liberarJugador(destino);
            return 0;
        }
    }
    return 1;
}


int cargarJugadores(v_jugadores *v)
{
    FILE *f;
    char linea[200];

    v->jugadores = NULL;
    v->num_jugadores = 0;

    f = fopen(ARCHIVO_JUGADORES, "r");
    if (f == NULL){
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    while (fgets(linea, sizeof(linea), f) != NULL){
        char *token;
        t_jugador *temp;

        eliminarSaltoLinea(linea);

        if (strlen(linea) == 0){
            continue;
        }

        temp = realloc(v->jugadores, (v->num_jugadores + 1) * sizeof(t_jugador));
        if (temp == NULL){
            printf("Error de memoria\n");
            liberarJugadores(v);
            fclose(f);
            return 0;
        }

        v->jugadores = temp;

        inicializarJugador(&v->jugadores[v->num_jugadores]);

        token = strtok(linea, "-");
        if (token == NULL){
            continue;
        }
        v->jugadores[v->num_jugadores].id_jugador = atoi(token);

        token = strtok(NULL, "-");
        if (token == NULL){
            liberarJugador(&v->jugadores[v->num_jugadores]);
            continue;
        }
        strncpy(v->jugadores[v->num_jugadores].nomb_jugador, token, MAX_NOMBRE - 1);
        v->jugadores[v->num_jugadores].nomb_jugador[MAX_NOMBRE - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL) {
            liberarJugador(&v->jugadores[v->num_jugadores]);
            continue;
        }
        strncpy(v->jugadores[v->num_jugadores].jugador, token, MAX_USER - 1);
        v->jugadores[v->num_jugadores].jugador[MAX_USER - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            liberarJugador(&v->jugadores[v->num_jugadores]);
            continue;
        }
        strncpy(v->jugadores[v->num_jugadores].contrasena, token, MAX_PASS - 1);
        v->jugadores[v->num_jugadores].contrasena[MAX_PASS - 1] = '\0';

        token = strtok(NULL, "-");
        while (token != NULL) {
            if (!agregarObjetoAJugador(&v->jugadores[v->num_jugadores], token)){
                printf("Error de memoria al cargar inventario\n");
                liberarJugador(&v->jugadores[v->num_jugadores]);
                liberarJugadores(v);
                fclose(f);
                return 0;
            }

            token = strtok(NULL, "-");
        }

        v->num_jugadores++;
    }

    fclose(f);
    return v->num_jugadores;
}

int guardarJugadores(v_jugadores v){
    FILE *f;
    int i, j;

    f = fopen(ARCHIVO_JUGADORES, "w");
    if (f == NULL){
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    for (i = 0; i < v.num_jugadores; i++){
        fprintf(f, "%02d-%s-%s-%s",
                v.jugadores[i].id_jugador,
                v.jugadores[i].nomb_jugador,
                v.jugadores[i].jugador,
                v.jugadores[i].contrasena);

        for (j = 0; j < v.jugadores[i].num_objetos; j++){
            fprintf(f, "-%s", v.jugadores[i].inventario[j]);
        }

        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}


int insertarJugadorArchivo(t_jugador j){
    FILE *f;
    int i;

    f = fopen(ARCHIVO_JUGADORES, "a");
    if (f == NULL){
        printf("Error al abrir el archivo %s\n", ARCHIVO_JUGADORES);
        return 0;
    }

    fprintf(f, "%02d-%s-%s-%s",
            j.id_jugador,
            j.nomb_jugador,
            j.jugador,
            j.contrasena);

    for (i = 0; i < j.num_objetos; i++){
        fprintf(f, "-%s", j.inventario[i]);
    }

    fprintf(f, "\n");

    fclose(f);
    return 1;
}


int altaJugador(v_jugadores *v, t_jugador nuevo){
    t_jugador *temp;
    t_jugador copia;

    if (existeJugadorPorUsername(*v, nuevo.jugador)){
        return 0;
    }

    nuevo.id_jugador = generarNuevoIdJugador(*v);

    temp = realloc(v->jugadores, (v->num_jugadores + 1) * sizeof(t_jugador));
    if (temp == NULL){
        printf("Error de memoria\n");
        return 0;
    }

    v->jugadores = temp;

    if (!copiarJugador(&copia, nuevo)){
        printf("Error al copiar el jugador\n");
        return 0;
    }

    v->jugadores[v->num_jugadores] = copia;
    v->num_jugadores++;

    return 1;
}


int generarNuevoIdJugador(v_jugadores v){
    int max = 0;
    int i;

    for (i = 0; i < v.num_jugadores; i++){
        if (v.jugadores[i].id_jugador > max){
            max = v.jugadores[i].id_jugador;
        }
    }

    return max + 1;
}


int buscarJugadorPorId(v_jugadores v, int id_jugador){
    int i;

    for (i = 0; i < v.num_jugadores; i++){
        if (v.jugadores[i].id_jugador == id_jugador){
            return i;
        }
    }

    return -1;
}


int buscarJugadorPorUsername(v_jugadores v, const char usuario[]){
    int i;

    for (i = 0; i < v.num_jugadores; i++){
        if (strcmp(v.jugadores[i].jugador, usuario) == 0){
            return i;
        }
    }

    return -1;
}


int existeJugadorPorUsername(v_jugadores v, const char usuario[]){
    if (buscarJugadorPorUsername(v, usuario) != -1){
        return 1;
    }

    return 0;
}


int existeJugadorPorId(v_jugadores v, int id_jugador){
    if (buscarJugadorPorId(v, id_jugador) != -1){
        return 1;
    }

    return 0;
}


void mostrarJugador(t_jugador j){
    int i;

    printf("ID: %02d\n", j.id_jugador);
    printf("Nombre: %s\n", j.nomb_jugador);
    printf("Usuario: %s\n", j.jugador);
    printf("Contrasena: %s\n", j.contrasena);

    printf("Inventario: ");
    if (j.num_objetos == 0){
        printf("vacio");
    }
    else{
        for (i = 0; i < j.num_objetos; i++){
            printf("%s", j.inventario[i]);
            if (i < j.num_objetos - 1){
                printf(", ");
            }
        }
    }
    printf("\n");
}


void listarJugadores(v_jugadores v){
    int i;

    for (i = 0; i < v.num_jugadores; i++){
        mostrarJugador(v.jugadores[i]);
        printf("\n");
    }
}


void liberarJugadores(v_jugadores *v){
    int i;

    if (v->jugadores != NULL){
        for (i = 0; i < v->num_jugadores; i++){
            liberarJugador(&v->jugadores[i]);
        }

        free(v->jugadores);
    }

    v->jugadores = NULL;
    v->num_jugadores = 0;
}


int agregarObjetoAJugador(t_jugador *j, const char *id_obj){
    char **temp;
    char *nuevo_obj;
    int i;

    if (j == NULL || id_obj == NULL){
        return 0;
    }

    for (i = 0; i < j->num_objetos; i++){
        if (strcmp(j->inventario[i], id_obj) == 0){
            return 0;
        }
    }

    nuevo_obj = malloc(MAX_ID_OBJ * sizeof(char));
    if (nuevo_obj == NULL){
        return 0;
    }

    strncpy(nuevo_obj, id_obj, MAX_ID_OBJ - 1);
    nuevo_obj[MAX_ID_OBJ - 1] = '\0';

    temp = realloc(j->inventario, (j->num_objetos + 1) * sizeof(char *));
    if (temp == NULL){
        free(nuevo_obj);
        return 0;
    }

    j->inventario = temp;
    j->inventario[j->num_objetos] = nuevo_obj;
    j->num_objetos++;

    return 1;
}


int quitarObjetoAJugador(t_jugador *j, const char *id_obj){
    int i, pos = -1;

    if (j == NULL || id_obj == NULL){
        return 0;
    }

    for (i = 0; i < j->num_objetos; i++) {
        if (strcmp(j->inventario[i], id_obj) == 0){
            pos = i;
            break;
        }
    }

    if (pos == -1) return 0;
    

    free(j->inventario[pos]);

    for (i = pos; i < j->num_objetos - 1; i++){
        j->inventario[i] = j->inventario[i + 1];
    }

    j->num_objetos--;

    if (j->num_objetos == 0){
        free(j->inventario);
        j->inventario = NULL;
    }
    else{
        char **temp = realloc(j->inventario, j->num_objetos * sizeof(char *));
        if (temp != NULL){
            j->inventario = temp;
        }
    }

    return 1;
}


int tieneObjetoJugador(t_jugador j, const char *id_obj){
    int i;

    if (id_obj == NULL){
        return 0;
    }

    for (i = 0; i < j.num_objetos; i++){
        if (strcmp(j.inventario[i], id_obj) == 0){
            return 1;
        }
    }

    return 0;
}