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

//atualmente lê, verifica o cabeçalho, se existem comentários, a densidade do rgb e armazena os dados certos em structs
void ler_imagem_ppm( FILE *imagem, FILE *mensagem, Imagem *img );

//reescreve uma imagem a partir dos dados armazenados em um struct
void copiar_imagem_codificada( Imagem *img_ppm );

//
static int* converter_mensagem_binario(FILE *mensagem, int *binarios);
