#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct bmpPixel{  //Estrutura que define os pixeis RGB da imagem
	unsigned char r,g,b, reserved;
}bmpPIXEL;


/*typedef struct tagBITMAPINFO{
	//SEGUNDOBMP bmiHeader;
	PIXEL *bmiColors;
}BITMAPINFO; */

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

/*
	// print no terminal do primeiro cabecalho
	printf("%s\n", cabe1.bmp_tipo );
	printf("%d\n", cabe1.bmp_tam );
	printf("%d\n", cabe1.bmp_reservado1 );
	printf("%d\n", cabe1.bmp_reservado2 );
	printf("%d\n", cabe1.bmp_infocab );

	// print do segundo cabecalho no terminal
	printf("\nSegundo cabecalho\n");
	printf("%d\n", cabe2.se_tam );
	printf("%d\n", cabe2.se_largura );
	printf("%d\n", cabe2.se_altura );
	printf("%d\n", cabe2.se_plano );
	printf("%d\n", cabe2.se_qtbits );
	printf("%d\n", cabe2.se_compressao );
	printf("%d\n", cabe2.se_tamimg );
	printf("%d\n", cabe2.se_rehor );
	printf("%d\n", cabe2.se_revert );
	printf("%d\n", cabe2.se_ncores );
	printf("%d\n", cabe2.se_ncoresimport );
*/
}


int main(int argc, char const *argv[])
{

	//lerImgPPM();
	lerImgBMP();

	return 0;
}
