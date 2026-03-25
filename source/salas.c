#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/salas.h"

int main()
{
 pruebaSalas();
}

void entrarSala(t_sala, t_conexion)
{

}

int comprobarConexion(t_conexion, int)
{

}

void cargarSalas(v_salas*)
{
    FILE *f = fopen("salas.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}

    
    
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

void cargarConexiones(v_conexiones*)
{
    FILE *f = fopen("salas.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}


    
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


// PRUEBAS ======================================================================================================
// (Borrar para la entrega)

void pruebaSalas()
{
v_salas salas;
salas.num_salas = 1;
salas.sala = (t_sala*) malloc(salas.num_salas * sizeof(t_sala));

salas.sala[0].id = 01;
strcpy(salas.sala[0].nombre, "cafete");
salas.sala[0].tipo = 'F';
strcpy(salas.sala[0].desc, "Robe me da cañitas de chocolate");

guardarSalas(salas);
}

void pruebaConexiones()
{
    v_conexiones conexiones;
    conexiones.num_conexiones = 1;
    conexiones.conexion = (t_conexion*) malloc(conexiones.num_conexiones * sizeof(t_conexion));

    conexiones.conexion[0].id_org = 01;
    conexiones.conexion[0].id_dst = 02;
    strcpy(conexiones.conexion[0].id_cnx, "D01");
    conexiones.conexion[0].estado = 0;
    strcpy(conexiones.conexion[0].cond, "llave amarilla");

    guardarConexiones(conexiones);
}