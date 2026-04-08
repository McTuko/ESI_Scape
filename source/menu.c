#include <stdio.h>
#include <windows.h>
#include "../include/menu.h"
#include "../include/partida.h"

int main()
{
    t_partida partida;
    partida.datos=1;
    portada();
    menu1(&partida);
}

void menu1(t_partida *partida)
{
    int n;
    int num;
    select_m1(&n);

    switch(n)
    {
    case 1:
        system("cls");
        // Implementar bien (funcion jugar)
        if(partida->datos==1){
                printf("Ya existe una partida\n");
                printf("%cDesea sobreescribir los datos?\n", 168);
                printf("1. Si\n");
                printf("2. No\n");
                printf("\n--> ");
                scanf("%i", &num);
                if(num==1) {system("cls");/*jugar(partida)*/;}
                else {system("cls");menu1(partida);}
            }
            else {/*jugar(partida)*/;partida->datos=1;}

        Sleep(1000);
        system("cls");
        menu1(partida);
        break;

    case 2:
        system("cls");  
        // Implementar bien
        if(partida->datos == 0){
            //cargarDatos(partida); hacer cargar datos unificado
            partida->datos=1;
            for(int i=0;i<2;i++){
                printf(". ");
                Sleep(1000);
                printf("Datos cargados correctamente");
            }
        } else printf("Error: No hay datos que cargar");

        Sleep(2000);
        system("cls");
        menu1(partida);
        break;

    case 3:
        system("cls");
        // Liberar memoria
        printf("Gracias por jugar, vuelve pronto!\n\n");
        exit (0);
    }
}

void select_m1(int *n)
{
    int resultado;
    do{
        impr_menu1();
        printf("\033[33m");
        printf("Seleccion --> ");
        printf("\033[0m");
        resultado = scanf("%i", n);
        
        if(resultado!=1){                       // Comprueba si es int
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            continue;
        }

        if(*n!=1 && *n!=2 && *n!=3){            // Comprueba si está en rango
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
        }
    } while(*n!=1 && *n!=2 && *n!=3);
}

void impr_menu1()
{
    printf("\033[32m");
    printf(" __  __ ___ _  _ _   _\n");
    printf("|  \\/  | __| \\| | | | |\n");
    printf("| |\\/| | __|    | |_| |\n");
    printf("|_|  |_|___|_|\\_|\\___/ \n\n");
    printf("\033[0m");

    printf("1. Nueva Partida\n");
    printf("2. Cargar Partida\n");
    printf("3. Salir\n\n");
}


void menu2(t_partida *partida)
{
    int n;
    int num;
    select_m2(&n);

    switch (n)
    { 
    case 1:
        system("cls");
        printf("%s", partida->salas.sala[partida->id_sala].desc);
        break;

    case 2:
        system("cls");
        mostrarItemsSala(&partida->items, partida->id_sala);
        //mostrarSalidas();
        break;
    case 3:
        system("cls");
        // 3. Entrar en otra sala
        break;
    case 4:
        system("cls");
        char cad[6];
        printf("Cod item -> ");
        //getw("%s", &cad);
        cogerItem(&partida->items, partida->id_sala, cad);
        break;
    case 5:
        system("cls");
        // 5. Soltar objeto
        break;
    case 6:
        system("cls");
        mostrarInventario(&partida->items);
        break;
    case 7:
        system("cls");
        // 7. Usar objeto
        break;
    case 8:
        system("cls");
        // 8. Resolver puzle
        break;
    case 9:
        system("cls");
        // 9. Guardar partida
        break;
    case 10:
        system("cls");
        menu1(partida);
        break;
    }
}

void select_m2(int *n)
{
    int resultado;
    do{
        impr_menu2();
        printf("\033[33m");
        printf("Seleccion --> ");
        printf("\033[0m");
        resultado=scanf("%i",n);

        if(resultado!=1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            continue;
        }

        if(*n!=1 && *n!=2 && *n!=3 && *n!=4 && *n!=5 && *n!=6 && *n!=7 && *n!=8 && *n!=9 && *n!=10){
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            return;
        }
    } while (*n!=1 && *n!=2 && *n!=3 && *n!=4 && *n!=5 && *n!=6 && *n!=7 && *n!=8 && *n!=9 && *n!=10);
}

void impr_menu2()
{
    printf("\033[32m");
    printf(" __  __ ___ _  _ _   _\n");
    printf("|  \\/  | __| \\| | | | |\n");
    printf("| |\\/| | __|    | |_| |\n");
    printf("|_|  |_|___|_|\\_|\\___/ \n\n");
    printf("\033[0m");

    printf("1. Describir sala\n");
    printf("2. Examinar objetos y salidas\n");
    printf("3. Entrar en otra sala\n");
    printf("4. Coger objeto\n");
    printf("5. Soltar objeto\n");
    printf("6. Inventario\n");
    printf("7. Usar objeto\n");
    printf("8. Resolver puzle\n");
    printf("9. Guardar partida\n");
    printf("10. Volver\n\n");
}


void ganador(t_partida *partida)
{
    Sleep(2000);
    system("cls");
                
    printf("  ____    _    _   _    _    ____   ___  ____   \n");
    printf(" / ___|  / \\  | \\ | |  / \\  |  _ \\ / _ \\|  _ \\ \n");
    printf("| |  _  / _ \\ |  \\| | / _ \\ | | | | | | | |_) |\n");
    printf("| |_| |/ ___ \\| |\\  |/ ___ \\| |_| | |_| |  _ < \n");
    printf(" \\____/_/   \\_\\_| \\_/_/   \\_\\____/ \\___/|_| \\_\\ \n");
    printf("\n\n\n                      ");
    
    // Imprimir nombre en vez de id
    printf("%s", partida->id_jugador);

    char tmp;
    printf("\n\nPara seguir <ENTER> ");
    while ((tmp = getchar()) != '\n' && tmp != EOF);
    getchar();
    menu1(partida);
}

void portada()
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


/* BITACORA ==========================================================================

Falta funcion de jugar(partida);
Donde poner y como implementar

Crear Cargardatos unificado

Crear funciones de liberar memoria y unificarlas

Hacer switch de menu2

*/
