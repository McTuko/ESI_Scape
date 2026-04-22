#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/menu.h"


/* ========================= AUX GENERALES ========================= */

void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}


/* ========================= LOGIN / REGISTRO ========================= */

int loginORegistro(v_jugadores *jugadores)
{
    char usuario[MAX_USER];
    char pass[MAX_PASS];
    int pos;
    int opcion;
    int continuar = 1;

    while (continuar)
    {
        printf("\nINICIO DE SESION\n");
        printf("Usuario: ");
        scanf("%10s", usuario);
        limpiarBuffer();

        printf("Contrasena: ");
        scanf("%8s", pass);
        limpiarBuffer();

        pos = buscarJugadorPorUsername(*jugadores, usuario);

        if (pos != -1)
        {
            if (strcmp(jugadores->jugadores[pos].contrasena, pass) == 0)
            {
                printf("Acceso correcto. Bienvenido/a %s\n",
                       jugadores->jugadores[pos].nomb_jugador);
                return pos;
            }

            printf("Contrasena incorrecta.\n");
            printf("1. Reintentar\n");
            printf("2. Volver\n");
            printf("Opcion: ");
            scanf("%d", &opcion);
            limpiarBuffer();

            if (opcion == 2)
            {
                continuar = 0;
            }
        }
        else
        {
            int opcion_menu = 0;
            do
            {
                printf("El usuario no existe.\n");
                printf("1. Registrarse\n");
                printf("2. Volver al Login\n");
                printf("3. Salir\n");
                printf("Opcion: ");
                scanf("%d", &opcion_menu);
                limpiarBuffer();

                switch (opcion_menu)
                {
                    case 1:
                        pos = registrarNuevoJugador(jugadores);
                        if (pos != -1)
                        {
                            return pos;
                        }
                        break;
                    case 2:
                        opcion_menu = 2; // Para salir del do-while y continuar el bucle principal
                        break;
                    case 3:
                        printf("Saliendo del programa...\n");
                        exit(0);
                    default:
                        printf("Opcion incorrecta.\n");
                        break;
                }
            } while (opcion_menu != 2);
        }
    }

    return -1;
}

int registrarNuevoJugador(v_jugadores *jugadores)
{
    t_jugador nuevo;
    int pos;

    nuevo.id_jugador = 0;
    nuevo.inventario = NULL;
    nuevo.num_objetos = 0;

    printf("Nombre completo: ");
    fgets(nuevo.nomb_jugador, MAX_NOMBRE, stdin);
    nuevo.nomb_jugador[strcspn(nuevo.nomb_jugador, "\n")] = '\0';

    printf("Nombre de usuario: ");
    scanf("%10s", nuevo.jugador);
    limpiarBuffer();

    printf("Contrasena: ");
    scanf("%8s", nuevo.contrasena);
    limpiarBuffer();

    if (!altaJugador(jugadores, nuevo))
    {
        printf("No se pudo registrar el jugador.\n");
        return -1;
    }

    guardarJugadores(*jugadores);

    pos = buscarJugadorPorUsername(*jugadores, nuevo.jugador);
    if (pos != -1)
    {
        printf("Registro correcto. Bienvenido/a %s\n",
               jugadores->jugadores[pos].nomb_jugador);
    }

    return pos;
}


/* ========================= PARTIDA NUEVA / CARGADA ========================= */

int buscarSalaInicial(v_salas salas)
{
    int i;

    for (i = 0; i < salas.num_salas; i++)
    {
        if (strcmp(salas.sala[i].tipo, "INICIAL") == 0)
        {
            return salas.sala[i].id;
        }
    }

    return -1;
}

void inicializarEstadoNuevaPartida(t_partida *partida,
                                    int id_jugador,
                                    int id_sala_inicial,
                                    v_items items,
                                    v_conexiones conx,
                                    t_puzle *puzles,
                                    int num_puzles)
{
    int i;

    inicializarPartida(partida);

    partida->id_jugador = id_jugador;
    partida->id_sala = id_sala_inicial;
    partida->datos = 1;

    for (i = 0; i < items.num_items; i++)
    {
        actualizarObjetoPartida(partida,
                                items.item[i].id,
                                items.item[i].localizacion);
    }

    for (i = 0; i < conx.num_conexiones; i++)
    {
        actualizarConexionPartida(partida,
                                  conx.conexiones[i].id_cnx,
                                  conx.conexiones[i].estado);
    }

    for (i = 0; i < num_puzles; i++)
    {
        actualizarPuzlePartida(partida,
                               puzles[i].id,
                               puzles[i].resuelto);
    }
}

void aplicarEstadoPartida(t_partida partida,
                           v_items *items,
                           v_conexiones *conx,
                           t_puzle *puzles,
                           int num_puzles,
                           t_jugador *jugador_actual)
{
    int i;
    int pos;

    for (i = 0; i < partida.num_objetos; i++)
    {
        pos = buscarItem(items, partida.objetos[i].id_obj);
        if (pos != -1)
        {
            items->item[pos].localizacion = partida.objetos[i].localizacion;
        }
    }

    for (i = 0; i < partida.num_conexiones; i++)
    {
        int j;
        for (j = 0; j < conx->num_conexiones; j++)
        {
            if (strcmp(conx->conexiones[j].id_cnx, partida.conexiones[i].id_cnx) == 0)
            {
                strcpy(conx->conexiones[j].estado, partida.conexiones[i].estado);
            }
        }
    }

    for (i = 0; i < partida.num_puzles; i++)
    {
        pos = buscarPuzlePorId(puzles, num_puzles, partida.puzles[i].id_puzle);
        if (pos != -1)
        {
            puzles[pos].resuelto = partida.puzles[i].resuelto;
        }
    }

    reconstruirInventarioJugadorDesdeItems(jugador_actual, *items);
}

void reconstruirInventarioJugadorDesdeItems(t_jugador *jugador, v_items items)
{
    int i;

    while (jugador->num_objetos > 0)
    {
        quitarObjetoAJugador(jugador, jugador->inventario[0]);
    }

    for (i = 0; i < items.num_items; i++)
    {
        if (items.item[i].localizacion == -1)
        {
            agregarObjetoAJugador(jugador, items.item[i].id);
        }
    }
}


/* ========================= VISUALIZACION ========================= */

void mostrarInventarioJugadorActual(t_jugador jugador, v_items items)
{
    int i;
    int pos;

    printf("Inventario:\n");

    if (jugador.num_objetos == 0)
    {
        printf("Vacio\n");
        return;
    }

    for (i = 0; i < jugador.num_objetos; i++)
    {
        pos = buscarItem(&items, jugador.inventario[i]);
        if (pos != -1)
        {
            printf("%s - %s\n",
                   items.item[pos].id,
                   items.item[pos].desc);
        }
        else
        {
            printf("%s\n", jugador.inventario[i]);
        }
    }
}

void mostrarSalidasDesdeSala(int sala_actual, v_conexiones conx)
{
    int i;

    printf("Salidas:\n");

    for (i = 0; i < conx.num_conexiones; i++)
    {
        if (conx.conexiones[i].id_org == sala_actual)
        {
            printf("-> Sala %02d (%s)\n",
                   conx.conexiones[i].id_dst,
                   conx.conexiones[i].estado);
        }
    }
}

int esSalaSalida(v_salas salas, int id_sala)
{
    int pos = buscarSalaPorId(salas, id_sala);

    if (pos == -1)
    {
        return 0;
    }

    return strcmp(salas.sala[pos].tipo, "SALIDA") == 0;
}


/* ========================= ACCIONES ========================= */

int jugadorCogeObjeto(t_partida *partida,
                      t_jugador *jugador,
                      v_items *items,
                      int sala_actual,
                      const char *id_obj)
{
    if (!cogerItem(items, sala_actual, id_obj))
    {
        return 0;
    }

    if (!agregarObjetoAJugador(jugador, id_obj))
    {
        soltarItem(items, sala_actual, id_obj);
        return 0;
    }

    actualizarObjetoPartida(partida, id_obj, -1);
    return 1;
}

int jugadorSueltaObjeto(t_partida *partida,
                        t_jugador *jugador,
                        v_items *items,
                        int sala_actual,
                        const char *id_obj)
{
    if (!tieneObjetoJugador(*jugador, id_obj))
    {
        return 0;
    }

    if (!soltarItem(items, sala_actual, id_obj))
    {
        return 0;
    }

    if (!quitarObjetoAJugador(jugador, id_obj))
    {
        cogerItem(items, sala_actual, id_obj);
        return 0;
    }

    actualizarObjetoPartida(partida, id_obj, sala_actual);
    return 1;
}

int usarObjetoEnConexion(t_partida *partida,
                          t_jugador jugador,
                          v_conexiones *conx,
                          int sala_actual,
                          const char *id_obj)
{
    int i;

    if (!tieneObjetoJugador(jugador, id_obj))
    {
        return 0;
    }

    for (i = 0; i < conx->num_conexiones; i++)
    {
        if (conx->conexiones[i].id_org == sala_actual &&
            strcmp(conx->conexiones[i].estado, "Bloqueada") == 0 &&
            strcmp(conx->conexiones[i].cond, id_obj) == 0)
        {
            strcpy(conx->conexiones[i].estado, "Activa");
            actualizarConexionPartida(partida,
                                      conx->conexiones[i].id_cnx,
                                      "Activa");
            return 1;
        }
    }

    return 0;
}

int resolverPuzleOConexion(t_partida *partida,
                            v_conexiones *conx,
                            t_puzle *puzles,
                            int num_puzles,
                            int sala_actual)
{
    int i;
    int pos_puzle;
    char respuesta[MAX_RESPUESTA];

    for (i = 0; i < conx->num_conexiones; i++)
    {
        if (conx->conexiones[i].id_org == sala_actual &&
            strcmp(conx->conexiones[i].estado, "Bloqueada") == 0 &&
            conx->conexiones[i].cond[0] == 'P')
        {
            pos_puzle = buscarPuzlePorId(puzles, num_puzles, conx->conexiones[i].cond);

            if (pos_puzle == -1)
            {
                continue;
            }

            mostrarPuzle(&puzles[pos_puzle]);
            printf("Respuesta: ");
            fgets(respuesta, MAX_RESPUESTA, stdin);
            respuesta[strcspn(respuesta, "\n")] = '\0';

            if (resolverPuzle(&puzles[pos_puzle], respuesta))
            {
                strcpy(conx->conexiones[i].estado, "Activa");
                actualizarConexionPartida(partida,
                                          conx->conexiones[i].id_cnx,
                                          "Activa");
                actualizarPuzlePartida(partida,
                                       puzles[pos_puzle].id,
                                       1);
                printf("Puzle resuelto. Conexion desbloqueada.\n");
                return 1;
            }

            printf("Respuesta incorrecta.\n");
            return 0;
        }
    }

    printf("No hay ningun puzle utilizable desde esta sala.\n");
    return 0;
}


/* ========================= MENU DE PARTIDA ========================= */

void menuPartida(t_partida *partida,
                 t_jugador *jugador_actual,
                 v_salas salas,
                 v_conexiones *conx,
                 v_items *items,
                 t_puzle *puzles,
                 int num_puzles)
{
    int opcion;

    do
    {
        printf("\nSala: %02d\n", partida->id_sala);
        printf("1. Describir sala\n");
        printf("2. Examinar (objetos y salidas)\n");
        printf("3. Entrar en otra sala\n");
        printf("4. Coger objeto\n");
        printf("5. Soltar objeto\n");
        printf("6. Inventario\n");
        printf("7. Usar objeto\n");
        printf("8. Resolver puzle / introducir codigo\n");
        printf("9. Guardar partida\n");
        printf("10. Volver\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion)
        {
            case 1:
            {
                int pos = buscarSalaPorId(salas, partida->id_sala);
                if (pos != -1)
                {
                    mostrarSala(salas.sala[pos]);

                    if (esSalaSalida(salas, partida->id_sala))
                    {
                        printf("Has llegado a la SALIDA. Has ganado.\n");
                        return;
                    }
                }
                break;
            }

            case 2:
                printf("Objetos en la sala:\n");
                mostrarItemsSala(items, partida->id_sala);
                mostrarSalidasDesdeSala(partida->id_sala, *conx);
                break;

            case 3:
            {
                int destino;
                int pos_cnx;

                printf("Introduce la sala destino: ");
                scanf("%d", &destino);
                limpiarBuffer();

                pos_cnx = buscarConexion(partida->id_sala, destino, *conx);

                if (pos_cnx == -1)
                {
                    printf("No existe conexion a esa sala.\n");
                }
                else if (strcmp(conx->conexiones[pos_cnx].estado, "Activa") != 0)
                {
                    printf("Conexion bloqueada. Condicion: %s\n",
                           conx->conexiones[pos_cnx].cond);
                }
                else
                {
                    partida->id_sala = destino;
                    printf("Te has movido a la sala %02d\n", destino);
                }
                break;
            }

            case 4:
            {
                char id_obj[MAX_ID_OBJ];

                printf("ID del objeto a coger: ");
                scanf("%4s", id_obj);
                limpiarBuffer();

                if (jugadorCogeObjeto(partida,
                                      jugador_actual,
                                      items,
                                      partida->id_sala,
                                      id_obj))
                {
                    printf("Objeto cogido correctamente.\n");
                }
                else
                {
                    printf("No se puede coger ese objeto.\n");
                }
                break;
            }

            case 5:
            {
                char id_obj[MAX_ID_OBJ];

                printf("ID del objeto a soltar: ");
                scanf("%4s", id_obj);
                limpiarBuffer();

                if (jugadorSueltaObjeto(partida,
                                        jugador_actual,
                                        items,
                                        partida->id_sala,
                                        id_obj))
                {
                    printf("Objeto soltado correctamente.\n");
                }
                else
                {
                    printf("No se puede soltar ese objeto.\n");
                }
                break;
            }

            case 6:
                mostrarInventarioJugadorActual(*jugador_actual, *items);
                break;

            case 7:
            {
                char id_obj[MAX_ID_OBJ];

                printf("ID del objeto a usar: ");
                scanf("%4s", id_obj);
                
                limpiarBuffer();

                if (usarObjetoEnConexion(partida,
                                         *jugador_actual,
                                         conx,
                                         partida->id_sala,
                                         id_obj))
                {
                    printf("Objeto usado correctamente.\n");
                }
                else
                {
                    printf("Ese objeto no se puede aplicar aqui.\n");
                }
                break;
            }

            case 8:
                resolverPuzleOConexion(partida,
                                       conx,
                                       puzles,
                                       num_puzles,
                                       partida->id_sala);
                break;

            case 9:
                if (guardarPartida(*partida))
                {
                    printf("Partida guardada.\n");
                }
                else
                {
                    printf("No se pudo guardar la partida.\n");
                }
                break;

            case 10:
                printf("Volviendo al menu principal...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 10);
}