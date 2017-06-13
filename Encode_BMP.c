void copiar_arquivo_codificado_bmp(Imagem *img_bmp){
  int i = 0;
  FILE *copia_bmp;
  copia_bmp = fopen("copias/teste-copia.bmp", "ab+");
  for(i = 0; i < 54; i++){
    fputc(img_bmp->header[i], copia_bmp);
  }
  fwrite(img_bmp->valores, 3 * img_bmp->largura, img_bmp->altura, copia_bmp); //escrevendo o valor dos pixels no novo arquivo de imagem
  fclose(copia_bmp);
}

int Encode_BMP(char *argv_input,char *argv_imagem){
  FILE *imagem_original, *mensagem_input;
	imagem_original = fopen(argv_imagem, "rb");
  mensagem_input = fopen(argv_input, "rb");
  Imagem *img;
	if( imagem_original == NULL ){
		printf("Erro na abertura dos arquivos. Verifique o nome, se eles existem ou se tem algum conteúdo salvo. Depois disso, tente novamente.\n");
	} else {
		img = ler_imagem_bmp(imagem_original, img);
    copiar_arquivo_codificado_bmp(img);
    //codificar_mensagem(mensagem_input, img);
	}
	fclose(imagem_original);
	return 0;
}
