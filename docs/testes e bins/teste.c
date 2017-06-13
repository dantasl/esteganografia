#include <stdio.h>
#include <stdlib.h>

typedef struct Pixels {
   unsigned char r, g, b;
} Pixel;

typedef struct Imagens {
  int largura, altura;
  Pixel *valores;
} Imagem;

Imagem* ler_cabecalho_bmp(FILE *fp1, Imagem *img);
void copiar_arquivo(char header[54], Imagem *img);

Imagem* ler_cabecalho_bmp(FILE *fp1, Imagem *img){
	fseek(fp1, 18, SEEK_SET);	//Seek to the Width position 0x12 (hexadecimal) equivale à 18 (em decimal) e a largura no bmp começa at byte 19
	fread(&img->largura, sizeof(int), 1, fp1);	//Reading Width
	fread(&img->altura, sizeof(int), 1, fp1);	//Read height
	printf("Dimensions of the Image is %d x %d \n", img->largura, img->altura);
	rewind(fp1);	//Seek to the start position
	return (img);
}

void copiar_arquivo(char header[54], Imagem *img){
  int i = 0;
  FILE *copia_bmp;
  copia_bmp = fopen("copias/teste-copia.bmp", "ab+");
  for(i = 0; i < 54; i++){
    fputc(header[i], copia_bmp);
  }
  fwrite(img->valores, 3 * img->largura, img->altura, copia_bmp); //escrevendo o valor dos pixels no novo arquivo de imagem
  fclose(copia_bmp);
}

int main(int argc, char const *argv[]) {
  FILE *arquivo; int i;
  Imagem *img;
  img = malloc(sizeof(Imagem));
  if (!img) {
      printf("ERRO -> Nao foi possivel alocar a memoria no struct Imagem.\n");
      exit(1);
  }
  arquivo = fopen("linux.bmp", "rb");
  if(arquivo == NULL){
    printf("Falha ao abrir arquivo.\n");
    exit(1);
  }

  img = ler_cabecalho_bmp(arquivo, img);
  int tamanho = (img->largura * img->altura * 3);
  printf("%d\n", tamanho);

  char header[54]; //cabeçalho da imagem bmp possui 54 bytes
  for(i = 0; i < 54; i++){
    header[i] = fgetc(arquivo);
    //printf("%x\n", header[i]);
  }

  img->valores = malloc(img->largura * img->altura * sizeof(Pixel));
  if (!img->valores){
    printf("ERRO -> Nao foi possivel alocar a memoria para os pixels.\n");
    exit(1);
  }

  /*depois de ter percorrido os valores do cabeçalho e desconsiderado os comentários (caso existam), os demais valores são os pixels
  que serão armazenados no struct */
  fread(img->valores, 3 * img->largura, img->altura, arquivo);

  copiar_arquivo(header, img);

  free(img);
  fclose(arquivo);
  return 0;
}
