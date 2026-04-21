#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/jugadores.h"
#include "../include/partida.h"

int main(){
    v_salas salas;
    cargarSalas(&salas);
    imprimirSalas(salas);
    liberarSalas(&salas);

    return 0;
}

// Precondición: Fichero "Salas.txt" existente con formato correcto
// Postcondición: Estructura v_salas cargada con los datos del fichero
int cargarSalas(v_salas *salas)
{
    FILE *f = fopen(ARCHIVO_SALAS, "r");
    t_sala *temp;
    char linea[250];
    char *token;
    int i = 0;

    salas->sala = NULL;
    salas->num_salas = 0;

    if (f == NULL) {printf("Error: Archivo nulo\n"); return 0;}

    while (fgets(linea, 250, f) != NULL)
    {
        if (linea != NULL)linea[strcspn(linea, "\n")] = '\0';
        if (strlen(linea) == 0) continue;

        temp = realloc(salas->sala, (i + 1) * sizeof(t_sala));
        if (temp == NULL){
            printf("Error al reservar memoria\n");
            liberarSalas(salas);
            fclose(f);
            return 0;
        }
        salas->sala = temp;

        token = strtok(linea, "-");
        if (token == NULL)
        {
            printf("Error de formato en id de sala\n");
            liberarSalas(salas);
            fclose(f);
            return 0;
        }
        salas->sala[i].id = atoi(token);

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Error de formato en nombre de sala\n");
            liberarSalas(salas);
            fclose(f);
            return 0;
        }
        strncpy(salas->sala[i].nombre, token, MAX_NOMBRE_SALA - 1);
        salas->sala[i].nombre[MAX_NOMBRE_SALA - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Error de formato en tipo de sala\n");
            liberarSalas(salas);
            fclose(f);
            return 0;
        }
        strncpy(salas->sala[i].tipo, token, MAX_TIPO_SALA - 1);
        salas->sala[i].tipo[MAX_TIPO_SALA - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Error de formato en descripcion de sala\n");
            liberarSalas(salas);
            fclose(f);
            return 0;
        }
        strncpy(salas->sala[i].desc, token, MAX_DESC_SALA - 1);
        salas->sala[i].desc[MAX_DESC_SALA - 1] = '\0';

        i++;
    }

    salas->num_salas = i;
    fclose(f);
    return 1;
}

// Precondición: Estructura v_salas con datos válidos
// Postcondición: Datos de la estructura guardados en el fichero con su formato correspondiente
int guardarSalas(v_salas salas)
{
    FILE *f = fopen(ARCHIVO_SALAS, "w");
    if (f == NULL){printf("Error: Archivo nulo\n");return 0;}

    for (int i=0;i<salas.num_salas;i++){
        fprintf(f, "%i-%s-%s-%s\n",
                salas.sala[i].id,
                salas.sala[i].nombre,
                salas.sala[i].tipo,
                salas.sala[i].desc);
    }
    fclose(f);
    return 1;
}

// Precondición: Estructura v_conexiones inicializada y con datos válidos. Sala actual = s1, Sala destino = s2
// Postcondición: Si la conexión está activa, se actualiza la sala en la partida. De lo contrario, se notifica de que la conexión está cerrada
void entrarSala(int s1, int s2, v_conexiones conx, t_partida *partida)
{
    int i;
    for (i = 0; i < conx.num_conexiones; i++)
    {
        if ((conx.conexiones[i].id_org == s1) && (conx.conexiones[i].id_dst == s2))
        {
            if (strcmp(conx.conexiones[i].estado, "Activa") == 0){partida->id_sala = s2;}
            else printf("Conexión cerrada\n"); 
        }
    }
}

// Precondición: Estructura v_salas con datos 
// Postcondición: Libera memoria dinámica de salas
void liberarSalas(v_salas *salas){
    free(salas->sala);
    salas->sala = NULL;
    salas->num_salas = 0;
}

// Precondición: ??
// Postcondición: ??
int buscarSalaPorId(v_salas salas, int id)
{
    for (int i=0;i<salas.num_salas;i++) if(salas.sala[i].id == id) return i;
    
    return -1;
}

// Precondición: Estructura t_sala con datos cargados
// Postcondición: Imprime los datos de la sala
void mostrarSala(t_sala sala)
{
    printf("ID: %02d\n", sala.id);
    printf("Nombre: %s\n", sala.nombre);
    printf("Tipo: %s\n", sala.tipo);
    printf("Descripcion: %s\n", sala.desc);
}


// PRUEBAS============================================================================================
void imprimirSalas(v_salas salas)
{
    int i;

    for (i = 0; i < salas.num_salas; i++)
    {
        printf("%02d-", salas.sala[i].id);
        printf("%s-", salas.sala[i].nombre);
        printf("%s-", salas.sala[i].tipo);
        printf("%s\n", salas.sala[i].desc);
    }
}


/* BITACORA ==========================================================================

Las funciones guardar (estructura a fichero) funcionan correctamente
Las funciones cargar (fichero a estructura) funcionan correctamente 

Borrar rewind y poner realloc por línea -> Listo
Función liberar memoria -> Listo

Control de errores en carga



Pendiente revisar entrarSala dentro de la lógica de partida

*/