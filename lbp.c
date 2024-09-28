// Includes de todo o projeto
#include <stdio.h>
#include <math.h>

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

int main (/* int argc, char *argv[] */) {

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

    return 0;
}
