void copiar_arquivo_codificado_bmp(Imagem *img_bmp){
  int i = 0;
  FILE *copia_bmp;
  copia_bmp = fopen("copias/copia.bmp", "ab+");
  for(i = 0; i < 54; i++){
    fputc(img_bmp->header[i], copia_bmp);
  }
  fwrite(img_bmp->valores, 3 * img_bmp->largura, img_bmp->altura, copia_bmp); //escrevendo o valor dos pixels no novo arquivo de imagem
  fclose(copia_bmp);
}

void codificar_mensagem_bmp(FILE *mensagem, Imagem *img){
  int tamanho_mensagem = tamanho_arquivo(mensagem);
  printf("O arquivo de input contendo a mensagem tem %d bytes.\n", tamanho_mensagem);
  printf("A imagem fornecida tem %d bytes.\n", (img->largura * img->altura * 3));
  if( tamanho_mensagem < (img->largura * img->altura * 3) ){
    printf("E possivel armazenar a mensagem na imagem. Prosseguindo...\n");
    int codificados = 0, para_codificar = tamanho_mensagem, temporario;
    int contador_r = 0, contador_g = 0, contador_b = 0, i;
    Codificar codifique_proximo = 0;
    while(codificados < para_codificar){
      if( (temporario = fgetc(mensagem)) == EOF ){ //caso seja o fim do arquivo, atribui temporario com o valor 3, que na tabela ascii equivale à end of text.
        temporario = 3;
        printf("Codificacao realizada com sucesso! Verifique o arquivo de saida armazenado no diretorio /copias.\n");
      }
      int* mensagem_binaria = (int *)calloc(8, sizeof(int));
      mensagem_binaria = get_binario_char(temporario);
      for(i = 0; i < 8; i++){
        int* pixel_binario = (int *)calloc(8, sizeof(int));
        if(codifique_proximo == R){
          //pegando valor binario do pixel
          pixel_binario = get_binario_char(img->valores[contador_r].r);
          if( pixel_binario[7] != mensagem_binaria[i] ){ //verifica se o bit menos significativo do pixel é igual ao i-ésimo bit da mensagem
            pixel_binario[7] = mensagem_binaria[i]; //se não for, troca o valor
          }
          //atribuindo o novo valor a imagem
          img->valores[contador_r].r = get_decimal_binario(pixel_binario);
          //aumentando os contadores
          contador_r++;
          codifique_proximo = G;
        } else if(codifique_proximo == G){
          //pegando valor binario do pixel
          pixel_binario = get_binario_char(img->valores[contador_g].g);
          if( pixel_binario[7] != mensagem_binaria[i] ){ //verifica se o bit menos significativo do pixel é igual ao i-ésimo bit da mensagem
            pixel_binario[7] = mensagem_binaria[i]; //se não for, troca o valor
          }
          //atribuindo o novo valor a imagem
          img->valores[contador_g].g = get_decimal_binario(pixel_binario);
          //aumentando os contadores
          contador_g++;
          codifique_proximo = B;
        } else if(codifique_proximo == B){
          //pegando valor binario do pixel
          pixel_binario = get_binario_char(img->valores[contador_b].b);
          if( pixel_binario[7] != mensagem_binaria[i] ){ //verifica se o bit menos significativo do pixel é igual ao i-ésimo bit da mensagem
            pixel_binario[7] = mensagem_binaria[i]; //se não for, troca o valor
          }
          //atribuindo o novo valor a imagem
          img->valores[contador_b].b = get_decimal_binario(pixel_binario);
          //aumentando os contadores
          contador_b++;
          codifique_proximo = R;
        }
        free(pixel_binario);
      }
      free(mensagem_binaria);
      codificados++;
    }
  } else {
    printf("ERRO -> A mensagem e maior que a imagem.\n");
    exit(1);
  }
  copiar_arquivo_codificado_bmp(img);
}

int Encode_BMP(char *argv_input,char *argv_imagem){
  FILE *imagem_original, *mensagem_input;
	imagem_original = fopen(argv_imagem, "rb");
  mensagem_input = fopen(argv_input, "rb");
  Imagem *img;
	if( imagem_original == NULL || mensagem_input == NULL ){
		printf("Erro na abertura dos arquivos. Verifique o nome, se eles existem ou se tem algum conteúdo salvo. Depois disso, tente novamente.\n");
	} else {
		img = ler_imagem_bmp(imagem_original, img);
    codificar_mensagem_bmp(mensagem_input, img);
	}
	fclose(imagem_original);
  fclose(mensagem_input);
	return 0;
}