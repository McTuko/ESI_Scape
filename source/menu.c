#include <stdio.h>
#include <windows.h>
#include "../include/menu.h"
#include "../include/partida.h"


void menu1(t_partida *partida)
{
    int n;
    int num;
    select_m(&n);

    switch(n)
    {
    case 1:
        system("cls");
        // Implementar bien (funcion jugar)
        if(partida->bool==1){
                printf("Ya existe una partida\n");
                printf("%cDesea sobreescribir los datos?\n", 168);
                printf("1. Si\n");
                printf("2. No\n");
                printf("\n--> ");
                scanf("%i", &num);
                if(num==1) {system("cls");/*jugar(partida)*/;}
                else {system("cls");menu1(partida);}
            }
            else {/*jugar(partida)*/;partida->bool=1;}

        Sleep(1000);
        system("cls");
        menu1(partida);
        break;
    case 2:
        system("cls");  
        // Implementar bien
        if(partida->bool==1){
            //cargarDatos(partida); hacer cargar datos unificado
            system("cls");
            partida->bool=1;
        } 
        else printf("Error: No hay datos que cargar");

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
        impr_menu();
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
    select_c(&n);

    switch (n)
    { 
    case 1:
        system("cls");
        
        break;
    case 2:
        system("cls");
        
        break;
    case 3:
        system("cls");
        
        break;
    case 4:
        system("cls");
        
        break;
    case 5:
        system("cls");
        
        break;
    case 6:
        system("cls");
        
        break;
    case 7:
        system("cls");
        
        break;
    case 8:
        system("cls");
        
        break;
    case 9:
        system("cls");
        
        break;
    case 10:
        system("cls");
        
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
    printf("8 Resolver puzle\n");
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
    menu(partida);
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
