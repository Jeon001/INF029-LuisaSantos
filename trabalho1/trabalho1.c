// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  DataQuebrada dq = quebraData(data);
  if (dq.valido == 0) {
      return 0;
  }

  int ano = dq.iAno;
  if (ano >= 0 && ano < 100) {
      ano += (ano < 50 ? 2000 : 1900);
  }

  int mes = dq.iMes;
  int dia = dq.iDia;

  if (mes < 1 || mes > 12) {
      return 0;
  }

  int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
  int diasNoMes;

  switch (mes) {
      case 2:
          diasNoMes = bissexto ? 29 : 28;
          break;
      case 4:
      case 6:
      case 9:
      case 11:
          diasNoMes = 30;
          break;
      default:
          diasNoMes = 31;
          break;
  }

  if (dia < 1 || dia > diasNoMes) {
      return 0;
  }

  return 1;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    DiasMesesAnos dma;
    dma.qtdDias = 0;
    dma.qtdMeses = 0;
    dma.qtdAnos = 0;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    } else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    } else {
      DataQuebrada di = quebraData(datainicial);
      DataQuebrada df = quebraData(datafinal);

      int anoI = di.iAno;
      if (anoI >= 0 && anoI < 100) anoI += (anoI < 50 ? 2000 : 1900);
      int anoF = df.iAno;
      if (anoF >= 0 && anoF < 100) anoF += (anoF < 50 ? 2000 : 1900);

      // Verificar se datainicial > datafinal
      int maior = 0;
      if (anoI > anoF) maior = 1;
      else if (anoI == anoF) {
          if (di.iMes > df.iMes) maior = 1;
          else if (di.iMes == df.iMes) {
              if (di.iDia > df.iDia) maior = 1;
          }
      }

      if (maior) {
          dma.retorno = 4;
          return dma;
      }

      int anos = anoF - anoI;
      int meses = df.iMes - di.iMes;
      int dias = df.iDia - di.iDia;

      if (dias < 0) {
          meses--;
          int mesAnterior = df.iMes - 1;
          int anoAnterior = anoF;
          if (mesAnterior < 1) {
              mesAnterior = 12;
              anoAnterior--;
          }
          int bissextoAnt = (anoAnterior % 4 == 0 && anoAnterior % 100 != 0) || (anoAnterior % 400 == 0);
          int diasMesAnt = 31;
          if (mesAnterior == 2) diasMesAnt = bissextoAnt ? 29 : 28;
          else if (mesAnterior == 4 || mesAnterior == 6 || mesAnterior == 9 || mesAnterior == 11) diasMesAnt = 30;

          dias += diasMesAnt;
      }

      if (meses < 0) {
          anos--;
          meses += 12;
      }

      dma.qtdAnos = anos;
      dma.qtdMeses = meses;
      dma.qtdDias = dias;
      dma.retorno = 1;
      return dma;
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    char alvo = c;

    for (int i = 0; texto[i] != '\0'; i++) {
        char atual = texto[i];
        int avanca = 0;

        if ((unsigned char)texto[i] == 0xC3 && texto[i+1] != '\0') {
            unsigned char c2 = (unsigned char)texto[i+1];
            avanca = 1;
            if (c2 == 0xA1 || c2 == 0xA0 || c2 == 0xA2 || c2 == 0xA3 || c2 == 0x81 || c2 == 0x80 || c2 == 0x82 || c2 == 0x83) atual = 'a';
            else if (c2 == 0xA9 || c2 == 0xEA || c2 == 0x89 || c2 == 0x8A) atual = 'e';
            else if (c2 == 0xAD || c2 == 0x8D) atual = 'i';
            else if (c2 == 0xB3 || c2 == 0xB4 || c2 == 0xB5 || c2 == 0x93 || c2 == 0x94 || c2 == 0x95) atual = 'o';
            else if (c2 == 0xBA || c2 == 0xBC || c2 == 0x9A || c2 == 0x9C) atual = 'u';
            else if (c2 == 0xA7 || c2 == 0x87) atual = 'c';
            else {
                avanca = 0;
            }
        }

        if (avanca) {
            i++;
        }

        char tComp = atual;
        char aComp = alvo;

        if (!isCaseSensitive) {
            if (tComp >= 'A' && tComp <= 'Z') tComp += 32;
            if (aComp >= 'A' && aComp <= 'Z') aComp += 32;
        }

        if (tComp == aComp) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int k = 0;

    int lenBuscaChars = 0;
    for (int b = 0; strBusca[b] != '\0'; ) {
        unsigned char c = (unsigned char)strBusca[b];
        int clen = 1;
        if (c >= 0xC0) clen = (c < 0xE0) ? 2 : ((c < 0xF0) ? 3 : 4);
        b += clen;
        lenBuscaChars++;
    }

    if (lenBuscaChars == 0) return 0;

    int lenBuscaBytes = 0;
    while (strBusca[lenBuscaBytes] != '\0') lenBuscaBytes++;

    int charIndex = 1;
    for (int i = 0; strTexto[i] != '\0'; ) {
        int match = 1;
        for (int j = 0; j < lenBuscaBytes; j++) {
            if (strTexto[i + j] == '\0' || strTexto[i + j] != strBusca[j]) {
                match = 0;
                break;
            }
        }

        if (match) {
            posicoes[k++] = charIndex;
            posicoes[k++] = charIndex + lenBuscaChars - 1;
            qtdOcorrencias++;
        }

        unsigned char tc = (unsigned char)strTexto[i];
        int tlen = 1;
        if (tc >= 0xC0) tlen = (tc < 0xE0) ? 2 : ((tc < 0xF0) ? 3 : 4);
        i += tlen;
        charIndex++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0;
    int temp = num;
    while (temp > 0) {
        int resto = temp % 10;
        invertido = invertido * 10 + resto;
        temp /= 10;
    }
    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    char sBase[20], sBusca[20];
    sprintf(sBase, "%d", numerobase);
    sprintf(sBusca, "%d", numerobusca);

    int qtdOcorrencias = 0;
    int lenBusca = 0;
    while (sBusca[lenBusca] != '\0') lenBusca++;
    int lenBase = 0;
    while (sBase[lenBase] != '\0') lenBase++;

    if (lenBusca == 0 || lenBusca > lenBase) return 0;

    for (int i = 0; i <= lenBase - lenBusca; i++) {
        int match = 1;
        for (int j = 0; j < lenBusca; j++) {
            if (sBase[i + j] != sBusca[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
    int len = 0;
    while (palavra[len] != '\0') len++;

    int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 10; c++) {
            for (int d = 0; d < 8; d++) {
                int ok = 1;
                for (int i = 0; i < len; i++) {
                    int nr = r + i * dx[d];
                    int nc = c + i * dy[d];
                    if (nr < 0 || nr >= 8 || nc < 0 || nc >= 10 || matriz[nr][nc] != palavra[i]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) return 1;
            }
        }
    }
    return 0;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
