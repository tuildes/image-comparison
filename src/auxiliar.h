#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Retorna a DISTANCIA EUCLIDIANA entre dois vetores de tamanho LENGHT
double euclidian_distance(int *v1, int *v2, size_t lenght);

// Imprime o manual de OPCOES do software
// Retorna 1
int options_manual();

// Destroir matrizes de qualquer natureza
void destroy_matrix(unsigned char **n, size_t l);

#endif // __AUXILIAR_H__