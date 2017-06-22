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