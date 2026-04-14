#include "../include/items.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void eliminarSaltoLinea(char *cadena){
    if (cadena != NULL)cadena[strcspn(cadena, "\n")] = '\0';
}


int buscarItem(v_items *items, const char *id){
    int i;
    for (i = 0; i < items->num_items; i++){
        if (strcmp(items->item[i].id, id) == 0) return i;
    }
    return -1;
}


void mostrarItemsSala(v_items *items, int sala){
    int i;
    for (i = 0; i < items->num_items; i++){
        if (items->item[i].localizacion == sala) printf("%s - %s\n", items->item[i].id, items->item[i].nombre);  
    }
}

int cogerItem(v_items *items, int sala, const char *id){
    int pos = buscarItem(items, id);
    if (pos == -1) return 0;
    if (items->item[pos].localizacion != sala)return 0;
    items->item[pos].localizacion = -1;
    return 1;
}


int soltarItem(v_items *items, int sala, const char *id){
    int pos = buscarItem(items, id);
    if (pos == -1)return 0;
    if (items->item[pos].localizacion != -1) return 0;
    items->item[pos].localizacion = sala;
    return 1;
}


int cargarItems(v_items *items){
    FILE *f = fopen(ARCHIVO_ITEMS, "r");
    char linea[250];
    int i = 0;

    items->item = NULL;
    items->num_items = 0;

    if (f == NULL){ printf("Error: Archivo nulo\n");return 0;}

    while (fgets(linea, 250, f) != NULL){
        t_item *temp;
        char *token;

        eliminarSaltoLinea(linea);
        if (strlen(linea) == 0)continue;
        
        temp = realloc(items->item, (i + 1) * sizeof(t_item));
        if (temp == NULL){
            printf("Error al reservar memoria\n");
            free(items->item);
            items->item = NULL;
            items->num_items = 0;
            fclose(f);
            return 0;
        }
        items->item = temp;

        token = strtok(linea, "-");
        if (token == NULL){
            printf("Error de formato en id del item\n");
            free(items->item);
            items->item = NULL;
            items->num_items = 0;
            fclose(f);
            return 0;
        }
        strncpy(items->item[i].id, token, MAX_ID_ITEM - 1);
        items->item[i].id[MAX_ID_ITEM - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL) {
            printf("Error de formato en nombre del item\n");
            free(items->item);
            items->item = NULL;
            items->num_items = 0;
            fclose(f);
            return 0;
        }
        strncpy(items->item[i].nombre, token, MAX_NOMBRE_ITEM - 1);
        items->item[i].nombre[MAX_NOMBRE_ITEM - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en descripcion del item\n");
            free(items->item);
            items->item = NULL;
            items->num_items = 0;
            fclose(f);
            return 0;
        }
        strncpy(items->item[i].desc, token, MAX_DESC_I - 1);
        items->item[i].desc[MAX_DESC_I - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL){
            printf("Error de formato en localizacion del item\n");
            free(items->item);
            items->item = NULL;
            items->num_items = 0;
            fclose(f);
            return 0;
        }

        if (strcmp(token, "Inventario") == 0){ items->item[i].localizacion = -1;
        }else items->item[i].localizacion = atoi(token);
        i++;
    }
    items->num_items = i;
    fclose(f);
    return 1;
}

int guardarItems(v_items items){
    FILE *f;
    int i;

    f = fopen(ARCHIVO_ITEMS, "w");
    if (f == NULL){
        printf("Error: Archivo nulo\n");
        return 0;
    }

    for (i = 0; i < items.num_items; i++){
        fprintf(f, "%s-%s-%s-",
                items.item[i].id,
                items.item[i].nombre,
                items.item[i].desc);

        if (items.item[i].localizacion == -1){
            fprintf(f, "Inventario\n");
        }
        else{
            fprintf(f, "%02d\n", items.item[i].localizacion);
        }
    }
    fclose(f);
    return 1;
}

void liberarItems(v_items *items){
    free(items->item);
    items->item = NULL;
    items->num_items = 0;
}