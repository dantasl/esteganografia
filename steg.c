#include "steg-header.h"
int main(int argc, char const *argv[]) {

  //verificando se os argumentos passados pelo usuário são válidos
  if (strcmp(argv[1], "-e") == 0){
    printf("encode \n");
  } else if(strcmp(argv[1], "-d") == 0){
    printf("decode \n");
  } else {
    printf("error\n");
  }
  /*
  FILE *imagem_original = fopen("imgs/imd-testing.ppm", "rb");
  FILE *imagem_copia = fopen("imgs/imd-copia.ppm", "ab+");
  unsigned char ch;
  int c, i, tamanho;
  i = 0;
  if( imagem_original == NULL ) {
    printf( "Erro na abertura do arquivo!\n" );
  } else {
    tamanho = tamanho_arquivo(imagem_original);
    printf("O tamanho do arquivo e: %d bytes.\n", tamanho);
    int *vet = calloc(tamanho, sizeof *vet);
    do {
      fscanf(imagem_original, "%c", &ch);
      if( feof(imagem_original) )
      {
         break ;
      }
      vet[i] = ch;
      printf("%d ", vet[i]);
      fprintf(imagem_copia, "%c", vet[i]);
      i++;
    } while(1);
    //printf("%c\n", vet[90]);
    free(vet);
  }
  fclose(imagem_original);
  fclose(imagem_copia);*/
  return 0;
}

int tamanho_arquivo(FILE *arquivo){
  fseek(arquivo, 0, SEEK_END);
  int tamanho = ftell(arquivo);
  rewind(arquivo);
  return tamanho;
}
