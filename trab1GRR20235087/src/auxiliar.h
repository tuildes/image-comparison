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

#define PRINT_MANUAL_AND_ERROR 0

/*
    Faz e retorna a distancia euclediana entre dois vetores
    Considera que ambos vetores vao de [0..255] de tamanho

    @param (double *v1) primeiro vetor
    @param (double *v2) segundo vetor
    @returns (double) distancia euclediana entre dois vetores
*/ 
double euclidian_distance(double *v1, double *v2);


/*
    Imprime o manual de OPCOES do software

    @returns (int) sempre 1
*/
int options_manual();

/*
    Destroi uma matriz (alocacao dinamica)

    @param (unsigned char **n) matriz a ser destruida
    @param (size_t l) altura da matriz
*/ 
void destroy_matrix(unsigned char **n, size_t l);

/*
    Concatena e retorna uma string no formato
    "dir/name"

    @param (char *dir) nome do diretorio
    @param (char *name) nome do arquivo
    @return (char *) string que concatena ambos (novo ponteiro)
*/
char* prepare_location_image(char *dir, char *name);

#endif // __AUXILIAR_H__
