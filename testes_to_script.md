# SUCESSO (RETURN 0) and no-leak
[ ] ./LBP -i archive.pgm -o result.pgm
[ ] ./LBP -i archive.pgm -d inputs/
[ ] ./LBP -o result.pgm -i archive.pgm
[ ] ./LBP -d inputs/ -i archive.pgm
[ ] ./LBP -i archive55Comentarys.pgm -o archive.pgm
[ ] ./LBP -i archive.pgm -o archive.pgm

# ERROS (RETURN != 0)
## ERROS (RETURN != 0) ENTRADAS INVALIDAS
[ ] ./LBP
[ ] ./LBP -i archive.pgm
[ ] ./LBP -i archive.tiff
[ ] ./LBP -d inputs/
[ ] ./LBP -d inputs.png
[ ] ./LBP -o archive.pgm
[ ] ./LBP -i -o
[ ] ./LBP -i -d
[ ] ./LBP -d inputs/ -o archive.pgm
[ ] ./LBP -i archive.pgm -d archive.pgm

## ERROS (ARQUIVOS CORROMPIDOS OU ERRADOS)
[ ] ./LBP -i corrupted.pgm -o archive.pgm 
[ ] ./LBP -i dir/ -o archive.pgm
[ ] ./LBP -i image4px.pgm -o archive.pgm
[ ] ./LBP -i blank.pgm -o archive.pgm

_mesmos testes de cima mas para -d"

[ ] ./LBP -i archive.pgm -d dirBlank/
[ ] ./LBP -i archive.pgm -d onlyLBP/
[ ] ./LBP -i 
