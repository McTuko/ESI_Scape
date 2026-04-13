#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/jugadores.h"
#include "../include/partida.h"

int main()
{

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

void entrarSala(int s1, int s2, v_conexiones conx, t_partida *partida)
{
    for(int i=0;i>conx.num_conexiones;i++){
        if((conx.conexion[i].id_org == s1) && (conx.conexion[i].id_dst == s2)){
            if(conx.conexion[i].estado == 1) partida->id_sala = s2;
            else printf("Conexión cerrada\n");
        }
    }
}

void freeSalas(v_salas* salas)
{
    free(salas->sala);
    salas->sala = NULL;
    salas->num_salas = 0;
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

Función liberar memoria -> Listo




Lógica de comprobar conexión y entrar en sala -> Comprobar

*/