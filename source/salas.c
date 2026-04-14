#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/jugadores.h"
#include "../include/partida.h"


static void eliminarSaltoLinea(char *cadena)
{
    if (cadena != NULL)cadena[strcspn(cadena, "\n")] = '\0';
}


int cargarSalas(v_salas *salas)
{
    FILE *f = fopen(ARCHIVO_SALAS, "r");
    char linea[250];
    int i = 0;

    salas->sala = NULL;
    salas->num_salas = 0;

    if (f == NULL){printf("Error: Archivo nulo\n"); return 0;}

    while (fgets(linea, 250, f) != NULL)
    {
        t_sala *temp;
        char *token;

        eliminarSaltoLinea(linea);

        if (strlen(linea) == 0) continue;

        temp = realloc(salas->sala, (i + 1) * sizeof(t_sala));
        if (temp == NULL)
        {
            printf("Error al reservar memoria\n");
            free(salas->sala);
            salas->sala = NULL;
            salas->num_salas = 0;
            fclose(f);
            return 0;
        }
        salas->sala = temp;

        token = strtok(linea, "-");
        if (token == NULL)
        {
            printf("Error de formato en id de sala\n");
            free(salas->sala);
            salas->sala = NULL;
            salas->num_salas = 0;
            fclose(f);
            return 0;
        }
        salas->sala[i].id = atoi(token);

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Error de formato en nombre de sala\n");
            free(salas->sala);
            salas->sala = NULL;
            salas->num_salas = 0;
            fclose(f);
            return 0;
        }
        strncpy(salas->sala[i].nombre, token, MAX_NOMBRE_SALA - 1);
        salas->sala[i].nombre[MAX_NOMBRE_SALA - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Error de formato en tipo de sala\n");
            free(salas->sala);
            salas->sala = NULL;
            salas->num_salas = 0;
            fclose(f);
            return 0;
        }
        strncpy(salas->sala[i].tipo, token, MAX_TIPO_SALA - 1);
        salas->sala[i].tipo[MAX_TIPO_SALA - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL)
        {
            printf("Error de formato en descripcion de sala\n");
            free(salas->sala);
            salas->sala = NULL;
            salas->num_salas = 0;
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


int guardarSalas(v_salas salas)
{
    FILE *f = fopen(ARCHIVO_SALAS, "w");
    int i;

    if (f == NULL){printf("Error: Archivo nulo\n");return 0; }

    for (i = 0; i < salas.num_salas; i++)
    {
        fprintf(f, "%02d-%s-%s-%s\n",
                salas.sala[i].id,
                salas.sala[i].nombre,
                salas.sala[i].tipo,
                salas.sala[i].desc);
    }
    fclose(f);
    return 1;
}


/* Pendiente de revisar más adelante */
void entrarSala(int s1, int s2, v_conexiones conx, t_partida *partida)
{
    int i;
    for (i = 0; i < conx.num_conexiones; i++)
    {
        if ((conx.conexiones[i].id_org == s1) && (conx.conexiones[i].id_dst == s2))
        {
            if (strcmp(conx.conexiones[i].estado, "Activa") == 0){partida->id_sala = s2;
            }else printf("Conexión cerrada\n"); 
        }
    }
}


void freeSalas(v_salas *salas)
{
    free(salas->sala);
    salas->sala = NULL;
    salas->num_salas = 0;
}


int buscarSalaPorId(v_salas salas, int id)
{
    int i;

    for (i = 0; i < salas.num_salas; i++)
    {
        if (salas.sala[i].id == id) return i;
    }
    return -1;
}

void mostrarSala(t_sala sala)
{
    printf("ID: %02d\n", sala.id);
    printf("Nombre: %s\n", sala.nombre);
    printf("Tipo: %s\n", sala.tipo);
    printf("Descripcion: %s\n", sala.desc);
}

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
Función describir sala terminada

Borrar rewind y poner realloc por línea -> Listo
Función liberar memoria -> Listo


Corrección tipo sala: pasa de char a string ("INICIAL", "NORMAL", "SALIDA")
Ajuste tamaños arrays:
nombre -> 31
desc -> 151

Control de errores en carga:
comprobación fopen, strtok y realloc
Uso de realloc con puntero temporal -> evita pérdida de memoria
Limpieza salto de línea -> eliminarSaltoLinea()
Cambio a fichero "Salas.txt" según enunciado
cargarSalas y guardarSalas devuelven int
Adaptación a conexiones:
conexion -> conexiones
estado entero -> string ("Activa"/"Bloqueada")
Corrección bucle en entrarSala

Añadidas funciones:
buscarSalaPorId()
mostrarSala()

Pendiente revisar entrarSala dentro de la lógica de partida

*/