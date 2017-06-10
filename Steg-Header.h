//bibliotecas necessárias para a execução do programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//typedefs do projeto
typedef struct Pixels {
   unsigned char r, g, b;
} Pixel;

typedef struct Imagens {
  int largura, altura;
  Pixel *valores;
} Imagem;

typedef enum codificar {
  R = 0,
  G = 1,
  B = 2,
} Codificar;

//arquivos do projeto
#include "Read_PPM.c"
#include "Encode_PPM.c"
#include "Encode_BMP.c"
#include "Decode_PPM.c"
#include "Decode_BMP.c"

//utilizada para descobrir o tamanho (em bytes) de imagens ou arquivos .txt
int tamanho_arquivo( FILE *arquivo );

//atualmente lê, verifica o cabeçalho, se existem comentários, a densidade do rgb e armazena os dados certos em structs
Imagem* ler_imagem_ppm( FILE *imagem, Imagem *img );

//reescreve uma imagem a partir dos dados armazenados em um struct
void copiar_imagem_codificada( Imagem *img_ppm );

//recebe os parametros necessários para codificar a mensagem na imagem
void codificar_mensagem( FILE *mensagem, Imagem *img );

//recebe um valor (decimal) e converte para binário
int* get_binario_char( int temporario );

//recebe um valor (binário) e converte para decimal
int get_decimal_binario( int* mensagem_binaria );

//ler a imagem a ser decodificada em ppm, com padrões diferente da função ler_imagem_ppm
void ler_imagem_decodificar_ppm( FILE *imagem, Imagem *img );

//decodifica a mensagem, armazenando-a em um arquivo de texto ou exibindo na tela
void decodificar_imagem( Imagem *img );
