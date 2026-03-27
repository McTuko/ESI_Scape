#ifndef MENU_H
#define MENU_H
#include "../include/partida.h"

void menu(t_partida*);
void impr_menu();
void select_m(int*);
void config(t_partida*);
void impr_config();
void select_c(int*);
void jugar(t_partida*);
void impr_jugar();
void select_j(int*);
void ganador(t_partida*, int);
void portada();

#endif