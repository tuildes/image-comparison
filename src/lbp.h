#ifndef __LBP_H__
#define __LBP_H__

#include "auxiliar.h"

// Abre o arquivo PGM (P2 ou P5)
// Retorna uma matriz que comporta essa imagem
// Salva a LARGURA e ALTURA
unsigned char** pgm_image_to_matrix(FILE *arc, size_t *width, size_t *height);


unsigned char** create_lbp_matrix(size_t width, size_t height, 
                                unsigned char *max,
                                unsigned char **new, 
                                unsigned char **original);

// Escreve no arquivo PGM (P5)
void create_pgm_image(size_t width, size_t height, unsigned short int max, 
                    unsigned char **m, FILE *pgm);

int create_histogram_archive(size_t row, size_t column, 
                            unsigned char **matrix, char *name);

int verify_histogram_archive(char *name);

unsigned int* histogram_file_to_vector(FILE *a);

char* concat_pgm(char *name);

#endif // __LBP_H__