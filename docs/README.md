<!-- HEADER -->
<p align="center">
  <img alt="Image in picture" src="https://raw.githubusercontent.com/tabler/tabler-icons/8d4f23166d708b42bacc5ce4bc73d72ba296057b/icons/outline/image-in-picture.svg" height="120">
  <h3 align="center">LBP Image Comparison</h3>
  <p align="center">Algoritmo de geração imagem e comparação de PGM usando LBP</p>
</p>
<!-- HEADER -->

## Sobre

O projeto **LBP IMAGE COMPARISON** é um software feito na linguagem `Clang`, proposto para comparações entre um banco de dados PGM (P2 ou P5) e uma outra imagem PGM. Além de possibilitar também apenas a criação de uma imagem LBP utilizando o tratamento por LBP (Local Binary Pattern).

## Funcionalidades

### Modo 01 (criação de imagem por LBP)

* Com base numa imagem PGM original, o algoritmo cria um segundo arquivo PGM ao tratar o arquivo original utilizando LBP
* **Entrada**: imagem.pgm base
* **Saída (STDIN)**: nenhuma
* **Saída**: criação de um arquivo output.pgm com nome especificado

```bash
./LBP -i original.pgm -o output.pgm
```

<!--
## Licença
Licenciado sob a licença XXX. Veja o arquivo `LICENSE` para mais detalhes.
-->

<br />

<p align="center">Criado com 💙 por <a href="https://github.com/tuildes">tuildes</a></p>
