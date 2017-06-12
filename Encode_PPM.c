int tamanho_arquivo(FILE *arquivo){
  fseek(arquivo, 01, SEEK_END); //move o ponteiro do início do arquivo até o final
  int tamanho = ftell(arquivo); //descobre o tamanho da distância percorrida
  rewind(arquivo); //rebobina o ponteiro pro início do arquivo
  return tamanho; //retorna um inteiro contendo o tamanho, em bytes, do arquivo
}

int* get_binario_char(int temporario){
  int i = 0, a = 7;
  int* bin = (int *)calloc(8, sizeof(int)); //calloc é usado porque ele inicia preenchendo todas as posições com zero, malloc preenche com lixo
  while(temporario > 0){
    bin[i] = temporario%2;
    temporario = temporario/2;
    i++;
  }
  return bin;
}

int get_decimal_binario(int* mensagem_binaria){
  int decimal = 0, i;
  for (i = 0; i < 8; i++)
    decimal += mensagem_binaria[i] * pow(2, i);
  return decimal;
}

void copiar_imagem_codificada(Imagem *img_ppm){
  FILE *copia_ppm;
  copia_ppm = fopen("copias/teste-copia.ppm", "ab+");
  fprintf(copia_ppm, "P6\n"); //escrevendo o cabeçalho, que deve ser P6
  fprintf(copia_ppm, "%d %d\n",img_ppm->largura,img_ppm->altura); //escrevendo as dimensões, já lidas da imagem original
  fprintf(copia_ppm, "255\n"); //escrevendo a densidade rgb, que deve ser 255
  fwrite(img_ppm->valores, 3 * img_ppm->largura, img_ppm->altura, copia_ppm); //escrevendo o valor dos pixels no novo arquivo de imagem
  fclose(copia_ppm);
}

void codificar_mensagem(FILE *mensagem, Imagem *img){
  //iniciando as operações com a mensagem de input do usuário. primeiro precisamos pegar o tamanho dela
  int tamanho_mensagem = tamanho_arquivo(mensagem);
  printf("O arquivo de input contendo a mensagem tem %d bytes.\n", tamanho_mensagem);
  printf("A imagem fornecida tem %d bytes.\n", (img->largura * img->altura * 3));

  //verificando se o input fornecido pelo usuário cabe na imagem selecionada
  if( tamanho_mensagem < (img->largura * img->altura * 3) ){
    printf("E possivel armazenar a mensagem na imagem. Prosseguindo...\n");

    /*
    Explicando a codificação:
    Vendo na sala de aula que um grupo de amigos encodificou a mensagem e ela ficou com tons acentuados de verde, percebi que
    é necessário "espalhar" a mensagem de forma mais igualitária possível entre os rgb dos pixels. Para isso eu criei um enum
    que auxilia o processo. Se eu codifiquei a mensagem em um R do pixel, devo fazer a próxima codificação em um G, e por aí vai.
    Dessa forma o programa não sobrecarrega o valor dos rgb e nem os deforma. Os contadores criados servem para auxiliar o programa
    a ter uma noção sobre qual pixel aquele r, g, ou b pertencem.
    */
    int codificados = 0, para_codificar = tamanho_mensagem, temporario;
    int contador_r = 0, contador_g = 0, contador_b = 0, i;
    Codificar codifique_proximo = 0;
    while(codificados < para_codificar){
      if( (temporario = fgetc(mensagem)) == EOF ){ //caso seja o fim do arquivo, atribui temporario com o valor 3, que na tabela ascii equivale à end of text.
        temporario = 3;
      }
      int* mensagem_binaria = (int *)calloc(8, sizeof(int));
      mensagem_binaria = get_binario_char(temporario);
      for(i = 0; i < 8; i++){
        int* pixel_binario = (int *)calloc(8, sizeof(int));
        if(codifique_proximo == R){
          //pegando valor binario do pixel
          pixel_binario = get_binario_char(img->valores[contador_r].r);
          if( pixel_binario[0] != mensagem_binaria[i] ){ //verifica se o bit menos significativo do pixel é igual ao i-ésimo bit da mensagem
            pixel_binario[0] = mensagem_binaria[i]; //se não for, troca o valor
          }
          //atribuindo o novo valor a imagem
          img->valores[contador_r].r = get_decimal_binario(pixel_binario);
          //aumentando os contadores
          contador_r++;
          codifique_proximo = G;
        } else if(codifique_proximo == G){
          //pegando valor binario do pixel
          pixel_binario = get_binario_char(img->valores[contador_g].g);
          if( pixel_binario[0] != mensagem_binaria[i] ){ //verifica se o bit menos significativo do pixel é igual ao i-ésimo bit da mensagem
            pixel_binario[0] = mensagem_binaria[i]; //se não for, troca o valor
          }
          //atribuindo o novo valor a imagem
          img->valores[contador_g].g = get_decimal_binario(pixel_binario);
          //aumentando os contadores
          contador_g++;
          codifique_proximo = B;
        } else if(codifique_proximo == B){
          //pegando valor binario do pixel
          pixel_binario = get_binario_char(img->valores[contador_b].b);
          if( pixel_binario[0] != mensagem_binaria[i] ){ //verifica se o bit menos significativo do pixel é igual ao i-ésimo bit da mensagem
            pixel_binario[0] = mensagem_binaria[i]; //se não for, troca o valor
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
  fclose(mensagem);
  copiar_imagem_codificada(img);
}
int Encode_PPM(char *argv_input,char *argv_imagem){
  FILE *imagem_original, *mensagem_input;
	imagem_original = fopen(argv_imagem, "rb");
  mensagem_input = fopen(argv_input, "rb");
  Imagem *img;
	if( imagem_original == NULL || mensagem_input == NULL ){
		printf("Erro na abertura dos arquivos. Verifique o nome, se eles existem ou se tem algum conteúdo salvo. Depois disso, tente novamente.\n");
	} else {
		img = ler_imagem_ppm(imagem_original, img);
    codificar_mensagem(mensagem_input, img);
	}
	fclose(imagem_original);
	return 0;
}
