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
        free(compDir);
        return 1;
    }

    original = fopen(originalPath, "r");

    // Erro ao abrir arquivo ORIGEM
    if(original == NULL) {
        printf("Não foi possível abrir arquivo de entrada (%s)\n", originalPath);
        perror("Erro");
        free(originalPath);
        free(outputPath);
        free(compDir);
        return EXIT_FAILURE;
    }

    switch(mode) {
    
        // Modo de CRIACAO DE IMAGEM LBP
        // APENAS GERA A SAIDA
        case 1: {
            FILE *lbpOutput = fopen(outputPath, "w");
            unsigned char maxPixel;

            // Criar matriz base para conversoes
            old = pgm_image_to_matrix(original, &width, &height);

            if(lbpOutput == NULL) { // Erro ao criar arquivo DESTINO
                printf("Não foi possível criar arquivo de saida (%s)\n", 
                        outputPath);
                perror("Erro");
                destroy_matrix(old, height);
                fclose(original);
                free(originalPath);
                free(outputPath);
                free(compDir);
                return EXIT_FAILURE;
            }

            if(old == NULL) { // Erro ao criar imagem
                fclose(lbpOutput);
                fclose(original);
                free(originalPath);
                free(outputPath);
                free(compDir);

                destroy_matrix(old, height);
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
            char *lbpArchive, *lbpArchiveComp, *compArchive, *mostNear = NULL;
            struct dirent *dir;
            double temp, mostNearValue = (-1.0);
            unsigned char maxPixel, **compMatrix;
            FILE *a, *b, *originalComp;
            unsigned int *v1, *v2; // Vetores de comparacao

            // Ler arquivos do diretorio
            DIR *d = opendir(compDir);
            if (d == NULL) { 
                perror("Erro ao abrir diretorio");

                destroy_matrix(old, height);
                fclose(original);
                free(originalPath);
                free(outputPath);
                free(compDir);
                free(d);
                return 1; 
            } // Fazer frees aqui

            // Preparar nome do arquivo de origem (A SER COMPARADO)
            lbpArchive = concat_pgm(originalPath);
            // Verificar se existe o arquivo atual LBP
            if (verify_histogram_archive(originalPath)) {
                printf("Falhou?");

                // Criar matriz base para conversoes
                old = pgm_image_to_matrix(original, &width, &height);

                result = create_lbp_matrix(width, height, &maxPixel, result, old);
                create_histogram_archive(width, height, result, lbpArchive);

                destroy_matrix(result, height);
            }
            // Arquivo de origem
            a = fopen(lbpArchive, "r");
            v1 = histogram_file_to_vector(a);

            while((dir = readdir(d)) != NULL) {
                if (dir->d_type == DT_REG) {                    
                    // Se o arquivo for .lbp vai pra proxima
                    if ((strstr(dir->d_name, ".lbp")) != NULL) continue;

                    compArchive = prepare_location_image(compDir, dir->d_name);

                    // Preparar nome do arquivo de origem
                    lbpArchiveComp = concat_pgm(compArchive);

                    // Verificar se estive o LBP de COMPARACAO
                    if (verify_histogram_archive(compArchive)) {

                        originalComp = fopen(compArchive, "r");
                        if (originalComp == NULL) {
                            destroy_matrix(old, height);
                            fclose(original);
                            free(originalPath);
                            free(outputPath);
                            free(compDir);
                            free(d);
                            return 1;
                        }

                        compMatrix = pgm_image_to_matrix(originalComp, &width, &height);

                        result = create_lbp_matrix(width, height, &maxPixel, result, compMatrix);
                        create_histogram_archive(width, height, result, lbpArchiveComp);

                        destroy_matrix(result, height);
                        destroy_matrix(compMatrix, height);
                        fclose(originalComp);
                    }

                    // Arquivo de comparacao
                    b = fopen(lbpArchiveComp, "r");
                    v2 = histogram_file_to_vector(b);

                    temp = euclidian_distance(v1, v2);
                    if ((mostNearValue < 0) || (temp < mostNearValue)) {
                        mostNearValue = temp;
                        free(mostNear);
                        mostNear = strdup(dir->d_name);
                    }

                    free(v2);
                    free(lbpArchiveComp);
                    free(compArchive);
                    fclose(b);
                }
            }

            printf("Imagem mais similar: %s %.06lf\n", mostNear, mostNearValue);

            free(d);
            free(v1);
            free(lbpArchive);
            free(mostNear);
            fclose(a);

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