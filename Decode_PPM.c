void decodificar_imagem(Imagem *img){
  int teste = img->valores[0].r;
  int* mensagem_binaria;
  mensagem_binaria = (int *)calloc(8, sizeof(int));
  mensagem_binaria = get_binario_char(teste);
  printf("%d\n", mensagem_binaria[0]);
}

int Decode_PPM(char *argv_imagem,char *argv_output){
  FILE *imagem_original;
	imagem_original = fopen(argv_imagem, "rb");
  Imagem *img;
	if( imagem_original == NULL ){
		printf("Erro na abertura dos arquivos. Verifique o nome, se eles existem ou se tem algum conteúdo salvo. Depois disso, tente novamente.\n");
	} else {
		img = ler_imagem_ppm(imagem_original, img);
    decodificar_imagem(img);
	}
	fclose(imagem_original);
  free(img);
	return 0;
}
