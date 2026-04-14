#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/jugadores.h"
#include "../include/salas.h"
#include "../include/conexiones.h"
#include "../include/items.h"
#include "../include/puzles.h"
#include "../include/partida.h"

#define MAX_RESPUESTA 100

/* ========================= PROTOTIPOS AUX ========================= */

static void limpiarBuffer(void);

static int loginORegistro(v_jugadores *jugadores);
static int registrarNuevoJugador(v_jugadores *jugadores);

static int buscarSalaInicial(v_salas salas);
static void inicializarEstadoNuevaPartida(t_partida *partida,
                                          int id_jugador,
                                          int id_sala_inicial,
                                          v_items items,
                                          v_conexiones conx,
                                          t_puzle *puzles,
                                          int num_puzles);

static void aplicarEstadoPartida(t_partida partida,
                                 v_items *items,
                                 v_conexiones *conx,
                                 t_puzle *puzles,
                                 int num_puzles,
                                 t_jugador *jugador_actual);

static void reconstruirInventarioJugadorDesdeItems(t_jugador *jugador,
                                                   v_items items);

static void mostrarInventarioJugadorActual(t_jugador jugador, v_items items);
static void mostrarSalidasDesdeSala(int sala_actual, v_conexiones conx);

static int jugadorCogeObjeto(t_partida *partida,
                             t_jugador *jugador,
                             v_items *items,
                             int sala_actual,
                             const char *id_obj);

static int jugadorSueltaObjeto(t_partida *partida,
                               t_jugador *jugador,
                               v_items *items,
                               int sala_actual,
                               const char *id_obj);

static int usarObjetoEnConexion(t_partida *partida,
                                t_jugador jugador,
                                v_conexiones *conx,
                                int sala_actual,
                                const char *id_obj);

static int resolverPuzleOConexion(t_partida *partida,
                                  v_conexiones *conx,
                                  t_puzle *puzles,
                                  int num_puzles,
                                  int sala_actual);

static int esSalaSalida(v_salas salas, int id_sala);

static void menuPartida(t_partida *partida,
                        t_jugador *jugador_actual,
                        v_salas salas,
                        v_conexiones *conx,
                        v_items *items,
                        t_puzle *puzles,
                        int num_puzles);


/* ========================= MAIN ========================= */

int main(void)
{
    v_jugadores jugadores;
    v_salas salas;
    v_conexiones conexiones;
    v_items items;
    t_puzle *puzles = NULL;
    int num_puzles = 0;

    t_partida partida;
    int pos_jugador;
    int opcion_principal;
    int sala_inicial;

    if (!cargarJugadores(&jugadores))
    {
        printf("Error al cargar Jugadores.txt\n");
        return 1;
    }

    if (!cargarSalas(&salas))
    {
        printf("Error al cargar Salas.txt\n");
        liberarJugadores(&jugadores);
        return 1;
    }

    if (!cargarConexiones(&conexiones))
    {
        printf("Error al cargar Conexiones.txt\n");
        liberarJugadores(&jugadores);
        freeSalas(&salas);
        return 1;
    }

    if (!cargarItems(&items))
    {
        printf("Error al cargar Objetos.txt\n");
        liberarJugadores(&jugadores);
        freeSalas(&salas);
        liberarConexiones(&conexiones);
        return 1;
    }

    num_puzles = cargarPuzles(ARCHIVO_PUZLES, &puzles);
    if (num_puzles == 0 && puzles == NULL)
    {
        printf("Error al cargar Puzles.txt\n");
        liberarJugadores(&jugadores);
        freeSalas(&salas);
        liberarConexiones(&conexiones);
        liberarItems(&items);
        return 1;
    }

    printf("Bienvenido al juego\n");
    printf("ESI ESCAPE\n");

    pos_jugador = loginORegistro(&jugadores);
    if (pos_jugador == -1)
    {
        printf("No se pudo iniciar sesion.\n");
        liberarJugadores(&jugadores);
        freeSalas(&salas);
        liberarConexiones(&conexiones);
        liberarItems(&items);
        liberarPuzles(&puzles);
        return 1;
    }

    do
    {
        printf("\nMENU PRINCIPAL\n");
        printf("1. Nueva partida\n");
        printf("2. Cargar partida\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion_principal);
        limpiarBuffer();

        switch (opcion_principal)
        {
            case 1:
                sala_inicial = buscarSalaInicial(salas);
                if (sala_inicial == -1)
                {
                    printf("No se ha encontrado una sala inicial.\n");
                    break;
                }

                inicializarEstadoNuevaPartida(&partida,
                                              jugadores.jugadores[pos_jugador].id_jugador,
                                              sala_inicial,
                                              items,
                                              conexiones,
                                              puzles,
                                              num_puzles);

                reconstruirInventarioJugadorDesdeItems(&jugadores.jugadores[pos_jugador], items);

                menuPartida(&partida,
                            &jugadores.jugadores[pos_jugador],
                            salas,
                            &conexiones,
                            &items,
                            puzles,
                            num_puzles);

                liberarPartida(&partida);
                break;

            case 2:
                if (!cargarPartida(&partida))
                {
                    printf("No se pudo cargar la partida.\n");
                    break;
                }

                if (partida.id_jugador != jugadores.jugadores[pos_jugador].id_jugador)
                {
                    printf("La partida guardada pertenece a otro jugador.\n");
                    liberarPartida(&partida);
                    break;
                }

                aplicarEstadoPartida(partida,
                                     &items,
                                     &conexiones,
                                     puzles,
                                     num_puzles,
                                     &jugadores.jugadores[pos_jugador]);

                menuPartida(&partida,
                            &jugadores.jugadores[pos_jugador],
                            salas,
                            &conexiones,
                            &items,
                            puzles,
                            num_puzles);

                liberarPartida(&partida);
                break;

            case 3:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion_principal != 3);

    guardarJugadores(jugadores);

    liberarJugadores(&jugadores);
    freeSalas(&salas);
    liberarConexiones(&conexiones);
    liberarItems(&items);
    liberarPuzles(&puzles);

    return 0;
}


/* ========================= LOGIN / REGISTRO ========================= */

static int loginORegistro(v_jugadores *jugadores)
{
    char usuario[MAX_USER];
    char pass[MAX_PASS];
    int pos;
    int opcion;

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
        return -1;
    }

    printf("El usuario no existe.\n");
    printf("1. Registrarse\n");
    printf("2. Volver\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    limpiarBuffer();

    if (opcion == 1)
    {
        return registrarNuevoJugador(jugadores);
    }

    return -1;
}

static int registrarNuevoJugador(v_jugadores *jugadores)
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

static int buscarSalaInicial(v_salas salas)
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

static void inicializarEstadoNuevaPartida(t_partida *partida,
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

static void aplicarEstadoPartida(t_partida partida,
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

static void reconstruirInventarioJugadorDesdeItems(t_jugador *jugador, v_items items)
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

static void mostrarInventarioJugadorActual(t_jugador jugador, v_items items)
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

static void mostrarSalidasDesdeSala(int sala_actual, v_conexiones conx)
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

static int esSalaSalida(v_salas salas, int id_sala)
{
    int pos = buscarSalaPorId(salas, id_sala);

    if (pos == -1)
    {
        return 0;
    }

    return strcmp(salas.sala[pos].tipo, "SALIDA") == 0;
}


/* ========================= ACCIONES ========================= */

static int jugadorCogeObjeto(t_partida *partida,
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

static int jugadorSueltaObjeto(t_partida *partida,
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

static int usarObjetoEnConexion(t_partida *partida,
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

static int resolverPuzleOConexion(t_partida *partida,
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

static void menuPartida(t_partida *partida,
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


/* ========================= AUX GENERALES ========================= */

static void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}