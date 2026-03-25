#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cargarJugadores(struct Jugador jugadores[], int max){

    FILE *f;
    char linea[200];
    int i = 0;

    f = fopen("Jugadores.txt","r");

    if(f == NULL){
        printf("Error al abrir archivo\n");
        return 0;
    }

    while(fgets(linea,200,f) != NULL && i < max){

        char *token;

        token = strtok(linea,"-");
        jugadores[i].id_jugador = atoi(token);

        token = strtok(NULL,"-");
        strcpy(jugadores[i].nomb_jugador,token);

        token = strtok(NULL,"-");
        strcpy(jugadores[i].jugador,token);

        token = strtok(NULL,"-");
        strcpy(jugadores[i].contrasena,token);

        token = strtok(NULL,"-\n");

        jugadores[i].num_obj = 0;

        char *obj = strtok(token,",");
        while(obj != NULL){
            jugadores[i].id_obj[jugadores[i].num_obj++] = atoi(obj);
            obj = strtok(NULL,",");
        }

        i++;
    }

    fclose(f);

    return i;
}