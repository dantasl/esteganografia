int tamanho_arquivo(FILE *arquivo){
  fseek(arquivo, 0L, SEEK_END);
  int tamanho = ftell(arquivo);
  fseek(arquivo, 0L, SEEK_SET);
  return tamanho;
}
