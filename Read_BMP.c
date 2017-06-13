/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct bmpPixel{  //Estrutura que define os pixeis RGB da imagem
	unsigned char r,g,b, reserved;
}bmpPIXEL;

// primeiro cabecalho
typedef struct Bitmap{
	//Cabecalho do arquivo;
	unsigned char bmp_tipo[2];//Tipo
    unsigned int bmp_tam;//Tamanho total do arquivo dadop em bytes
    unsigned short int bmp_reservado1; // 0
    unsigned short int bmp_reservado2; // 0
    unsigned int bmp_infocab;	// true color = 54
}BITMAP;

// segundo cabecalho
typedef struct BitmapSegundo
{
	unsigned int se_tam;
	unsigned int se_largura;
	unsigned int se_altura;
	unsigned short int se_plano;
	unsigned short int se_qtbits;
	unsigned int se_compressao;
	unsigned int se_tamimg;
	unsigned int se_rehor;
	unsigned int se_revert;
	unsigned int se_ncores;
	unsigned int se_ncoresimport;

}SEGUNDOBMP;


void lerImgBMP(){

	FILE *img, *img_nova;  //Define a criação de dois arquivos

	BITMAP cabe1;
	SEGUNDOBMP	cabe2;

	int i,j;

	img=fopen("linux.bmp", "rb"); //Abre o arquivo a ser lido

	if(img == NULL){
    printf("Nao foi possivel abrir o arquivo\n");
    exit(1);
  }
  // scan do primerio cabecalho
  fread(&cabe1.bmp_tipo, sizeof(cabe1.bmp_tipo), 1,img);
  fread(&cabe1.bmp_tam, sizeof(cabe1.bmp_tam), 1,img);
  fread(&cabe1.bmp_reservado1, sizeof(cabe1.bmp_reservado1), 1,img);
  fread(&cabe1.bmp_reservado2, sizeof(cabe1.bmp_reservado2), 1,img);
	fread(&cabe1.bmp_infocab, sizeof(cabe1.bmp_infocab), 1,img);

	// leitura do 2 cabecalho
	fread(&cabe2.se_tam, sizeof(cabe2.se_tam), 1,img);
  fread(&cabe2.se_largura, sizeof(cabe2.se_largura), 1,img);
  fread(&cabe2.se_altura, sizeof(cabe2.se_altura), 1,img);
  fread(&cabe2.se_plano, sizeof(cabe2.se_plano), 1,img);
	fread(&cabe2.se_qtbits, sizeof(cabe2.se_qtbits), 1,img);
	fread(&cabe2.se_compressao, sizeof(cabe2.se_compressao), 1,img);
  fread(&cabe2.se_tamimg, sizeof(cabe2.se_tamimg), 1,img);
  fread(&cabe2.se_rehor, sizeof(cabe2.se_rehor), 1,img);
  fread(&cabe2.se_revert, sizeof(cabe2.se_revert), 1,img);
	fread(&cabe2.se_ncores, sizeof(cabe2.se_ncores), 1,img);
	fread(&cabe2.se_ncoresimport, sizeof(cabe2.se_ncoresimport), 1,img);

	bmpPIXEL **Matriz;
  Matriz=(bmpPIXEL**)malloc(cabe2.se_altura*sizeof(bmpPIXEL*));
  for(i=cabe2.se_altura;i>0;i--){
      Matriz[i]=(bmpPIXEL*)malloc(cabe2.se_largura*sizeof(bmpPIXEL));
      for(j=0;j<cabe2.se_largura;j++){
          fscanf(img,"%c%c%c%c",&Matriz[i][j].r, &Matriz[i][j].g, &Matriz[i][j].b, &Matriz[i][j].reserved);
       //printf("%c%c%c%c",Matriz[i][j].r, Matriz[i][j].g, Matriz[i][j].b, Matriz[i][j].reserved);
      }
  }
	img_nova=fopen("imd_copia.bmp","wb"); //Abertura do arquivo binário para escrita
	if(img_nova == NULL){
		fprintf(stderr,"Erro na abertura\n");
		exit(1);
	}
	// print do 1 cabecalho no arquivo;
	fwrite(&cabe1.bmp_tipo, sizeof(cabe1.bmp_tipo), 1,img_nova);
  fwrite(&cabe1.bmp_tam, sizeof(cabe1.bmp_tam), 1,img_nova);
  fwrite(&cabe1.bmp_reservado1, sizeof(cabe1.bmp_reservado1), 1,img_nova);
  fwrite(&cabe1.bmp_reservado2, sizeof(cabe1.bmp_reservado2), 1,img_nova);
	fwrite(&cabe1.bmp_infocab, sizeof(cabe1.bmp_infocab), 1,img_nova);
	// print do 2 cabecalho no arquivo
	fwrite(&cabe2.se_tam, sizeof(cabe2.se_tam), 1,img_nova);
  fwrite(&cabe2.se_largura, sizeof(cabe2.se_largura), 1,img_nova);
  fwrite(&cabe2.se_altura, sizeof(cabe2.se_altura), 1,img_nova);
  fwrite(&cabe2.se_plano, sizeof(cabe2.se_plano), 1,img_nova);
	fwrite(&cabe2.se_qtbits, sizeof(cabe2.se_qtbits), 1,img_nova);
	fwrite(&cabe2.se_compressao, sizeof(cabe2.se_compressao), 1,img_nova);
  fwrite(&cabe2.se_tamimg, sizeof(cabe2.se_tamimg), 1,img_nova);
  fwrite(&cabe2.se_rehor, sizeof(cabe2.se_rehor), 1,img_nova);
  fwrite(&cabe2.se_revert, sizeof(cabe2.se_revert), 1,img_nova);
	fwrite(&cabe2.se_ncores, sizeof(cabe2.se_ncores), 1,img_nova);
	fwrite(&cabe2.se_ncoresimport, sizeof(cabe2.se_ncoresimport), 1,img_nova);
	for(i=cabe2.se_altura;i>0;i--){
    	for(j=0;j<cabe2.se_largura;j++){
    		fprintf(img_nova,"%c%c%c%c",Matriz[i][j].r, Matriz[i][j].g, Matriz[i][j].b, Matriz[i][j].reserved);
    	}
  }

	fclose (img_nova);
	fclose(img);
	printf("Imagem BMP criada :D\n");
}


int main(int argc, char const *argv[])
{
	lerImgBMP();
	return 0;
} */
#include <stdio.h>
#include <stdlib.h>

#define IMAGEM "linux.bmp"

//WORD == unsigned short %hu
//DWORD == unsigned long %lu
//LONG == long %li

struct bitmap
{
    //Cabeçalho do arquivo bitmap
    unsigned short bmp_tipo;//Tipo
    unsigned long bmp_tam;//Tamanho total do arquivo
    unsigned short bmp_reservado1;
    unsigned short bmp_reservado2;
    unsigned long bp_infocab;//Número de bytes daqui pra frente para acessar o Info header

    //Informações para leitura do bitmap(Info reader)
    unsigned long leitor_tam;//Tamanho da estrutura
    long bmp_larg;//Largura
    long bmp_alt;//Altura
    unsigned short bmp_planos_cor;//Planos de cor(sempre 1)
    unsigned short bmp_bpp;//Bits por pixel
    unsigned long bmp_compressao;//Tipo de compressão
    unsigned long bmp_tam_img;//Tamanho da imagem em bytes
    long bmp_x_pxl_por_mtr;//Pixels por metro em x
    long bmp_y_pxl_por_mtr;//Pixels por metro em y
    unsigned long bmp_cont_cores;//Número de cores usadas
    unsigned long bmp_cont_coresw;//Número de cores improtantes para o windows

    //Paleta
    unsigned char paleta[256];

    //Dados para montagem da imagem(tamanho variável)
    unsigned* dados;//Alocar memória antes da leitura dos dados
};

struct bitmap* ler_bitmap(FILE*, int*);
void liberar_bitmap(struct bitmap*);

int main(int argc, char* argv[])
{
    int i, t;
    FILE* img;
    struct bitmap* bmp=NULL;

    //Abre arquivo no modo binário
    img = fopen(IMAGEM, "r+b");

    if(img == NULL){
        perror("fopen");
        return 0;
    }

    bmp = ler_bitmap(img, &t);

    if(bmp == NULL){
        printf("Falha ao ler bitmap.\n");
        return 0;
    }

    printf("Bitmap[%s]:\n", IMAGEM);
    printf("=-=-=BITMAP ARQUIVO CABECALHO=-=-=\n");
    printf("Tipo: 0x%x.\n", bmp->bmp_tipo);
    printf("Tamanho total do arquivo: %lu bytes.\n", bmp->bmp_tam);
    printf("Reservado1(?): %d.\n", bmp->bmp_reservado1);
    printf("Reservado2(?): %d.\n", bmp->bmp_reservado2);
    printf("Numero de bytes daqui pra frente para acessar o info reader: %lu.\n", bmp->bp_infocab);

    printf("=-=-=BITMAP INFO CABECALHO=-=-=\n");
    printf("Tamanho da estrutura: %lu bytes.\n", bmp->leitor_tam);
    printf("larguraXaltura: %lix%li.\n", bmp->bmp_larg, bmp->bmp_alt);
    printf("Numero de planos de cor(?): %d.\n", bmp->bmp_planos_cor);
    printf("Bits/Bytes por pixel: %d - %d.\n", bmp->bmp_bpp, bmp->bmp_bpp/8);
    printf("Tipo de compressao(?): %lu.\n", bmp->bmp_compressao);
    printf("Tamanho da imagem: %lu bytes.\n", bmp->bmp_tam_img);
    printf("Numero de pixels por metro em x e y(?): %li - %li.\n", bmp->bmp_x_pxl_por_mtr, bmp->bmp_y_pxl_por_mtr);
    printf("Numero de cores usadas: %lu.\n", bmp->bmp_cont_cores);
    printf("Numero de cores importantes para o Windows: %lu.\n", bmp->bmp_cont_coresw);

    printf("=-=-=PALETA=-=-=\n");
    printf("Paleta:\n");
    for(i=0; i < 257; i++)
        printf("0x%x ", bmp->paleta[i]);
    puts("\n");

    printf("=-=-=DADOS=-=-=\n");
    for(i=0; i < t; i++)
       printf("0x%x ", bmp->dados[i]);

    liberar_bitmap(bmp);

    return 0;
}

struct bitmap* ler_bitmap(FILE* arquivo, int* tdados)
{
    int tcab=sizeof(struct bitmap)-sizeof(void*);
    struct bitmap* bmp = (struct bitmap*)malloc(sizeof(struct bitmap));

    if(bmp == NULL)
        return NULL;

    fread(bmp, tcab, 1, arquivo);//Lendo conteúdo do cabeçalho

    //Quantidade de bytes nos dados
    fseek(arquivo, 0, SEEK_END);
    *tdados = ftell(arquivo) - tcab;

    //Até 4 bytes por pixels(32 bits)
    bmp->dados = (unsigned*)malloc(4*(*tdados));

    if(bmp->dados == NULL)
        return NULL;

    //Posiciona no ponto de leitura
    fseek(arquivo, tcab, SEEK_SET);
    //Ler os dados
    fread(bmp->dados, *tdados, 1, arquivo);

    return bmp;
}

void liberar_bitmap(struct bitmap* bmp)
{
    free(bmp->dados);
    free(bmp);
}
