int tamanho_arquivo(FILE *arquivo){
  fseek(arquivo, 0, SEEK_END);
  int tamanho = ftell(arquivo);
  rewind(arquivo);
  return tamanho;
}
//todo -> ler o cabecao e dropar mensagens de erro
void ler_imagem_ppm(FILE *imagem){
	FILE *imagem_copia;
	imagem_copia = fopen("copias/teste-copia.ppm", "ab+");
	unsigned char ch;
	int tamanho = tamanho_arquivo(imagem);
	int *img = calloc(tamanho, sizeof *img); //transformar isso em struct
	int i = 0;
	do {
	    fscanf(imagem, "%c", &ch);
	    if( feof(imagem) ){
	    	break ;
	    }
		img[i] = ch;
		fprintf(imagem_copia, "%c", img[i]);
		i++;
	} while(1);
	free(img);
	fclose(imagem_copia);
}

int Encode_PPM(char *argv_input,char *argv_imagem){
	FILE *imagem_original;
	imagem_original = fopen(argv_imagem, "rb");
	if( imagem_original == NULL ){
		printf("Erro na abertura do arquivo: %s!\n", argv_imagem);
	} else {
		ler_imagem_ppm(imagem_original);		
	}
	fclose(imagem_original);
	return 0;
}