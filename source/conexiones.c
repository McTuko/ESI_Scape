#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/conexiones.h"

int main()
{
    v_conexiones conx;
    cargarConexiones(&conx);
    imprimirConexiones(conx);
    liberarConexiones(&conx);

    return 0;
}

// GESTIÓN FICHEROS ===================================================================

int cargarConexiones(v_conexiones *conx)
{
    FILE *f = fopen(ARCHIVO_CONEXIONES, "r");
    t_conexion *temp;
    char linea[250];
    char *token;
    int i = 0;

    conx->conexiones = NULL;
    conx->num_conexiones = 0;

    if(f == NULL) {printf("Error: Archivo nulo\n"); return 0;}

    while(fgets(linea, 250, f) != NULL)
    {
        if(linea != NULL) linea[strcspn(linea, "\n")] = '\0';
        if (strlen(linea) == 0) continue;

        temp = realloc(conx->conexiones, (i + 1) * sizeof(t_conexion));
        if(temp == NULL){
            printf("Error al reservar memoria\n");
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }
        conx->conexiones = temp;

        token = strtok(linea, "-");
        if(token == NULL){
            printf("Error de formato en id_cnx\n");
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }
        strcpy(conx->conexiones[i].id_cnx, token);

        token = strtok(NULL, "-");
        if(token == NULL){
            printf("Error de formato en id_org\n");
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }
        conx->conexiones[i].id_org = atoi(token);

        token = strtok(NULL, "-");
        if(token == NULL){
            printf("Error de formato en id_dst\n");
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }
        conx->conexiones[i].id_dst = atoi(token);

        token = strtok(NULL, "-");
        if(token == NULL){
            printf("Error de formato en estado\n");
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }
        strcpy(conx->conexiones[i].estado, token);

        token = strtok(NULL, "-");
        if(token == NULL){
            printf("Error de formato en cond\n");
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }
        strcpy(conx->conexiones[i].cond, token);

        if(!conexionValida(conx->conexiones[i])){
            printf("Conexion invalida: %s\n", conx->conexiones[i].id_cnx);
            liberarConexiones(conx);
            fclose(f);
            return 0;
        }

        i++;
    }

    conx->num_conexiones = i;
    fclose(f);
    return 1;
}

int guardarConexiones(v_conexiones conx)
{
    FILE *f = fopen(ARCHIVO_CONEXIONES, "w");
    if (f == NULL){printf("Error: Archivo nulo\n");return 0;}

    for (int i=0;i<conx.num_conexiones;i++){
        fprintf(f, "%s-%d-%d-%s-%s\n",
                conx.conexiones[i].id_cnx,
                conx.conexiones[i].id_org,
                conx.conexiones[i].id_dst,
                conx.conexiones[i].estado,
                conx.conexiones[i].cond);
    }
    fclose(f);
    return 1;
}


// VALIDACIÓN =========================================================================

int estadoValido(const char *estado)
{
    if(strcmp(estado, "Activa") == 0 || strcmp(estado, "Bloqueada") == 0) {return 1;}
    return 0;
}

int conexionValida(t_conexion conx)
{
    if(strlen(conx.id_cnx) == 0) return 0;

    if(conx.id_org <= 0 || conx.id_dst <= 0) return 0;

    if(!estadoValido(conx.estado)) return 0;
    
    if(strlen(conx.cond) == 0) return 0;
    
    return 1;
}


// UTILIDADES =========================================================================

void liberarConexiones(v_conexiones *conx)
{
    free(conx->conexiones);
    conx->conexiones = NULL;
    conx->num_conexiones = 0;
}

int buscarConexion(int s1, int s2, v_conexiones conx)
{
    for(int i = 0; i < conx.num_conexiones; i++)
    {
        if(conx.conexiones[i].id_org == s1 && conx.conexiones[i].id_dst == s2) return i;
    }

    return -1;
}

int existeConexion(int s1, int s2, v_conexiones conx)
{
    if(buscarConexion(s1, s2, conx) != -1) return 1;
    return 0;
}

int conexionEstaActiva(int s1, int s2, v_conexiones conx)
{
    int pos = buscarConexion(s1, s2, conx);

    if(pos == -1) return 0;
    
    if(strcmp(conx.conexiones[pos].estado, "Activa") == 0) return 1;
    
    return 0;
}

int desbloquearConexion(const char *id_cnx, v_conexiones *conx)
{
    for(int i = 0; i < conx->num_conexiones; i++)
    {
        if(strcmp(conx->conexiones[i].id_cnx, id_cnx) == 0){strcpy(conx->conexiones[i].estado, "Activa"); return 1;}
    }
    return 0;
}


// PRUEBAS ============================================================================
// Inicializar e imprimir estructuras
// (Borrar para la entrega)

void imprimirConexiones(v_conexiones cnx)
{
    for(int i = 0; i < cnx.num_conexiones; i++)
    {
        printf("%s-", cnx.conexiones[i].id_cnx);
        printf("%02d-", cnx.conexiones[i].id_org);
        printf("%02d-", cnx.conexiones[i].id_dst);
        printf("%s-", cnx.conexiones[i].estado);
        printf("%s\n", cnx.conexiones[i].cond);
    }
}


/* BITACORA ==========================================================================

Las funciones guardar (estructura a fichero) funcionan correctamente
Las funciones cargar (fichero a estructura) funcionan correctamente
Borrar rewind y poner realloc por línea -> Listo




Lógica de comprobar conexión
//Dani, esto borralo, son los cambios que he hecho yo pero es tu codigo
Estado cambiado a cadena: "Activa" / "Bloqueada"
conexion pasa a llamarse conexiones según la nueva cabecera
Se limpia el salto de línea al leer
Se comprueba realloc
comprobarConexion sustituida por:
- buscarConexion
- existeConexion
- conexionEstaActiva
- desbloquearConexion
Cambios hechos en cargarConexiones:
- Se elimina el salto de línea al leer cada línea del fichero
- Se comprueba que la línea no esté vacía antes de procesarla
- Se comprueba el resultado de realloc para evitar pérdidas de memoria
- Se valida cada conexión antes de agregarla al vector
*/