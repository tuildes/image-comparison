#include "auxiliar.h"

int options_manual() {
    printf( "Opção inválida\n"
            "\t-i [<archive>]\tName of original archive (P2 or P5)\n"
            "\t-o [<archive>]\tName of result LBP archive (P5)\n");
    return EXIT_FAILURE;
}

double euclidian_distance(int *v1, int *v2, size_t lenght) {
    double res;
    for (size_t i = 0; i < lenght; i++) {
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