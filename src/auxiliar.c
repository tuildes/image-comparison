#include "auxiliar.h"

int options_manual() {
    printf( "\e[0;97mManual of LBP IMAGE COMPARATION\e[0m\n"
            "\t-i [<image.pgm>]\tName of original archive (P2 or P5)\n"
            "\t-d [<directory>]\tDirectory with comparations images (P2 or P5)\n"
            "\t-o [<image.pgm>]\ttName of result LBP archive (P5)\n\n"
            "\e[0;97mExamples of entry:\e[0m\n"
            "\t./LBP -i archive.pgm -d inputs/\n"
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

char* prepare_location_image(char *dir, char *name) {

    char *target = NULL;
    size_t tam = (strlen(dir) + strlen(name) + 3);

    if ((target = (char*)malloc(sizeof(char) * tam)) == NULL) 
        return NULL;

    strcpy(target, dir);
    strcat(target, "/");
    strcat(target, name);

    return target;
}