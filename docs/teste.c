#include <stdio.h>
#include <stdlib.h>

int size_of_image(FILE *fp1);

int size_of_image(FILE *fp1)
{
	int width, height;

	fseek(fp1, 0x12, SEEK_SET);	//Seek to the Width position 0x12 (hexadecimal) equivale à 18 (em decimal) e a largura no bmp começa at byte 19
	fread(&width, sizeof(int), 1, fp1);	//Reading Width
	fread(&height, sizeof(int), 1, fp1);	//Read height
	printf("Dimensions of the Image is %d x %d \n", width, height);
	rewind(fp1);	//Seek to the start position

	return ((width * height * 3) / 8);
}

int main(int argc, char const *argv[]) {
  FILE *arquivo; int i;
  arquivo = fopen("teste.bmp", "rb");
  if(arquivo == NULL){
    printf("Falha ao abrir arquivo.\n");
    exit(1);
  }

  int tamanho = size_of_image(arquivo);
  printf("%d\n", tamanho);

  char header[54]; //cabeçalho da imagem bmp possui 54 bytes
  for(i = 0; i < 54; i++){
    header[i] = fgetc(arquivo);
    //printf("%x\n", header[i]);
  }
  fclose(arquivo);
  return 0;
}
