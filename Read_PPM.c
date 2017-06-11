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
  /*
  alguns arquivos ppm contém comentários, seja para especificar o criador ou atribuir direitos autorais.
  isso irá prejudicar quando formos codificar as mensagens na imagem, então é necessário retira-los
  cada # marca o inicio de uma linha de comentários. o programa deve percorrer toda essa linha até encontrar o \n.

  int comentarios = getc(imagem);
  while (comentarios == '#'){
     while( (comentarios = getc(imagem)) != '\n') ;
  } */

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
  return img;
}
