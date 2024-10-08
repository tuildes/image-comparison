#ifndef __LBP_H__
#define __LBP_H__

#include "auxiliar.h"

// Abre o arquivo PGM (P2 ou P5)
// Retorna uma matriz que comporta essa imagem
// Salva a LARGURA e ALTURA
unsigned char** pgm_image_to_matrix(FILE *arc, size_t *width, size_t *height);

// Retorna uma matriz de LARGURA e ALTURA definidas
// Todos os elementos zerados

// Cria uma matriz zerada
unsigned char **create_matrix_lbp(size_t width, size_t height);

// Escreve no arquivo PGM
void create_pgm_image(size_t width, size_t height, unsigned short int max, 
                    unsigned char **m, FILE *pgm);

unsigned char print_local(unsigned char *vector, unsigned char comp);

int create_histogram_archive(size_t row, size_t column, 
                            unsigned char **matrix, char *name);

int create_lbp_pattern(size_t width, size_t height, unsigned char *max,
                        unsigned char **new, unsigned char **original);

#endif // __LBP_H__