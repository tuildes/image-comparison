#include "lbp.h"
#include "auxiliar.h"

int main (int argc, char *argv[]) {

    // Arquivos de ENTRADA
    FILE *original;
    char *originalPath = NULL, *outputPath = NULL, *compDir = NULL;
    size_t width, height;

    // Matrizes/arquivos de manipulacao
    unsigned char **result = NULL, **old = NULL;
    
    char option; // Opcao das entradas
    unsigned int mode = 0; // Modo de operacao
   
    // Verifica opcoes de entrada
    if (((argc + 1) % 2) || (argc == 1)) { // Numero de entradas errada
        options_manual();
        return 1;
    }

    while ((option = getopt(argc, argv, "i:o:d:")) != -1) {
        switch (option) {
            case 'i': // Tipo input
                originalPath = strdup(optarg);
                break;
            case 'o': // Output
                outputPath = strdup(optarg);
                mode = 1; // Modo de output
                break;
            case 'd':
                compDir = strdup(optarg);
                mode = 2; // Modo de comparacao
                break;
            default: // Entradas erradas
                printf("\n");
                options_manual();
                return 1;
        }
    }

    if (!originalPath) { // Sem input
        options_manual();

        free(originalPath);
        free(outputPath);
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
            unsigned char maxPixel;

            if(lbpOutput == NULL) { // Erro ao criar arquivo DESTINO
                printf("Não foi possível criar arquivo de saida (%s)\n", 
                        outputPath);
                perror("Erro");
                return EXIT_FAILURE;
            }

            // Cria a MATRIZ seguindo o LBP pela imagem OLD
            result = create_lbp_matrix(width, height, &maxPixel, result, old);

            // Cria o arquivo com base na MATRIZ LBP
            create_pgm_image(width, height, maxPixel, result, lbpOutput);

            // Destruir a matrix e fechar arquivo de output
            fclose(lbpOutput);
            destroy_matrix(result, height);
            break;
        }

        case 2: {
            char *lbpArchive, *lbpArchiveComp, *compArchive; // *mostNear;
            // double temp, mostNearValue;
            unsigned char maxPixel, **compMatrix;
            FILE *a, *b, *originalComp;
            unsigned int *v1, *v2;
            int aux;

            compArchive = "inputs/Apuleia1.pgm";

            // Preparar nome do arquivo de origem
            lbpArchive = concat_pgm(originalPath);
            lbpArchiveComp = concat_pgm(compArchive);

            // Ler arquivos do diretorio
            DIR *d = opendir(compDir);

            if (d == NULL) { return 1; } // Fazer frees aqui

            struct dirent *dir;
            while((dir = readdir(d)) != NULL) {
                if (dir->d_type == DT_REG)
                    printf("%s/%s\n", compDir, dir->d_name);
                // Verificar extensoes do arquivo
            }

            free(d);

            // Verificar se existe o arquivo atual LBP
            aux = verify_histogram_archive(originalPath);
            if (aux == 1) {

                result = create_lbp_matrix(width, height, &maxPixel, result, old);
                create_histogram_archive(width, height, result, lbpArchive);

                destroy_matrix(result, height);
            }

            // Verificar se estive o LBP de COMPARACAO
            aux = verify_histogram_archive(compArchive);
            if (aux == 1) {

                originalComp = fopen(compArchive, "r");
                if (originalComp == NULL) {
                    // Fazrr frees aqui
                    return 1;
                }

                compMatrix = pgm_image_to_matrix(originalComp, &width, &height);

                result = create_lbp_matrix(width, height, &maxPixel, result, compMatrix);
                create_histogram_archive(width, height, result, lbpArchiveComp);

                destroy_matrix(result, height);
                destroy_matrix(compMatrix, height);
                fclose(originalComp);
            }

            // Arquivo de origem
            a = fopen(lbpArchive, "r");
            v1 = histogram_file_to_vector(a);

            // Arquivo de comparacao
            b = fopen(lbpArchiveComp, "r");
            v2 = histogram_file_to_vector(b);

            // Finalizacao
            printf("Imagem mais similar: %s, %s %.06lf\n", compArchive, 
                                        lbpArchive, euclidian_distance(v1, v2));

            free(v1);
            free(v2);
            free(lbpArchive);
            free(lbpArchiveComp);
            fclose(a);
            fclose(b);

            break;
        }

        default:
            options_manual();
    }

    destroy_matrix(old, height);
    fclose(original);
    free(originalPath);
    free(outputPath);
    free(compDir);

    return EXIT_SUCCESS;
}