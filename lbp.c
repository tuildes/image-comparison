// Includes de todo o projeto
#include <stdio.h>
#include <math.h>

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

/*
int pgm2_to_lbp(FILE *pgm, FILE *lbp, 
                size_t width, size_t height, size_t max) { 

    return EXIT_SUCCESS; 
} */
unsigned char print_local(unsigned char *vector, unsigned char comp) {
    unsigned char res = 0, j = 1;

    for (short int i = 0; i < 8; i++) {
        if (vector[i] > comp) res += j;
        j *= 2;
    }

    return res;
}

int main (/* int argc, char *argv[] */) {

    FILE *original, *new;

    char typeP[10];
    size_t width, height;
    short unsigned int max;

    unsigned char localBinary[8] = {
        1, 1, 1,
        1, 1, // Deveria ter um no meio
        1, 1, 1
    };

    original = fopen("test/imageP2.pgm", "r");
    new = fopen("test/imageP2.lbp.pgm", "w+");

    if(original == NULL) {
        perror("Erro ao abrir arquivo PGM");
        return EXIT_FAILURE;
    }

    if(new == NULL) {
        perror("Erro ao criar arquivo LBP");
        return EXIT_FAILURE;
    }

    fscanf(original, "%10s", typeP);
    fscanf(original, "%lu %lu %hu", &width, &height, &max);

    printf("Type: %s - %lu,%lu - max:(%hu)\n", typeP, width, height, max);

    printf("LSB: %u\n", print_local(localBinary, 0));

    fclose(original);

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
