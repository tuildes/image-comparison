#include "lbp.h"

unsigned char** pgm_image_to_matrix(FILE *arc, size_t *width, size_t *height) {

    unsigned char** m; // Matriz a ser retornada
    char typeP[10]; // Tipo da imagem (P2 ou P5)
    short unsigned int n, max;

    // Fazer a leitura de TIPO, LARGURA, ALTURA e VALOR MAXIMO
    fscanf(arc, "%10s", typeP);
    fscanf(arc, "%lu %lu %hu", width, height, &max);

    m = (unsigned char **) malloc (sizeof(unsigned char *) * (*height));

    if (m == NULL) return NULL; // Erro ao alocar

    for(size_t i = 0; i < (*height); i++)
        m[i] = (unsigned char*) malloc (sizeof(unsigned char) * (*width));

    for(size_t i = 0; i < (*height); i++) {
        for(size_t j = 0; j < (*width); j++) {
            fscanf(arc, "%hu", &n);
            m[i][j] = (unsigned char) n;
        }
    }

    return m;
}

// Cria uma matriz zerada
unsigned char **create_matrix_lbp(size_t width, size_t height) {
    unsigned char** m;

    m = (unsigned char **) malloc (sizeof(unsigned char *) * height);

    for(size_t i = 0; i < height; i++)
        m[i] = (unsigned char*) calloc (width, sizeof(unsigned char)); 

    return m;
}

// Escreve no arquivo PGM
void create_pgm_image(size_t width, size_t height, unsigned short int max, 
                    unsigned char **m, FILE *pgm) {

    // Ir pro inicio
    // Trocaro  255 pelo MAXIMO
    fprintf(pgm, "P2\n%lu %lu\n%hu\n", width, height, max);

    // Colocar a matriz no arquivo
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++)
            fprintf(pgm, "%hu ", m[i][j]);
        fprintf(pgm, "\n");
    }

    return;
}

unsigned char print_local(unsigned char *vector, unsigned char comp) {
    unsigned char res = 0, j = 1;

    for (short int i = 0; i < 8; i++) {
        if (vector[i] > comp) res += j;
        j *= 2;
    }

    return res;
}

unsigned char __local_binnary_pattern(size_t row, size_t column, 
                                    unsigned char **matrix) {

    unsigned char res = 0, factor = 1;
    
    for(size_t i = 0; i <= 2; i++) {
        for(size_t j = 0; j <= 2; j++) {
            // Ignorar o numero que estamos analisando
            if ((i == 1) && (j == 1)) continue;

            if (matrix[(column + i)][(row + j)] >= matrix[(column + 1)][(row + 1)])
                res += factor;

            factor *= 2;
        }
    }
    
    return res;
}

unsigned char* __create_histogram_lbp(size_t row, size_t column,
                                    unsigned char **matrix) {

    unsigned char *h;

    if ((h = (unsigned char *)calloc(256, sizeof(unsigned char))) == NULL)
        return NULL;

    for(size_t j = 0; j < row; j++)
        for(size_t i = 0; i < column; i++)
            h[matrix[i][j]]++;

    return h;
}

int create_histogram_archive(size_t row, size_t column, 
                            unsigned char **matrix, char *name) {

    FILE *histogram;
    char *h;

    histogram = fopen(name, "w");
    h = __create_histogram_lbp(row, column, matrix);

    // Tratamentos de erros
    if (histogram == NULL) {
        perror("Erro ao criar arquivo LBP");
        return 1;
    }

    if (h == NULL) {
        printf("Erro ao criar vetor de histograma\n");
        return 1;
    }

    // Escrever no arquivo LBP (BINARIO)
    fwrite(h, 1, 256, histogram);

    fclose(histogram);
    free(h);

    return 0;
}

int create_lbp_pattern(size_t width, size_t height, unsigned char *max,
                        unsigned char **new, unsigned char **original) {
    
    // Casos de ERRO (impossivel iterar)
    if ((width < 3) || (height < 3) || (original == NULL) || (new == NULL))
        return EXIT_FAILURE;

    *max = 0;

    // Iterar sobre TODA a MATRIZ (1..n-1)(1..n-1)
    for(size_t i = 1; i <= (height - 2); i++) {
        for(size_t j = 1; j <= (width - 2); j++) {
            new[i][j] = __local_binnary_pattern((j - 1), (i - 1), original);
            if (*max < new[i][j]) *max = new[i][j];
        }
    }

    return EXIT_SUCCESS;
}
