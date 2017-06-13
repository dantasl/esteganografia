Imagem* ler_imagem_bmp(FILE *imagem, Imagem *img){
  int i = 0;
  img = malloc(sizeof(Imagem));
  if (!img) {
      printf("ERRO -> Nao foi possivel alocar a memoria no struct Imagem.\n");
      exit(1);
  }
  //lendo as informações do cabeçalho da imagem bmp
  fseek(imagem, 18, SEEK_SET);	//pela documentação do bmp, a posição que armazena a largura do arquivo é a 19
	fread(&img->largura, sizeof(int), 1, imagem);	//armazenando a largura no struct da imagem
	fread(&img->altura, sizeof(int), 1, imagem);	//armazenando a altura no struct da imagem
	printf("A imagem possui o tamanho de %d x %d \n", img->largura, img->altura);
	rewind(imagem);	//retorna o ponteiro para o início da imagem */ exit(1);

  char header[54]; //cabeçalho da imagem bmp possui 54 bytes
  for(i = 0; i < 54; i++){
    img->header[i] = fgetc(imagem);
  }

  img->valores = malloc(img->largura * img->altura * sizeof(Pixel));
  if (!img->valores){
    printf("ERRO -> Nao foi possivel alocar a memoria para os pixels.\n");
    exit(1);
  }

  //depois de ter percorrido os valores do cabeçalho, os demais valores são os pixels que serão armazenados no struct
  fread(img->valores, 3 * img->largura, img->altura, imagem);

  return img;
}
