# Esteganografia (bit menos diferencial) em C
Documentação elaborada para o projeto final das disciplinas de Introdução e Práticas de Técnicas de Programação.  
Escrito por: Lucas Gomes Dantas - (dantaslucas@ufrn.edu.br).

## Formatos de imagem aceitáveis

Antes de iniciar a encodificação/decodificação das suas imagens, certifique-se de que elas possuem o formato PPM ou BMP.
Demais formatos serão recusados pelo algoritmo.

## Compilando o projeto

* Clone este repositório em um local de sua preferência
* Pelo terminal, vá até o diretório do projeto
* Digite **make**

## Parâmetros para execução

**Encodificando uma mensagem:**

Para encodificar uma mensagem, certifique-se de ter fornecido os parâmetros na seguinte ordem:

*./steg -e -i [inputfile] -f [fomato] [imagem]*

* Onde **-e** diz ao programa que ele deve rodar em modo de encodificação;
* **-i** avisa que o próximo parâmetro será um arquivo contendo a mensagem à ser criptografada;
* **[inputfile]** é a mensagem (dê preferência à formatos .txt);
* **-f** avisa que o próximo parâmetro será o formato da imagem;
* **[formato]** deve ser apenas ppm ou bmp,
* **[imagem]** é a imagem que irá armazenar a mensagem criptografada.

Exemplo:

*./steg -e -i mensagem.txt -f ppm imagem.ppm*  
*./steg -e -i segrego.txt -f bmp imagem.bmp*

**Decodificando uma mensagem:**

Para decodificar uma mensagem, certifique-se de ter fornecido os parâmetros na seguinte ordem:

*./steg -d -o [output] -f [formato] [imagem]*

Ou:

*./steg -d -s -f [formato] [imagem]*
