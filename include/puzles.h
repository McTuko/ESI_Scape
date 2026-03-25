#ifndef PUZLES_H
#define PUZLES_H

#define MAX_DESC 151
#define MAX_SOL 50

typedef struct {
    char id[4];             // P01
    char nombre[16];
    int sala;
    char tipo[10];          // "Codigo" o "Palabra"
    char descripcion[MAX_DESC];
    char solucion[MAX_SOL];
    int resuelto;
} t_puzle;

// Funciones
int cargarPuzles(const char *nombreFichero, t_puzle **puzles);

int hayPuzleSala(t_puzle *puzles, int n, int sala);
void mostrarPuzle(t_puzle *p);

int resolverPuzle(t_puzle *p, char *respuesta);

#endif