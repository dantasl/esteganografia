#include "Steg-Header.h"
int main(int argc, char *argv[]) {
  int i;
  char *argv_imagem, *argv_input, *argv_output;
  //verificando se os argumentos passados pelo usuário são válidos
  if ( (argc == 7)||(argc == 6) ){
    if ( strcmp(argv[1], "-e") == 0 && strcmp(argv[5], "ppm") == 0 ){
      argv_imagem = argv[6];
      argv_input = argv[3];
      Encode_PPM(argv_input, argv_imagem);
    } else if( strcmp(argv[1], "-e") == 0 && strcmp(argv[5], "bmp") == 0 ){
      //encode_bpm();
    } else if( strcmp(argv[1], "-d") == 0 && strcmp(argv[5], "ppm") == 0 ){
      if( strcmp(argv[2], "-s" ) == 0 ){
        argv_imagem = argv[5];
        argv_output = argv[2];
      } else {
        argv_imagem = argv[6];
        argv_output = argv[3];
      }
      Decode_PPM(argv_imagem, argv_output);
    } else if( strcmp(argv[1], "-d") == 0 && strcmp(argv[5], "bmp") == 0 ){
      //decode_bpm();
    } else {
      printf("\nFormato de imagem digitado não suportado.\nDigitado: %s\nEsperado: bmp ou ppm\nDuvidas? Consulte o README.\n\n", argv[5]);
    }
  } else {
    printf("\nERRO -> Parametro(s) informado(s) nao confere(m) com o(s) esperado(s).\n");
    printf("Digitados:\n");
    for(i = 1; i < argc; i++){
      printf(" %s ", argv[i]);
    }
    printf("\nEsperando:\n");
    printf("-e -i <inputfile> -f <format> <image>\nOU\n-d -o <outputfile> -f <format> <image>\nOU\n-d -s -f <format> <image>\n");
    printf("Consulte o arquivo README para mais informacoes e exemplos.\n\n");
  }
  return 0;
}
