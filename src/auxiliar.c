#include "auxiliar.h"

int options_manual() {
    printf( "Opção inválida\n"
            "\t-i [<archive>]\tName of original archive (P2 or P5)\n"
            "\t-o [<archive>]\tName of result LBP archive (P5)\n\n"
            "\t./LBP -i archive.pgm -o result.pgm\n");
    return EXIT_FAILURE;
}

double euclidian_distance(unsigned int *v1, unsigned int *v2) {
    double res = 0;

    for (size_t i = 0; i < 255; i++) {
        res += ((*v1 - *v2) * (*v1 - *v2));
        v1++;
        v2++;
    }

    return sqrt(res);
}

void destroy_matrix(unsigned char **n, size_t l) {
    if (n == NULL) return;
    for (size_t i = 0; i < l; i++) free(n[i]);
    free(n);
}