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

Digamos que nosso arquivo **mensagem.txt** contenha apenas um único caractere (para facilitar a exemplificação) e este caractere é o "R". Seu valor decimal na tabela ASCII é 82, que em binário fica 01010010. Para cada bit de "R", precisaremos de 1 byte da imagem para armazená-lo. Neste exemplo, precisamos de 8 bytes. Se 1 pixel contém 3 bytes, arredondando a conta precisaremos de uma imagem com no mínimo 3 pixels para armazenar "R".

Os valores desses 3 pixels serão então convertidos para binário e as verificações serão nos bits menos diferenciais (os de ordem 2⁰). Para facilitar na exemplificação, transcreverei abaixo apenas os bit menos diferenciais desses 3 pixels:

* 1 0 0 0 1 1 1 0 0

Consideremos os valores em binário do "R" (de trás pra frente). Se o primeiro bit do "R" for igual ao bit menos diferencial do primeiro pixel, o valor é mantido, caso contrário é trocado para o valor de "R", e assim sucessivamente. No nosso exemplo, fica assim:

* Primeiro bit de R = 0. Bit menos diferencial do primeiro byte = 1. São diferentes, troca.
* Segundo bit de R = 1. Bit menos diferencial do segundo byte = 0. São diferentes, troca.
* Terceiro bit de R = 0. Bit menos diferencial do terceiro byte = 0. São iguais, mantém.
* Quarto bit de R = 0. Bit menos diferencial do quarto byte = 0. São iguais, mantém.
* Quinto bit de R = 1. Bit menos diferencial do quinto byte = 1. São iguais, mantém.
* Sexto bit de R = 0. Bit menos diferencial do sexto byte = 1. São diferentes, troca.
* Sétimo bit de R = 1. Bit menos diferencial do sétimo byte = 1. São iguais, mantém.
* Oitavo bit de R = 0. Bit menos diferencial do oitavo byte = 0. São iguais, mantém.

Ao final da operação, os bits menos significativos desses 8 bytes será:

* 0 1 0 0 1 0 1 0

Ou seja, os mesmos bits que compõem o caractere "R"! Depois disso, cada byte será convertido de binário para decimal e armazenado de volta no struct que contém todos os pixels da imagem.

É criado então uma cópia da imagem original, contendo agora nos bits menos diferenciais dos 3 primeiros pixels a mensagem criptografada, no nosso caso, o "R".
