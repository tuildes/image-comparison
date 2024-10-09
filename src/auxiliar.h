#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h> 

#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Retorna a DISTANCIA EUCLIDIANA entre dois vetores de tamanho LENGHT
double euclidian_distance(unsigned int *v1, unsigned int *v2);

// Imprime o manual de OPCOES do software
// Retorna 1
int options_manual();

// Destroir matrizes de qualquer natureza
void destroy_matrix(unsigned char **n, size_t l);

char* prepare_location_image(char *dir, char *name);

#endif // __AUXILIAR_H__