// Includes de todo o projeto
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

// Retorna a DISTANCIA EUCLIDIANA entre dois vetores de tamanho LENGHT
double euclidian_distance(int *v1, int *v2, size_t lenght) {
    double res;
    for (size_t i = 0; i < lenght; i++) {
        res += ((*v1 - *v2) * (*v1 - *v2));
        v1++;
        v2++;
    }
    return sqrt(res);
}

// Cria matriz com base no arquivo ARC
// Faz leitura do arquivo
unsigned char** create_matrix_pgm(size_t width, size_t height, FILE *arc) {
    unsigned char** m;
    short unsigned int n;

    // Fazer a leitura interna

    m = (unsigned char **) malloc (sizeof(unsigned char *) * height);

    for(size_t i = 0; i < height; i++)
        m[i] = (unsigned char*) malloc (sizeof(unsigned char) * width);

    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
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

// Imprime a matriz
void print_matrix(size_t width, size_t height, unsigned char **m) {
    for(size_t i = 0; i < height; i++) {
        for(size_t j = 0; j < width; j++) {
            printf("%03u ", m[i][j]);
        }
        printf("\n");
    }
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

int create_lbp_pattern(size_t width, size_t height, unsigned char **new, 
                        unsigned char **original) {

    // Fazer TODAS as iteracoes
    // E preparar a matriz
    // Verifica se eh menor que 3 ou NULO
    
    // Casos de ERRO (impossivel iterar)
    if ((width < 3) || (height < 3) || (original == NULL) || (new == NULL))
        return EXIT_FAILURE;

    // Iterar sobre TODA a MATRIZ (1..n-1)(1..n-1)
    for(size_t i = 1; i <= (height - 2); i++) {
        for(size_t j = 1; j <= (width - 2); j++)
            new[i][j] = __local_binnary_pattern((j - 1), (i - 1), original);
    }

    return EXIT_SUCCESS;
}

int print_options_error() {
    printf( "\nOpção inválida\n"
            "\t-i archive.pgm\tarchive name to make LBP\n");
    return EXIT_FAILURE;
}

int main (int argc, char *argv[]) {

    FILE *new;

    // Arquivos de ENTRADA
    FILE *original;
    char typeP[5];
    char *originalPath;

    unsigned char **result, **old;
    size_t width, height;
    short unsigned int max;

    char option;

    // Verifica o tipo de arquivo
    // -i input
   
    // Verifica opcoes de entrada
    if (argc == 1) return print_options_error(); // Sem entradas
    while ((option = getopt(argc, argv, "i:")) != -1) {
        switch (option) {
            case 'i': // Tipo input
                originalPath = strdup(optarg);
                break;
            default: // Entradas erradas
                return print_options_error();
        }
    }

    original = fopen(originalPath, "r");
    new = fopen("outputs/teste.pgm", "w+");

    // Erro ao abrir arquivo ORIGEM
    if(original == NULL) {
        perror("Erro ao abrir arquivo PGM");
        return EXIT_FAILURE;
    }

    // Erro ao criar arquivo DESTINO
    if(new == NULL) {
        perror("Erro ao criar arquivo LBP");
        return EXIT_FAILURE;
    }

    fscanf(original, "%10s", typeP);
    fscanf(original, "%lu %lu %hu", &width, &height, &max);

    printf("Type: %s - %lu,%lu - max:(%hu)\n", typeP, width, height, max);

    // Criar matrizes
    old = create_matrix_pgm(width, height, original);
    result = create_matrix_lbp(width, height);
    
    // print_matrix(width, height, old); 

    create_lbp_pattern(width, height, result, old);

    create_pgm_image(width, height, 255, result, new);

    fclose(original);
    fclose(new);


    // Limpar matrizes
    for (size_t i = 0; i < height; i++) {
        free(result[i]);
        free(old[i]);
    }

    free(old);
    free(result);
    free(originalPath);







    // -i input
    // -d directory base com as imagens

    // Deve aceitar PGM ASCII e BINARIO
    // FORMATO P2 E P5
    
    // Entry ./lbp -d ./base -i img1.tif
    // Exit: <img mais similar> <distance>

    // <img> nome do arquivo com a extensao
    // distance => %6.lf

    // IMAGEM LBP => imagem.ext => imagem.lbp
    // Arquivo binario

    // Caso 2.
    // ./lbp -i img1.tif -o img_out.tif
    // Gera a imagem LBP com o nome informado
    // SEM SAIDAS
    // Erros => nao criar a imagem

    return EXIT_SUCCESS;
}
