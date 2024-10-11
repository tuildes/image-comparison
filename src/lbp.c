#include "lbp.h"

unsigned char** pgm_image_to_matrix(FILE *arc, size_t *width, size_t *height) {

    unsigned char** m; // Matriz a ser retornada
    char *res;
    char typeP[5], line[256]; // Tipo da imagem (P2 ou P5)
    short unsigned int n, max, counter = 0;

    // Ler a atual linha e remover comentarios
    while(counter < 3) {
        res = fgets(line, 255, arc);
        if (res == NULL) return NULL;
        if (line[0] == '#') continue; // Remover comentario

        counter++;
        // Fazer a leitura de TIPO, LARGURA, ALTURA e VALOR MAXIMO
        switch(counter) {
            case 1: { 
                if (!sscanf(line, "%s", typeP))
                    return NULL;
                break;  
            }
            case 2: { 
                if (!sscanf(line, "%lu %lu", width, height))
                    return NULL;
                break; 
            }
            case 3: { 
                if (!sscanf(line, "%hu", &max))
                    return NULL;
                break; 
            }
            default: break;
        }
    }

    if( (!*height) || (!width) || (!arc) || 
        (*height < 3) || (*width < 3) || (!typeP[1])) {
        return NULL;
    }

    m = (unsigned char **) malloc (sizeof(unsigned char *) * (*height));
    if (m == NULL) return NULL; // Erro ao alocar

    for(size_t i = 0; i < (*height); i++)
        m[i] = (unsigned char*) malloc (sizeof(unsigned char) * (*width));

    // P2 FORMAT
    if (typeP[1] == '2') {
        for(size_t i = 0; i < (*height); i++) {
            for(size_t j = 0; j < (*width); j++) {
                fscanf(arc, "%hu", &n);
                m[i][j] = (unsigned char) n;
            }
        }

    // P5 FORMAT
    } else if (typeP[1] == '5') {
        for(size_t i = 0; i < (*height); i++) fread(m[i], sizeof(unsigned char), (*width), arc);

    } else { // Caso FALHA (fallback)
        for(size_t i = 0; i < (*height); i++) { 
            free(m[i]); 
            return NULL; 
        }
    }

    return m;
}

// Retorna uma matriz de LARGURA e ALTURA definidas
// Todos os elementos zerados
unsigned char** __blank_matrix(size_t width, size_t height) {
    unsigned char** m;

    m = (unsigned char **) malloc (sizeof(unsigned char *) * height);

    for(size_t i = 0; i < height; i++)
        m[i] = (unsigned char*) calloc (width, sizeof(unsigned char)); 

    return m;
}

// Encontra o valor unitario da LBP com base da matriz dada
unsigned char __local_binnary_pattern(size_t row, size_t column, 
                                    unsigned char **matrix) {

    unsigned char res = 0, factor = 1;
    
    for(size_t i = 0; i <= 2; i++) {
        for(size_t j = 0; j <= 2; j++) {
            // Ignorar o numero que estamos analisando
            if ((i == 1) && (j == 1)) continue;

            if (matrix[(column + i)][(row + j)] >= matrix[(column + 1)][(row + 1)])
                res += factor;
            factor = factor << 1; // Multiplicacao por dois
        }
    }
    
    return res;
}

unsigned char** create_lbp_matrix(size_t width, size_t height, 
                                unsigned char *max,
                                unsigned char **new, 
                                unsigned char **original) {
    
    // Casos de ERRO (impossivel iterar)
    if ((width < 3) || (height < 3) || (original == NULL))
        return NULL;

    *max = 0;
    new = __blank_matrix(width, height);

    // Iterar sobre TODA a MATRIZ (1..n-1)(1..n-1)
    for(size_t i = 1; i < (height - 1); i++) {
        for(size_t j = 1; j < (width - 1); j++) {
            new[i][j] = __local_binnary_pattern((j - 1), (i - 1), original);
            if (*max < new[i][j]) *max = new[i][j];
        }
    }

    return new;
}


// Escreve no arquivo PGM (P5)
void create_pgm_image(size_t width, size_t height, unsigned short int max, 
                    unsigned char **m, FILE *pgm) {

    fprintf(pgm, "P5\n%lu %lu\n%hu\n", width, height, max);

    // Colocar a matriz no arquivo
    for(size_t i = 0; i < height; i++)
        fwrite(m[i], 1, width, pgm);

    return;
}

// ERRO => INTEIROS
unsigned int* __create_histogram_lbp(size_t row, size_t column,
                                    unsigned char **matrix) {

    unsigned int *h;

    if ((h = (unsigned int *)calloc(256, sizeof(unsigned int))) == NULL)
        return NULL;

    for(size_t j = 0; j < row; j++)
        for(size_t i = 0; i < column; i++)
            h[matrix[i][j]]++;

    return h;
}

int create_histogram_archive(size_t row, size_t column, 
                            unsigned char **matrix, char *name) {

    FILE *histogram;
    unsigned int *h;

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
    fwrite(h, sizeof(unsigned int), 256, histogram);

    fclose(histogram);
    free(h);

    return 0;
}

int verify_histogram_archive(char *name) {
    char *aux;
    FILE *arc;

    aux = concat_pgm(name);

    arc = fopen(aux, "r");
    if (arc == NULL) {
        free(aux);
        return 1; // Nao existe
    }

    fclose(arc);
    free(aux);
    return 0;
}

char* concat_pgm(char *name) {
    char* aux;
    size_t dot = 0;
    for(size_t i = strlen(name); i > 0; i--) {
        if (name[i] == '.') {
            dot = i;
            break;
        }
    }

    if (dot == 0) return NULL;

    if ((aux = (char *)malloc(sizeof(char) * (strlen(name) + 5))) == NULL) 
        return NULL; // ERRO
    
    strcpy(aux, name);
    aux[dot] = '\0';
    strcat(aux, ".lbp");
    return aux;
}

unsigned int* histogram_file_to_vector(FILE *a) {
    fseek(a, 0, SEEK_SET);

    unsigned int *v;

    if ((v = (unsigned int *)calloc(256, sizeof(unsigned int))) == NULL)
        return NULL;

    // Verificar se os binarios estao certos
    size_t bytes = fread(v, sizeof(unsigned int), 256, a);

    if (bytes < 256) {
        free(v);
        return NULL;
    }

    // printf("%hhu\n", v[1]);

    return v;
}
