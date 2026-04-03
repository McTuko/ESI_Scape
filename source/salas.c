#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/jugadores.h"

int main()
{
// Texto azul
    printf("\033[34m\n");
    printf("::::::::::  ::::::::  :::::::::::               ::::::::::  ::::::::   ::::::::      :::     :::::::::  ::::::::::\n");
    printf(":+:        :+:    :+:     :+:                   :+:        :+:    :+: :+:    :+:   :+: :+:   :+:    :+: :+:\n");
    printf("+:+        +:+            +:+                   +:+        +:+        +:+         +:+   +:+  +:+    +:+ +:+\n");
    printf("+#++:++#   +#++:++#++     +#+     +#++:++#++    +#++:++#   +#++:++#++ +#+        +#++:++#++: +#++:++#+  +#++:++#\n");
    printf("+#+               +#+     +#+                   +#+               +#+ +#+        +#+     +#+ +#+        +#+\n");
    printf("#+#        #+#    #+#     #+#                   #+#        #+#    #+# #+#    #+# #+#     #+# #+#        #+#\n");
    printf("##########  ########  ###########               ##########  ########   ########  ###     ### ###        ##########\n");
    printf("\033[0m");

    // Texto blanco
    printf("\033[37m"); 
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("\033[0m");
}


void cargarSalas(v_salas *salas)
{
    FILE *f = fopen("../ficheros/salas.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}
    char linea[250];
    int i=0;
    salas->sala = NULL;

    while(fgets(linea, 250, f) != NULL){
        salas->sala = realloc(salas->sala, (i+1) * sizeof(t_sala));

        salas->sala[i].id = atoi(strtok(linea,"-"));        // Entero
        strcpy(salas->sala[i].nombre, strtok(NULL,"-"));    // String
        salas->sala[i].tipo = (strtok(NULL, "-"))[0];       // Caracter : [0] porque devuelve puntero (vector)
        strcpy(salas->sala[i].desc, strtok(NULL,"-"));
        i++;
    }
    salas->num_salas = i;
    
    fclose(f);
}

void guardarSalas(v_salas salas)
{
    FILE *f = fopen("../ficheros/salas.txt", "w");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}

    for(int i=0;i<salas.num_salas;i++){
        fprintf(f, "%i-%s-%c-%s\n", salas.sala[i].id, salas.sala[i].nombre, salas.sala[i].tipo, salas.sala[i].desc);
    }
    fclose(f);
}

void entrarSala(t_sala salas, t_conexion conexiones, t_jugador jugadores)
{

}


// PRUEBAS ======================================================================================================
// Inicializar e imprimir estructuras
// (Borrar para la entrega)

void inicializarSalas()
{
    v_salas salas;
    salas.num_salas = 2;
    salas.sala = (t_sala*) malloc(salas.num_salas * sizeof(t_sala));

    salas.sala[0].id = 01;
    strcpy(salas.sala[0].nombre, "Aula magia");
    salas.sala[0].tipo = 'F';
    strcpy(salas.sala[0].desc, "Sandra quiere enchufe");

    salas.sala[1].id = 02;
    strcpy(salas.sala[1].nombre, "cafeteria");
    salas.sala[1].tipo = 'N';
    strcpy(salas.sala[1].desc, "Quiero un donut");
}

void imprimirSalas(v_salas salas)
{
    for(int i=0;i<salas.num_salas;i++){
        printf("%i-", salas.sala[i].id);
        printf("%s-", salas.sala[i].nombre);
        printf("%c-", salas.sala[i].tipo);
        printf("%s", salas.sala[i].desc);
    }
}


/* BITACORA ==========================================================================

Las funciones guardar (estructura a fichero) funcionan correctamente
Las funciones cargar (fichero a estructura) funcionan correctamente 
Funcion describir sala terminada

Borrar rewind y poner realloc por línea -> Listo




Lógica de comprobar conexión y entrar en sala

Incluir free de la memoria dinámica

*/