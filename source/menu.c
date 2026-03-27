#include <stdio.h>
#include <windows.h>
#include "../include/menu.h"
#include "../include/partida.h"


//Cabecera: void menu(partida*)
//Precondicion: Partida inicializado
//Postcondicion: Ejecuta un menú de selección
void menu (t_partida *partida)
{
    int n;
    select_m(&n);
    switch(n)
    {
    case 1:
        system("cls");
        config(partida);
        break;
    case 2:
        system("cls");  
        jugar(partida);
        break;
    case 3:
        system("cls");
        liberarMemoria(partida);
        printf("Gracias por jugar, vuelve pronto!\n\n");
        exit (0);
    }
}


//Cabecera: void select_m(int*)
//Precondicion: int* inicializado
//Postcondicion: Devuelve 1, 2 ó 3
void select_m(int *n)
{
    int resultado;
    do{
        impr_menu();
        printf("\033[33m");
        printf("Seleccion --> ");
        printf("\033[0m");
        resultado = scanf("%i", n);
        if(resultado!=1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            continue;
        }
        if(*n!=1 && *n!=2 && *n!=3){
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
        }
    } while(*n!=1 && *n!=2 && *n!=3);
}


//Cabecera: void impr_menu()
//Precondicion: Ninguna
//Postcondicion: Imprime el menú
void impr_menu()
{
    printf("\033[32m");
    printf(" __  __ ___ _  _ _   _\n");
    printf("|  \\/  | __| \\| | | | |\n");
    printf("| |\\/| | __|    | |_| |\n");
    printf("|_|  |_|___|_|\\_|\\___/ \n\n");
    printf("\033[0m");

    printf("1. Configuracion\n");
    printf("2. Jugar\n");
    printf("3. Salir\n\n");
}


//Cabecera: void config(partida*)
//Precondicion: Partida inicializado
//Postcondicion: Ejecuta un menú de selección de configuración
void config(t_partida *partida)
{
    int n;
    int num;
    select_c(&n);
    switch (n)
    { 
    case 1:
        system("cls");

            if(partida->bool==1){
                printf("Ya hay datos introducidos\n");
                printf("%cDesea sobreescribir los datos?\n", 168);
                printf("1. Si\n");
                printf("2. No\n");
                printf("\n--> ");
                scanf("%i", &num);
                if(num==1) {system("cls");introducirDatos(partida);}
                else {system("cls");config(partida);}
            }
            else {introducirDatos(partida);partida->bool=1;}
        Sleep(1000);
        system("cls");
        config(partida);
        
        break;
    case 2:
        system("cls");

            if(partida->bool==1) mostrarDatos(*partida);          
            else{printf("Error: No hay datos que mostrar"); Sleep(2000);}           
            
        system("cls");
        config(partida);
        break;
    case 3:
        system("cls");

            if(partida->bool==1) {
                partida->bool=0;
                liberarMemoria(partida);
                partida->bool_g=0;
                for(int i=0;i<3;i++){
                    printf(". ");
                    Sleep(500);
                    }
                system("cls");
                printf("Datos borrados!");
            } else printf("Error: No hay datos que borrar");

        Sleep(2000);
        system("cls");
        config(partida);
        break;
    case 4:
        system("cls");
            if(partida->bool==1){
                guardarDatos(partida);
            } else printf("Error: No hay datos que guardar");
            
        Sleep(2000);
        system("cls");
        config(partida);
        break;
    case 5:
        system("cls");

        if(partida->bool==0){
            cargarDatos(partida);
            system("cls");
            partida->bool=1;
        } 
        else if(partida->bool==1)
        {
            printf("Ya hay datos introducidos\n");
            printf("%cDesea sobreescribir los datos?\n", 168);
            printf("1. Si\n");
            printf("2. No\n");
            printf("\n--> ");
            scanf("%i", &num);
            if(num==1) {system("cls"); cargarDatos(partida);}
            else {system("cls");config(partida);}
        }
        else printf("Error: No hay datos que cargar");

        Sleep(2000);
        system("cls");
        config(partida);
        break;
    case 6:
        system("cls");
        menu(partida);
    }
}


//Cabecera: void select_c(int*)
//Precondicion: int* inicializado
//Postcondicion: Devuelve 1, 2, 3, 4, 5 ó 6
void select_c(int *n)
{
    int resultado;
    do{
        impr_config();
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
        if(*n!=1 && *n!=2 && *n!=3 && *n!=4 && *n!=5 && *n!=6){
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            return;
        }
    } while (*n!=1 && *n!=2 && *n!=3 && *n!=4 && *n!=5 && *n!=6);
}


//Cabecera: void impr_config()
//Precondicion: Ninguma
//Postcondicion: Imprime la configuración
void impr_config()
{
    printf("\033[32m");
    printf("  ____ ___  _   _ _____ ___ ____ _   _ ____      _    ____ ___ ___  _   _ \n");
    printf(" / ___/ _ \\| \\ | |  ___|_ _/ ___| | | |  _ \\    / \\  / ___|_ _/ _ \\| \\ | |\n");
    printf("| |  | | | |  \\| | |_   | | |  _| | | | |_) |  / _ \\| |    | | | | |  \\| |\n");
    printf("| |__| |_| | |\\  |  _|  | | |_| | |_| |  _ <  / ___ \\ |___ | | |_| | |\\  |\n");
    printf(" \\____\\___/|_| \\_|_|   |___\\____|\\___/|_| \\_\\/_/   \\_\\____|___\\___/|_| \\_|\n\n");
    printf("\033[0m");

    printf("1. Introducir datos\n");
    printf("2. Mostrar\n");
    printf("3. Borrar\n");
    printf("4. Guardar\n");
    printf("5. Cargar\n");
    printf("6. Volver\n\n");
}


//Cabecera: void jugar(partida*)
//Precondicion: Partida inicializado
//Postcondicion: Ejecuta un menú de selección de partida
void jugar(t_partida *partida)
{
    int n;
    select_j(&n);
    switch(n)
    {
    case 1:
        system("cls");

        if(partida->bool==1)
        {
            if(partida->jugador[0].ganador == 0 && partida->jugador[1].ganador == 0) 
            {
                if(partida->empieza == 1) {
                    printf("Este es el jugador que empieza: %s\n", partida->jugador[0].n_jugador);
                    EmpezarPartida(partida, 1);
                }
                else if (partida->empieza == 2) {
                    printf("Este es el jugador que empieza: %s\n", partida->jugador[1].n_jugador);
                    EmpezarPartida(partida, 2);
                }

                if(partida->jugador[0].ganador == partida->jugador[1].ganador){
                    
                    printf("Empate\n");
                }
                else{
                    
                    system ("cls");
                    if(partida->jugador[0].ganador == 1) ganador(partida, 0);
                    else ganador(partida, 1);
                }
                
                system("cls");
                menu(partida);
                
            }
            else{printf("Error: La partida ha finalizado, reinicielo o borre los datos primero\n"); Sleep(2000);}
        }

        else{printf("Error: No hay datos introducidos"); Sleep(2000);}
        
        system("cls");
        jugar(partida);
        break;
    case 2:
        system("cls");  

            if(partida->jugador[0].ganador==1 || partida->jugador[1].ganador==1)
            {
                ReiniciarPartida(partida); 
                printf("Reiniciando...\n");
                Sleep(1000);
                system("cls");
            }
            else{printf("Error: No se ha jugado ninguna partida previa");Sleep(2000); system("cls"); jugar(partida);}

        system("cls");
        jugar(partida);
        break;
    case 3:                                             //Contador de barcos
        system("cls");

            if(partida->jugador[0].ganador==1 || partida->jugador[1].ganador==1) resumen(*partida);
            else{printf("Error: No se ha jugado ninguna partida previa");Sleep(2000);}
        
        system("cls");
        jugar(partida);
        break;
    case 4:
        system("cls");
        menu(partida);
    }
}


//Cabecera: void select_j(int*)
//Precondicion: int* inicializado
//Postcondicion: Devuelve 1, 2, 3 ó 4
void select_j(int *n)
{
    int resultado;
    do{
        impr_jugar();
        printf("\033[33m");
        printf("Seleccion --> ");
        printf("\033[0m");
        resultado=scanf("%i", n);
        if(resultado!=1){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            continue;
        }
        if(*n!=1 && *n!=2 && *n!=3 && *n!=4){
            printf("Seleccion invalida!\n");
            Sleep(1000);
            system("cls");
            return;
        }
    } while(*n!=1 && *n!=2 && *n!=3 && *n!=4);
}



//Cabecera: void ganador(partida*, int)
//Precondicion: La partida debe haber acabado (Hay un ganador)
//Postcondicion: Imprime mensaje de victoria y da la opción de volver al menú
void ganador(t_partida *partida, int id)
{
    Sleep(2000);
    system("cls");
                
    printf("  ____    _    _   _    _    ____   ___  ____   \n");
    printf(" / ___|  / \\  | \\ | |  / \\  |  _ \\ / _ \\|  _ \\ \n");
    printf("| |  _  / _ \\ |  \\| | / _ \\ | | | | | | | |_) |\n");
    printf("| |_| |/ ___ \\| |\\  |/ ___ \\| |_| | |_| |  _ < \n");
    printf(" \\____/_/   \\_\\_| \\_/_/   \\_\\____/ \\___/|_| \\_\\ \n");
    printf("\n\n\n                      ");
    for(int j=0;j<19;j++) {

    if(partida->jugador[id].n_jugador[j] == '\0')
        j = 19;
    else 
    printf("%c", partida->jugador[id].n_jugador[j]);
    }

    char tmp;
    printf("\n\nPara seguir <ENTER> ");
    while ((tmp = getchar()) != '\n' && tmp != EOF);
    getchar();
    menu(partida);
}


//Cabecera: void impr_jugar()
//Precondicion: Ninguna
//Postcondicion: Imprime el menú de partida
void impr_jugar()
{
    printf("\033[32m");
    printf("     _ _   _  ____    _    ____    ____   _    ____ _____ ___ ____    _    \n");
    printf("    | | | | |/ ___|  / \\  |  _ \\  |  _ \\ / \\  |  _ \\_   _|_ _|  _ \\  / \\   \n");
    printf(" _  | | | | | |  _  / _ \\ | |_) | | |_) / _ \\ | |_) || |  | || | | |/ _ \\  \n");
    printf("| |_| | |_| | |_| |/ ___ \\|  _ <  |  __/ ___ \\|  _ < | |  | || |_| / ___ \\ \n");
    printf(" \\___/ \\___/ \\____/_/   \\_\\_| \\_\\ |_| /_/   \\_\\_| \\_\\|_| |___|____/_/   \\_\\ \n\n");
    printf("\033[0m");

    printf("1. Jugar partida\n");
    printf("2. Reiniciar partida\n");
    printf("3. Resumen\n");
    printf("4. Volver\n\n");
}


//Cabecera: void ganador(partida*, int)
//Precondicion: Ninguna
//Postcondicion: Imprime la portada
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
    printf(" ^^^^^ ^^^^^^^^^^^^^^^^^^^^^             ^^^^^^^^^^^^^^^^^^^\n");
    printf("\033[0m");

    // Texto blanco
    printf("\033[37m"); 
    for (int i = 0; i < 2; i++) printf("---------------------------------------------------------------------------------\n");
    printf("\033[0m");
}
