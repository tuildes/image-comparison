# SUCESSO (RETURN 0) and no-leak
[X] ./LBP -i archive.pgm -o result.pgm
[x] ./LBP -i archive.pgm -d inputs/
[X] ./LBP -o result.pgm -i archive.pgm
[X] ./LBP -d inputs/ -i archive.pgm
[X] ./LBP -i archive55Comentarys.pgm -o archive.pgm
[X] ./LBP -i archive.pgm -o archive.pgm
[X] ./LBP -i p5/p5 -o archive.pgm
[X] ./LBP -i p5/p2 -d dir/onlyP2/onlyP5

# ERROS (RETURN != 0)
## ERROS (RETURN != 0) ENTRADAS INVALIDAS
[X] ./LBP
[X] ./LBP -i archive.pgm
[X] ./LBP -i archive.tiff
[X] ./LBP -d inputs/
[X] ./LBP -d inputs.png
[X] ./LBP -o archive.pgm
[X] ./LBP -i -o
[X] ./LBP -i -d
[X] ./LBP -d inputs/ -o archive.pgm
[X] ./LBP -i archive.pgm -d archive.pgm

## ERROS (ARQUIVOS CORROMPIDOS OU ERRADOS)
[X] ./LBP -i corrupted.pgm -o archive.pgm 
[X] ./LBP -i dir/ -o archive.pgm
[X] ./LBP -i image4px.pgm -o archive.pgm
[X] ./LBP -i blank.pgm -o archive.pgm

_mesmos testes de cima mas para -d"

[X] ./LBP -i archive.pgm -d dirBlank/
[X] ./LBP -i archive.pgm -d onlyLBP/
[X] ./LBP -i corrupted.pgm -d folder/
[X] ;/LBP -i archive.pgm -d onlyNotPGM/

_testes de pastas, mas sem o / e nome sem extensao_

[X] ./LBP -i archive.pgm -d copysAndMoreCopies/
[X] ./LBP -i archive.pgm -d dirCorrupted/
[X] ./LBP -i archive.pgm -d src/

## LBP corrumpidos

[ ] ./LBP -i archive.pgm -d dirLBPCORRUPTED/
[ ] ./LBP -i corrupted.lbp -d dir/

