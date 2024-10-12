#include "lbp.h"
#include "auxiliar.h"

int main (int argc, char *argv[]) {

    // Arquivos de ENTRADA
    FILE *original;
    char *originalPath = NULL, // String representando o arquivo de entrada
        *outputPath = NULL, // String represnentando  oarquivo de saida
        *compDir = NULL; // String reprensetnado diretorio de comparacao
    size_t width, height; // Tamanho das imagens (generico)
    unsigned char **result = NULL, **old = NULL; // Matrizes de manipulacao
    
    char option; // Opcao das entradas
    unsigned int mode = 0; // Modo de operacao
   
    // Verifica opcoes de entrada
    if (((argc + 1) % 2) || (argc == 1)) { // Numero de entradas errada
        options_manual();
        return EXIT_FAILURE;
    }

    // Tratar entradas
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
                return EXIT_FAILURE;
        }
    }

    // ERRO: Sem entrada (input) inserida
    if (!originalPath) {
        options_manual();

        free(originalPath);
        free(outputPath);
        free(compDir);
        return EXIT_FAILURE;
    }

    original = fopen(originalPath, "r"); // Abrir arquivo de entrada (input)

    // Erro ao abrir arquivo de entrada (INPUT)
    if(original == NULL) {
        printf("Não foi possível abrir arquivo de entrada (%s)\n", 
                                                    originalPath);
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

            unsigned char maxPixel; // Valor maximo de TOM DE PRETO

            // Criar matriz base para conversoes
            old = pgm_image_to_matrix(original, &width, &height);

            if(old == NULL) { // Erro ao matriz de imagem
                fclose(original);
                free(originalPath);
                free(outputPath);
                free(compDir);

                destroy_matrix(old, height);
                return EXIT_FAILURE; 
            }

            // Abertura de arquivo de saida
            FILE *lbpOutput = fopen(outputPath, "w");
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

            // Cria a MATRIZ seguindo o LBP pela imagem OLD
            result = create_lbp_matrix(width, height, &maxPixel, result, old);
            // Cria o arquivo com base na MATRIZ LBP
            create_pgm_image(width, height, maxPixel, result, lbpOutput);

            // Destruir a matrix e fechar arquivo de output
            fclose(lbpOutput);
            destroy_matrix(result, height);
            destroy_matrix(old, height);
            break;
        }

        case 2: {
            char *originalLBPArchive, // Arquivo LBP original (base)
                *comparisonLBPArchive, // Arquivo LBP de comparacao (dir)
                *comparisonDirLBP, // Diretorio + arquivo LBP para abertura
                *mostNear = NULL;
            struct dirent *dir; // Ponteiro do diretorio de comparacao
            double temp, mostNearValue = (-1.0); // Auxiliar para calculos
            unsigned char maxPixel, // Valor maximo de TOM de PRETO
                        **compMatrix; // Matriz para criacao de vetor LBP
            FILE *a, *b, *comparisonImage;
            unsigned int *v1, *v2; // Vetores de comparacao

            // Ler arquivos do diretorio
            DIR *d = opendir(compDir);
            if (d == NULL) { 
                perror("Erro ao abrir diretorio");

                fclose(original);
                free(originalPath);
                free(outputPath);
                free(compDir);
                free(d);
                return EXIT_FAILURE; 
            } // Fazer frees aqui

            // Preparar nome do arquivo de origem (A SER COMPARADO)
            originalLBPArchive = concat_pgm(originalPath);
            // Verificar se existe o arquivo atual LBP
            if (verify_histogram_archive(originalPath)) {

                // Criar matriz base para conversoes
                old = pgm_image_to_matrix(original, &width, &height);

                // Se em caso de ERRO retorna ERRO
                if (old == NULL) {
                    free(originalLBPArchive);
                    fclose(original);
                    free(originalPath);
                    free(outputPath);
                    free(compDir);
                    free(d);
                    return EXIT_FAILURE;
                }

                // Cria arquivo de HISTOGRAMA BINARIO
                result = create_lbp_matrix(width, height, &maxPixel, 
                                        result, old);
                create_histogram_archive(width, height, result, 
                                        originalLBPArchive);

                // Destruir matrizes auxilaires
                destroy_matrix(result, height);
                destroy_matrix(old, height);
            }
            // Arquivo de origem
            a = fopen(originalLBPArchive, "r");
            v1 = histogram_file_to_vector(a);

            while((dir = readdir(d)) != NULL) {
                if (dir->d_type == DT_REG) {                    
                    // Se o arquivo for .lbp vai pra proxima
                    if ((strstr(dir->d_name, ".lbp")) != NULL) continue;

                    // Prepara o path completo (dir + nome)
                    comparisonDirLBP = prepare_location_image(compDir, 
                                                            dir->d_name);

                    // Preparar nome do arquivo de origem
                    comparisonLBPArchive = concat_pgm(comparisonDirLBP);

                    // Verificar se estive o LBP de COMPARACAO
                    if (verify_histogram_archive(comparisonDirLBP)) {

                        // Abrir arquivo de HISTORGAMA BINARIO
                        comparisonImage = fopen(comparisonDirLBP, "r");
                        if (comparisonImage == NULL) {
                            destroy_matrix(old, height);
                            fclose(original);
                            free(originalPath);
                            free(outputPath);
                            free(compDir);
                            free(d);
                            return EXIT_FAILURE;
                        }

                        // Prepara a matriz base
                        compMatrix = pgm_image_to_matrix(comparisonImage, 
                                                        &width, &height);

                        // Se a matriz der errado (continua)
                        if (compMatrix == NULL) {
                            fclose(comparisonImage);
                            free(comparisonLBPArchive);
                            free(comparisonDirLBP);
                            continue;
                        }

                        // Cria e escreve o arquivo LBP
                        result = create_lbp_matrix(width, height, &maxPixel, 
                                                result, compMatrix);
                        create_histogram_archive(width, height, result, 
                                                comparisonLBPArchive);

                        // Destroi e limpa memoria
                        destroy_matrix(result, height);
                        destroy_matrix(compMatrix, height);
                        fclose(comparisonImage);
                    }

                    // Arquivo de comparacao
                    b = fopen(comparisonLBPArchive, "r");
                    v2 = histogram_file_to_vector(b);

                    // Verifica a distancia das imagens e guarda a mais proxima
                    temp = euclidian_distance(v1, v2);
                    if ((mostNearValue < 0) || (temp < mostNearValue)) {
                        mostNearValue = temp;
                        free(mostNear);
                        mostNear = strdup(dir->d_name);
                    }

                    free(v2);
                    free(comparisonLBPArchive);
                    free(comparisonDirLBP);
                    fclose(b);
                }
            }

            // Se existir, imprime a imagem mais similar
            if (mostNear != NULL)
                printf("Imagem mais similar: %s %.06lf\n", mostNear, 
                                                    mostNearValue);

            free(d);
            free(v1);
            free(originalLBPArchive);
            free(mostNear);
            fclose(a);

            break;
        }

        default:
            options_manual();
    }

    fclose(original);
    free(originalPath);
    free(outputPath);
    free(compDir);

    return EXIT_SUCCESS;
}
