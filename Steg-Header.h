//bibliotecas necessárias para a execução do programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//arquivos do projeto
#include "Encode_PPM.c"
#include "Encode_BMP.c"
#include "Decode_PPM.c"
#include "Decode_BMP.c"

//utilizada para descobrir o tamanho (em bytes) de imagens ou arquivos .txt
int tamanho_arquivo( FILE *arquivo );