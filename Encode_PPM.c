typedef struct Pixels {
   unsigned char r, g, b;
} Pixel;

typedef struct Imagens {
  int largura, altura;
  Pixel *valores;
} Imagem;

typedef enum codificar {
  R = 0,
  G = 1,
  B = 2,
} Codificar;

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
  fwrite(img_ppm->valores, 3 * img_ppm->largura, img_ppm->altura, copia_ppm);
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

    //iniciando a codificaçao
    int codificados = 0, para_codificar = (tamanho_mensagem - 1), temporario;
    int contador_r = 0, contador_g = 0, contador_b = 0, i; //explicar depois
    Codificar codifique_proximo = 0;
    while(codificados < para_codificar){
      if ( (temporario = fgetc(mensagem)) != EOF ){
        int* mensagem_binaria = (int *)calloc(8, sizeof(int));
        int* pixel_binario = (int *)calloc(8, sizeof(int));
        mensagem_binaria = get_binario_char(temporario);
        for(i = 0; i < 8; i++){
          if(codifique_proximo == R){
            //pegando valor binario do pixel
            pixel_binario = get_binario_char(img->valores[contador_r].r);
            if( !(pixel_binario[0] == mensagem_binaria[0]) ){
              pixel_binario[0] = mensagem_binaria[0];
            }
            //atribuindo o novo valor a imagem
            img->valores[contador_r].r = get_decimal_binario(pixel_binario);
            //aumentando os contadores
            contador_r++;
            codifique_proximo = G;
          } else if(codifique_proximo == G){
            //pegando valor binario do pixel
            pixel_binario = get_binario_char(img->valores[contador_g].g);
            if( !(pixel_binario[0] == mensagem_binaria[0]) ){
              pixel_binario[0] = mensagem_binaria[0];
            }
            //atribuindo o novo valor a imagem
            img->valores[contador_g].g = get_decimal_binario(pixel_binario);
            //aumentando os contadores
            contador_g++;
            codifique_proximo = B;
          } else if(codifique_proximo == B){
            //pegando valor binario do pixel
            pixel_binario = get_binario_char(img->valores[contador_b].b);
            if( !(pixel_binario[0] == mensagem_binaria[0]) ){
              pixel_binario[0] = mensagem_binaria[0];
            }
            //atribuindo o novo valor a imagem
            img->valores[contador_b].b = get_decimal_binario(pixel_binario);
            //aumentando os contadores
            contador_b++;
            codifique_proximo = R;
          }
        }
        codificados++;
      }
    }
  } else {
    printf("ERRO -> A mensagem e maior que a imagem.\n");
    exit(1);
  }
  copiar_imagem_codificada(img);
}

void ler_imagem_ppm(FILE *imagem, FILE *mensagem, Imagem *img){
  //checando se a imagem possui em seu cabeçalho o formato p6.
  char header[16];
  fgets(header, sizeof(header), imagem);
  if( !(header[0] == 'P' && header[1] == '6') ){
    printf("ERRO -> Imagem fornecida nao possui formato P6. \n");
    exit(1); //usamos exit(1) quando é uma saída por erro
  }
  //alocando a memória no struct
  img = malloc(sizeof(Imagem));
  if (!img) {
      printf("ERRO -> Nao foi possivel alocar a memoria no struct Imagem.\n");
      exit(1);
  }
  /*
  alguns arquivos ppm contém comentários, seja para especificar o criador ou atribuir direitos autorais.
  isso irá prejudicar quando formos codificar as mensagens na imagem, então é necessário retira-los
  cada # marca o inicio de uma linha de comentários. o programa deve percorrer toda essa linha até encontrar o \n.
  */
  int comentarios = getc(imagem);
  while (comentarios == '#'){
     while( (comentarios = getc(imagem)) != '\n') ;
  }

  /*pegando tamanho da imagem pelo cabeçalho. segundo a documentação, a parte responsável por mostrar o tamanho será um número, espaço em branco
  seguido de outro número */
  fscanf(imagem, "%u %u", &img->largura, &img->altura);

  //é necessário que a imagem fornecida possua densidade igual à 255, que equivalem à oito bits, para a escala de cores que vamos utilizar
  int densidade_rgb;
  fscanf(imagem, "%d", &densidade_rgb);
  if( densidade_rgb != 255 ){
    printf("ERRO -> Densidade do componente RGB deve ser 255. Seu arquivo possui: %d\n", densidade_rgb);
    exit(1);
  }

  //após ter removido os comentários e pego os dados do componente rgb, o programa precisa quebrar a linha para finalmente chegar nos pixels
  while (fgetc(imagem) != '\n');

  //iniciando a alocação dinâmica para os pixels. lembrando que um pixel são 3 bytes.
  img->valores = malloc(img->largura * img->altura * sizeof(Pixel));
  if (!img->valores){
    printf("ERRO -> Nao foi possivel alocar a memoria para os pixels.\n");
    exit(1);
  }

  /*lendo os pixels do arquivo. primeiro parâmetro indica que a leitura será armazenada em img->valores, o struct criado para os pixels, */
  //daqui pra baixo tá errado
    fread(img->valores, 3 * img->largura, img->altura, imagem);
  //daqui pra cima tá errado

  codificar_mensagem(mensagem, img);
}

int Encode_PPM(char *argv_input,char *argv_imagem){
  FILE *imagem_original, *mensagem_input;
	imagem_original = fopen(argv_imagem, "rb");
  mensagem_input = fopen(argv_input, "rb");
  Imagem *img;
	if( imagem_original == NULL || mensagem_input == NULL ){
		printf("Erro na abertura dos arquivos. Verifique o nome, se eles existem ou se tem algum conteúdo salvo. Depois disso, tente novamente.\n");
	} else {
		ler_imagem_ppm(imagem_original, mensagem_input, img);
	}
	fclose(imagem_original);
	return 0;
}
