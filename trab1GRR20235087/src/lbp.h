#ifndef __LBP_H__
#define __LBP_H__

#include "auxiliar.h"

/*
    Recebe um arquivo do tipo PGM (P2 ou P5)
    Transcreve o arquivo em uma matrix do tipo unsigned char
    Define *width e *height para a largura e altura da imagem
    retorna NULL em caso de ERRO (falha)

    @param (FILE) *arc - arquivo pgm com a imagem
    @param (size_t *) width - largura da imagem entrada (a ser modificado)
    @param (size_t *) height - altura da imagem entrada (a ser modificado)
    @param (char *) type - tipo da imagem (2 ou 5)
    @returns (unsigned char**) matriz alocada com o arquivo PGM
*/
unsigned char** pgm_image_to_matrix(FILE *arc, size_t *width, size_t *height, 
                                    char *type);


/*
    Cria uma segunda matriz seguindo o LBP de uma matriz original

    @param (size_t) width - largura da imagem entrada
    @param (size_t) height - altura da imagem entrada
    @param (unsigned char *) max - tom de preto maximo (a ser modificado)
    @param (unsigned char **) new - matriz nova a ser alocada e criada
    @param (unsigned char **) original - matriz original usada de base
    @returns @unsigned char **) matriz alocada com o LBP (**new)
*/
unsigned char** create_lbp_matrix(size_t width, size_t height, 
                                unsigned char *max,
                                unsigned char **new, 
                                unsigned char **original);

/*
    Escreve em um arquivo, uma matrix LBP e criando um arquivo PGM P5

    @param (size_t) width - largura da imagem entrada
    @param (size_t) height - altura da imagem entrada
    @param (unsigned char) max - tom de preto maximo (a ser modificado)
    @param (unsigned char **) m - matriz usada para escrita cvom LBP
    @param (FILE *) pgm - arquivo a ser escrito
    @param (char) type - tipo do arquivo ('2' ou '5')
*/ 
void create_pgm_image(size_t width, size_t height, unsigned short int max, 
                    unsigned char **m, FILE *pgm, char type);

/*
    Recebe um arquivo do tipo PGM (P2 ou P5)
    Transcreve o arquivo em uma matrix do tipo unsigned char
    Define *width e *height para a largura e altura da imagem
    retorna NULL em caso de ERRO (falha)

    @param (size_t *) row - largura da imagem entrada 
    @param (size_t *) column - altura da imagem entrada
    @param (unsigned char **) matrix - matriz a ser usada para criar LBP
    @param (unsigned char *) name - nome do arquivo de histograma
    @returns (int) - status do pedido (0 para sucesso)
*/ 
int create_histogram_archive(size_t row, size_t column, 
                            unsigned char **matrix, char *name);

/*
    Verifica se existe um arquivo LBP de certo arquivo

    @param (char*) name - nome do arquivo para verificar 
    @param (int) 1 para nao existe e 0 para existe
*/ 
int verify_histogram_archive(char *name);

/*
    Cria um vetor com base em arquivo de HISTOGRAMAa

    @param (FILE) *a - arquivo de histograma (LBP)
    @return (unsigned int *) - vetor alocado
*/ 
double* histogram_file_to_vector(FILE *a);

/*
    Concatena um texto com .lbp no fim

    @param (char *) name - string a ser concatenada
    @returs (char *) string alocada com .lbp no fim
*/ 
char* concat_pgm(char *name);

#endif // __LBP_H__