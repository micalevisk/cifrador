//  ./programa <n_palavras_senha> <mostrar_sequências>
//  autoDiceWare.c
//  Created by Micael Levi on 02/07/16.
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>

#define ERROR_USE fprintf(stderr, "\n-> TO USE: ./program_name <password_size> <show_numbers(0 = no)>\n")
#define ERROR_OPENFILE perror("AO ABRIR PARA LEITURA")

#define N_ARGS 3 						/* Tamanho do array 'argv'. */
#define MOSTRAR_SEQUENCIAS atoi(argv[2])/* Mostrar sequências correspondente às palavras. */
#define TAM_SENHA atoi(argv[1]) 		/* Quantidade de palavras na senha-frase. */
#define TAM_CHARS 8 					/* Quantidade máxima de caracteres por palavra. */
#define PAGINAS_FILE "tabela_convertida/vetor1" /* Arquivo que contém a relação PREFIX:PAGE. */
#define CHAVES_FILE  "tabela_convertida/vetor2" /* Arquivo que contém a relação KEY:LINE.    */
#define TABELA_DIR	 "tabela_convertida/pages/" /* Diretório que contém todas as 36 páginas separadas em arquivos distintos (arquivos binários). */

typedef struct{
  unsigned short key;
  char word[TAM_CHARS];
}tipoDados;

//////////////////////////////////////////////////////////////////////////////
unsigned gerarSequencia(void);
int tamanhoDoArquivo(FILE* descritor);
int buscarNoArquivo(FILE* descritor, unsigned short chave, char* palavraLida);
void sleep(const unsigned secs);
//////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]){
	int nPalavraAtual;
	char numeroPagina[3], dirPagina[strlen(TABELA_DIR)+3], *palavraAtual;
	unsigned sequenciaAtual, *sequenciasObtidas;
	unsigned short prefixoAtual, chaveAtual; /* O 'prefixo' indica a página e a 'chave' indica a palavra. */
	unsigned short prefixoLido;
	FILE *arqLeituraPrefixo, *arqLeituraPalavra;

	if(argc != N_ARGS){ ERROR_USE; exit(EXIT_FAILURE); }

	arqLeituraPrefixo = fopen(PAGINAS_FILE, "r");
	if(!arqLeituraPrefixo){ ERROR_OPENFILE; exit(EXIT_FAILURE); }

	palavraAtual = (char*) malloc(sizeof(char)*TAM_CHARS);
	sequenciasObtidas = (unsigned*) malloc(sizeof(unsigned)*TAM_SENHA);

	fprintf(stdout, "\n> SENHA-FRASE: ");
	/* Obtendo sequência e procurando a palavra referente à ela. Repetindo esse processo TAM_SENHA vezes. */
	for(nPalavraAtual=0; nPalavraAtual < TAM_SENHA; nPalavraAtual++){
		sequenciaAtual = gerarSequencia();
		sequenciasObtidas[nPalavraAtual] = sequenciaAtual;

		prefixoAtual = sequenciaAtual / 1000; /* 2 primeiros números da sequência. */
		chaveAtual 	 = sequenciaAtual % 1000; /* 3 últimos números da sequência. */
		// printf(">> [%u] %hhu|%hu\n", sequenciaAtual, prefixoAtual, chaveAtual);

		/* Buscando no vetor1 a página correspondente ao prefixoAtual. */ 
		rewind(arqLeituraPrefixo);
		while(fscanf(arqLeituraPrefixo, "%hhu:%s", &prefixoLido, numeroPagina)==2) 
			if(prefixoLido == prefixoAtual) break;

		/* Definindo diretório do arquivo que contém a palavra correspondente à chave que será buscada. */
		strcpy(dirPagina, TABELA_DIR);
		strcat(dirPagina, numeroPagina);

		/* Abrindo arquivo de acordo com a página referenciada, buscando a chave corrente e exibindo a palavra correspondente. */
		arqLeituraPalavra = fopen(dirPagina, "rb");
		if(!arqLeituraPalavra){ ERROR_OPENFILE; exit(EXIT_FAILURE); }
		buscarNoArquivo(arqLeituraPalavra, chaveAtual, palavraAtual);
		fprintf(stdout,"%s ", palavraAtual);
		fclose(arqLeituraPalavra);

		sleep(1); /* Por está obtendo a mesma sequência "aletória" quando o intervalo é menor que 1s. */
	}
	fclose(arqLeituraPrefixo);

	if(MOSTRAR_SEQUENCIAS){
		fprintf(stdout, "\n> SEQUENCIAS : ");
		for(nPalavraAtual=0; nPalavraAtual < TAM_SENHA; nPalavraAtual++) fprintf(stdout, "[%u] ", sequenciasObtidas[nPalavraAtual]);
	}

	return 0;
}


unsigned gerarSequencia(){
	unsigned nRandom, quantidade=5, i;
	unsigned seq=0;
	srand(time(0));
	for(i=0; i < quantidade; i++){
		nRandom = rand() % 6 + 1;
		nRandom *= (unsigned)pow(10,i);

		seq += nRandom;
	}	
	return seq;
}


int tamanhoDoArquivo(FILE* descritor){
	struct stat buf;
	fstat(fileno(descritor), &buf);
	return buf.st_size;
}

int buscarNoArquivo(FILE* descritor, unsigned short chave, char* palavraLida){
	unsigned inicio=0, meio, fim;
	tipoDados dadosAtual;

    fim = tamanhoDoArquivo(descritor) / sizeof(tipoDados);
    rewind(descritor);

    while(inicio <= fim){
      meio = (inicio+fim)/2;

      fseek(descritor, meio * sizeof(tipoDados), SEEK_SET); 
      fread(&dadosAtual, sizeof(tipoDados), 1, descritor);

      if(chave > dadosAtual.key)  inicio = meio + 1;
      else if(chave < dadosAtual.key)fim = meio - 1;
      else{
      	strcpy(palavraLida, dadosAtual.word);
      	return 1;
      } 
    }
    return 0;
}


void sleep(const unsigned secs){
	unsigned final = time(0) + secs;
	while(time(0) < final);
}
