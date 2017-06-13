void decodificar_imagem(Imagem *img, char *argv_output){
  FILE *output;
  int* mensagem_binaria;
  int* temporario_cores;
  int i = 0, temporario_decimal = 0, cont_r = 0, cont_g = 0, cont_b = 0;
  Codificar decodifique_proximo = 0;
  if ( strcmp(argv_output, "-s") != 0) {
    output =  fopen(argv_output, "w+"); //caso o usuário tenha decidido por salvar a mensagem decodificada em um arquivo, é necessário criá-lo
  } else {
    printf("Holy moly, Marjory vai ficar orgulhosa! Descobrimos a mensagem secreta:\n");
  }
  /* tendo em vista que na hora de codificar eu fiz com que cada r, g e b recebessem os dados da forma mais igualitária possível,
    é necessário usar uma lógica similar à da codificação para ler os dados.*/
  while(temporario_decimal != 3){ //por quê 3? 3 é o decimal para End of Text
    temporario_cores = (int *)calloc(8, sizeof(int));
    for(i = 0; i < 8; i++){
      mensagem_binaria = (int *)calloc(8, sizeof(int));
      if(decodifique_proximo == R){
        mensagem_binaria = get_binario_char(img->valores[cont_r].r);
        temporario_cores[i] = mensagem_binaria[0];
        decodifique_proximo = G;
        cont_r++;
      } else if(decodifique_proximo == G){
        mensagem_binaria = get_binario_char(img->valores[cont_g].g);
        temporario_cores[i] = mensagem_binaria[0];
        decodifique_proximo = B;
        cont_g++;
      } else {
        mensagem_binaria = get_binario_char(img->valores[cont_b].b);
        temporario_cores[i] = mensagem_binaria[0];
        decodifique_proximo = R;
        cont_b++;
      }
      free(mensagem_binaria);
    }
    //caso o valor encontrado na leitura dos bits menos significativos for diferente do End of Text (em decimal é 3), toma as decisões de ouput
    if( (temporario_decimal = get_decimal_binario(temporario_cores)) != 3 ){
      if( strcmp(argv_output, "-s") == 0 ){
        //caso o usuário tenha escolhido ver a mensagem decodificada no prompt, imprime ela
        printf("%c", temporario_decimal);
      } else{
        //caso tenha escolhido salvá-la em um arquivo, escreve o valor encontrado
        fputc(temporario_decimal, output);
      }
    }
    free(temporario_cores);
  }
  if ( strcmp(argv_output, "-s") != 0){
    printf("Holy moly, Marjory vai ficar orgulhosa! Decodificamos a mensagem, verifique o arquivo %s e descubra.\n", argv_output);
    fclose(output);
  }
}

int Decode_PPM(char *argv_imagem,char *argv_output){
  FILE *imagem_original;
	imagem_original = fopen(argv_imagem, "rb");
  Imagem *img;
	if( imagem_original == NULL ){
		printf("Erro na abertura da imagem PPM original. Verifique o nome, se ela existe ou se tem algum conteúdo salvo. Depois disso, tente novamente.\n");
	} else {
		img = ler_imagem_ppm(imagem_original, img);
    decodificar_imagem(img, argv_output);
	}
	fclose(imagem_original);
  free(img);
	return 0;
}
