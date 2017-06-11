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

### Encodificando uma mensagem

Para encodificar uma mensagem, certifique-se de ter fornecido os parâmetros na seguinte ordem:

*./steg -e -i [inputfile] -f [fomato] [imagem]*

* Onde **-e** diz ao programa que ele deve rodar em modo de encodificação;
* **-i** avisa que o próximo parâmetro será um arquivo contendo a mensagem à ser criptografada;
* **[inputfile]** é a mensagem (dê preferência à formatos .txt);
* **-f** avisa que o próximo parâmetro será o formato da imagem;
* **[formato]** deve ser apenas ppm ou bmp;
* **[imagem]** é a imagem que irá armazenar a mensagem criptografada.

**Exemplo:**

*./steg -e -i mensagem.txt -f ppm imagem.ppm*  
*./steg -e -i segrego.txt -f bmp imagem.bmp*

### Decodificando uma mensagem

Para decodificar uma mensagem, certifique-se de ter fornecido os parâmetros na seguinte ordem:

*./steg -d -o [output] -f [formato] [imagem]*

Ou:

*./steg -d -s -f [formato] [imagem]*

* Onde **-d** diz ao programa que ele deve rodar em modo de decodificação;
* **-o** avisa que o próximo parâmetro é o arquivo onde a mensagem decodificada será armazenada;
* **[output]** é o arquivo que o programa irá criar para armazenar sua mensagem;
* **-f** avisa que o próximo parâmetro será o formato da imagem;
* **[formato]** deve ser apenas ppm ou bmp;
* **[imagem]** é a imagem que que contém a mensagem e de onde será realizada decodificação;
* **-s** indica que a mensagem decodificada deve ser exibida na tela, não salva em um arquivo (essa opção invalda **-o [output]**).

**Exemplo:**

*./steg -d -o mensagem.txt -f ppm imagem.ppm*  
*./steg -d -s -f bmp imagem.bmp*

# Como é realizada a encodificação de mensagens?

O programa irá considerar dois argumentos importantes para esse processo: a imagem e a mensagem fornecidas.

A primeira verificação à ser feita é se a mensagem cabe dentro da imagem. Depois disso, para facilitar o trabalho, precisamos converter tanto os pixels da imagem quanto os caracteres da mensagem para binário. Com isso feito, basta sair comparando os bits menos diferenciais (ou **lsb**, sigla em inglês para less differential bit) dos pixels com os caracteres da mensagem.

Acompanhe o seguinte exemplo:

Digamos que nosso arquivo **mensagem.txt** contenha apenas um único caractere (para facilitar a exemplificação) e este caractere é o "R". Seu valor decimal na tabela ASCII é 82, que em binário fica 01010010. Para armazenar "R" em uma imagem, sem distorcê-la. 
