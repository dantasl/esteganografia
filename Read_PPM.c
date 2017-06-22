Imagem* ler_imagem_ppm(FILE *imagem, Imagem *img){
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

  //após ter pego os dados do componente rgb, o programa precisa quebrar a linha para finalmente chegar nos pixels
  while (fgetc(imagem) != '\n');

  //iniciando a alocação dinâmica para os pixels. lembrando que um pixel possui três cores, cada cor com 1 byte.
  img->valores = malloc(img->largura * img->altura * sizeof(Pixel));
  if (!img->valores){
    printf("ERRO -> Nao foi possivel alocar a memoria para os pixels.\n");
    exit(1);
  }

  /*depois de ter percorrido os valores do cabeçalho e desconsiderado os comentários (caso existam), os demais valores são os pixels
  que serão armazenados no struct */
  fread(img->valores, 3 * img->largura, img->altura, imagem);
  return img;
}