<!-- HEADER -->
<p align="center">
  <img alt="Image in picture" src="https://raw.githubusercontent.com/tabler/tabler-icons/8d4f23166d708b42bacc5ce4bc73d72ba296057b/icons/outline/image-in-picture.svg" height="120">
  <h3 align="center">LBP Image Comparison</h3>
  <p align="center">Algoritmo de geração imagem e comparação de PGM usando LBP</p>
</p>
<!-- HEADER -->

## Sobre

O projeto **LBP IMAGE COMPARISON** é um software feito na linguagem `Clang`, proposto para comparações entre um banco de dados PGM (P2 ou P5) e uma outra imagem PGM. Além de possibilitar também apenas a criação de uma imagem LBP utilizando o tratamento por LBP (Local Binary Pattern).

## Sobre a entrega

* Feito por Gustavo Benitez Frehse
* GRR20235087
* Informática Biomédica

## Funcionalidades

### Modo 01 (criação de imagem por LBP)

* Com base numa imagem PGM original, o algoritmo cria um segundo arquivo PGM ao tratar o arquivo original utilizando LBP
* **Entrada**: imagem.pgm base
* **Saída (STDIN)**: nenhuma
* **Saída**: criação de um arquivo output.pgm com nome especificado

```bash
./LBP -i original.pgm -o output.pgm
```

### Modo 02 (comparação de imagens)

* Compara uma imagem entrada com todas as imagens PGM dentro e retorna a mais parecida
* **Entrada**: imagem.pgm e diretorio/
* **Saida (STDIN)**: imgNear.pgm 134.670000

```bash
./LBP -i original.pgm -d images/
```

## Compilação e execução
```bash
# Na raiz (compilar)
makefile

# Rodar software
./LBP
```

## 🚀 Arquivos
    
    src/            // Pasta da SOURCE e códigos do projeto
    ├── auxiliar.c    // Funções auxiliares do projeto
    ├── auxiliar.h    // Assinaturas das funções auxiliares
    ├── lbp.c         // Funções de manipulação de PGM e LBP
    ├── lbp.h         // Assinaturas das funções PGM e LBP
    └── main.c        // Corpo do software + main()
    makefile        // Arquivo MAKEFILE que gera o executável
    README.md       // Este README com a descrição do projeto 


**OBS**: Mais documentações e usos nas assinaturas das funções

### Pasta src/ (detalhado)

Pasta com todos os arquivos fontes: C e H

### src/auxiliar.c & src/auxiliar.h

Funções auxiliares do projeto de funções mais genpericas:
* Calculo de distancia euclediana: euclidian_distance
* Mostrar o manual de opções: options_manual
* Destruir uma matrix: destroy_matrix
* Preparar local (concatenar dir + arquivo): prepare_location_image

### src/lbp.c & src/lbp.h

Funções de manipulação de imagens PGM e arquivos LBP
* Criar matriz com base em uma imagem PGM: pgm_image_to_matrix
* Criar matriz LBP com base numa matriz: create_lbp_matrix
* Criar arquivo PGM utilizando matriz LBP: create_pgm_image
* Criar arquivo histograma LBP: create_histogram_archive
* Verificar existencia de histrograma: verify_histogram_archive
* Transformar histograma em um vetor: histogram_file_to_vector
* Concatenar string + .lbp: concat_pgm

### src/main.c

Software propriamento dito que trata erros e escolhe dois modos de processamento descritos acima
Além de chamar diversas das funções descritas acima e tratar diretórios.

### Arquiivo makefile

Arquivo base para faciltiar compilação e padronização

### README.md

Contém informações do projeto, tutorial e uma pequena documentação

<!--
## Licença
Licenciado sob a licença XXX. Veja o arquivo `LICENSE` para mais detalhes.
-->

##

<br />

<p align="center">Criado com 💙 por <a href="https://github.com/tuildes">tuildes</a></p>
