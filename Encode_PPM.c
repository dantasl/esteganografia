int Encode_PPM(char *argv_input,char *argv_imagem){
	FILE *imagem_original, *imagem_copia;
	imagem_original = fopen(argv_imagem, "rb");
	imagem_copia = fopen("imgs/teste-copia.ppm", "ab+");
	if( imagem_original == NULL ){
		printf("Erro na abertura do arquivo: %s!\n", argv_imagem);
	} else {
		unsigned char ch;
		int tamanho = tamanho_arquivo(imagem_original);
		int *imagem = calloc(tamanho, sizeof *imagem); //transformar isso em struct
		int i;
		do {
	    	fscanf(imagem_original, "%c", &ch);
	      	if( feof(imagem_original) ){
	        	break ;
	      	}
		    imagem[i] = ch;
		    fprintf(imagem_copia, "%c", imagem[i]);
		    i++;
	    } while(1);
	    free(imagem);

	}
	fclose(imagem_original);
  	fclose(imagem_copia);
	return 0;
}

int tamanho_arquivo(FILE *arquivo){
  fseek(arquivo, 0, SEEK_END);
  int tamanho = ftell(arquivo);
  rewind(arquivo);
  return tamanho;
}