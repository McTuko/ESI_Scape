#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/salas.h"

int main()
{
    v_salas salas;
    cargarSalas(&salas);
    imprimirSalas(salas);
}

void entrarSala(t_sala, t_conexion)
{

}

int comprobarConexion(t_conexion, int)
{

}

void cargarSalas(v_salas *salas)
{
    FILE *f = fopen("../ficheros/salas.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}
    char linea[250];
    int cnt=0;

    while(fgets(linea, 250, f) != NULL) cnt++;
    salas->sala = (t_sala*) malloc(cnt * sizeof(t_sala));
    rewind(f);

    for(int i=0;i<cnt;i++){
        fgets(linea, 250, f);
        salas->sala[i].id = atoi(strtok(linea,"-"));
        strcpy(salas->sala[i].nombre, strtok(NULL,"-"));
        salas->sala[i].tipo = (strtok(NULL, "-"))[0];
        strcpy(salas->sala[i].desc, strtok(NULL,"-"));
    }
    salas->num_salas = cnt;
    
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


void cargarConexiones(v_conexiones *conx)
{
    FILE *f = fopen("../ficheros/conexiones.txt", "r");
    if(f == NULL) {printf("Error: Archivo nulo"); return;}
    char linea[250];
    int cnt=0;

    while(fgets(linea, 250, f) != NULL) cnt++;
    conx->conexion = (t_conexion*) malloc(cnt * sizeof(t_conexion));
    rewind(f);

    for(int i=0;i<cnt;i++){
        fgets(linea, 250, f);
        strcpy(conx->conexion[i].id_cnx, strtok(linea,"-"));
        conx->conexion[i].id_org = atoi(strtok(NULL,"-"));
        conx->conexion[i].id_dst = atoi(strtok(NULL,"-"));
        conx->conexion[i].estado = atoi(strtok(NULL,"-"));
        strcpy(conx->conexion[i].cond, strtok(NULL,"-"));
    }
    conx->num_conexiones = cnt;
    
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

void inicializarSalas()
{
    v_salas salas;
    salas.num_salas = 2;
    salas.sala = (t_sala*) malloc(salas.num_salas * sizeof(t_sala));

    salas.sala[0].id = 01;
    strcpy(salas.sala[0].nombre, "cafete");
    salas.sala[0].tipo = 'F';
    strcpy(salas.sala[0].desc, "Robe me da cañitas de chocolate");

    salas.sala[1].id = 02;
    strcpy(salas.sala[1].nombre, "ñesi");
    salas.sala[1].tipo = 'N';
    strcpy(salas.sala[1].desc, "Bombardeenme");
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

void inicializarConexiones()
{
    v_conexiones conexiones;
    conexiones.num_conexiones = 1;
    conexiones.conexion = (t_conexion*) malloc(conexiones.num_conexiones * sizeof(t_conexion));

    conexiones.conexion[0].id_org = 01;
    conexiones.conexion[0].id_dst = 02;
    strcpy(conexiones.conexion[0].id_cnx, "D01");
    conexiones.conexion[0].estado = 0;
    strcpy(conexiones.conexion[0].cond, "llave amarilla");
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

/*VITACORAS==========================================================================

Las funciones guardar (estructura a fichero) funcionan correctamente

Las funciones cargar (fichero a estructura) NO funciona pues la estructura se debe pasar como puntero

*/