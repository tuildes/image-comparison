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
#include "lbp.h"
#include "auxiliar.h"

int main (int argc, char *argv[]) {

    // Arquivos de ENTRADA
    FILE *original;
    char *originalPath, *outputPath;
    short unsigned int max;
    size_t width, height;

    // Matrizes/arquivos de manipulacao
    unsigned char **result, **old;
    unsigned char maxNew;
    
    char option; // Opcao das entradas
    unsigned int mode = 0; // Modo de operacao
   
    // Verifica opcoes de entrada
    if ((argc + 1) % 2) { // Numero de entradas errada
        options_manual();
        return 1;
    }

    while ((option = getopt(argc, argv, "i:o:")) != -1) {
        switch (option) {
            case 'i': // Tipo input
                originalPath = strdup(optarg);
                break;
            case 'o': // Output
                outputPath = strdup(optarg);
                mode = 1; // Modo de output
                break;
            case 'd':
                mode = 0; // 2
                break;
            default: // Entradas erradas
                printf("\n");
                options_manual();
                return 1;
        }
    }

    if ((argc + 1) % 2) { // Numero de entradas errada
        options_manual();
        return 1;
    }

    original = fopen(originalPath, "r");

    // Erro ao abrir arquivo ORIGEM
    if(original == NULL) {
        printf("Não foi possível abrir arquivo de entrada (%s)\n", originalPath);
        perror("Erro");
        return EXIT_FAILURE;
    }

    // Criar matrizes
    old = pgm_image_to_matrix(original, &width, &height);

    switch(mode) {
    
        // Modo de CRIACAO DE IMAGEM LBP
        // APENAS GERA A SAIDA
        case 1: {
            FILE *lbpOutput = fopen(outputPath, "w");
            if(lbpOutput == NULL) { // Erro ao criar arquivo DESTINO
                printf("Não foi possível criar arquivo de saida (%s)\n", outputPath);
                perror("Erro");
                return EXIT_FAILURE;
            }

            result = create_matrix_lbp(width, height); 

            // Cria uma MATRIZ LBP
            create_lbp_pattern(width, height, &maxNew, result, old);

            // Cria o arquivo com base na MATRIZ LBP
            create_pgm_image(width, height, maxNew, result, lbpOutput);

            // Destruir a matrix e fechar arquivo de output
            fclose(lbpOutput);
            destroy_matrix(result, height);
            break;
        }
        
        default:
            options_manual();
    }

    // Criar histograma
    // create_histogram_archive(width, height, result, "result.lbp");

    destroy_matrix(old, height);

    fclose(original);
    free(originalPath);
    free(outputPath);

    return EXIT_SUCCESS;
}