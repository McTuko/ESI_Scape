#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/conexiones.h"

int main()
{
    v_conexiones cnx;
    cargarConexiones(&cnx);
    imprimirConexiones(cnx);
    //guardarConexiones(cnx);
}


void cargarConexiones(v_conexiones *conx)
{
    FILE *f = fopen("../ficheros/conexiones.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}
    char linea[250];
    int i=0;
    conx->conexion = NULL;

    while(fgets(linea, 250, f) != NULL){
        conx->conexion = realloc(conx->conexion, (i+1) * sizeof(t_conexion));

        strcpy(conx->conexion[i].id_cnx, strtok(linea,"-"));
        conx->conexion[i].id_org = atoi(strtok(NULL,"-"));
        conx->conexion[i].id_dst = atoi(strtok(NULL,"-"));
        conx->conexion[i].estado = atoi(strtok(NULL,"-"));
        strcpy(conx->conexion[i].cond, strtok(NULL,"-"));
        i++;
    }
    conx->num_conexiones = i;
    
    fclose(f);
}

void guardarConexiones(v_conexiones conx)
{
    FILE *f = fopen("../ficheros/conexiones.txt", "w");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}

    for(int i=0;i<conx.num_conexiones;i++){
        fprintf(f, "%s-%i-%i-%i-%s\n", conx.conexion[i].id_cnx, conx.conexion[i].id_org, conx.conexion[i].id_dst, conx.conexion[i].estado, conx.conexion[i].cond);
    }
    fclose(f);
}

int comprobarConexion(int s1, int s2, v_conexiones conx)
{
    
}

void freeConx(v_conexiones* conx)
{
    free(conx->conexion);
    conx->conexion = NULL;
    conx->num_conexiones = 0;
}


// PRUEBAS ======================================================================================================
// Inicializar e imprimir estructuras
// (Borrar para la entrega)

void inicializarConexiones()
{
    v_conexiones conexiones;
    conexiones.num_conexiones = 2;
    conexiones.conexion = (t_conexion*) malloc(conexiones.num_conexiones * sizeof(t_conexion));

    conexiones.conexion[0].id_org = 01;
    conexiones.conexion[0].id_dst = 02;
    strcpy(conexiones.conexion[0].id_cnx, "D01");
    conexiones.conexion[0].estado = 0;
    strcpy(conexiones.conexion[0].cond, "llave amarilla");

    conexiones.conexion[1].id_org = 03;
    conexiones.conexion[1].id_dst = 04;
    strcpy(conexiones.conexion[1].id_cnx, "E03");
    conexiones.conexion[1].estado = 0;
    strcpy(conexiones.conexion[1].cond, "gallina loca");
}

void imprimirConexiones(v_conexiones cnx)
{
    for(int i=0;i<cnx.num_conexiones;i++){
        printf("%s-", cnx.conexion[i].id_cnx);
        printf("%i-", cnx.conexion[i].id_org);
        printf("%i-", cnx.conexion[i].id_dst);
        printf("%i-", cnx.conexion[i].estado);
        printf("%s", cnx.conexion[i].cond);
    }
}


/* BITACORA ==========================================================================

Las funciones guardar (estructura a fichero) funcionan correctamente
Las funciones cargar (fichero a estructura) funcionan correctamente 

Borrar rewind y poner realloc por línea -> Listo

Crear función para liberar memoria -> Listo




Lógica de comprobar conexión

*/