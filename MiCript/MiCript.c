//
//	OBS: COMPILAR COM g++
//  MiCript.c
//  Created by Micael Levi on 16/02/02.
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved
//

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TAM_TEXTO 100000
#define KEY_SIZE 500

#define ERROR_MSG printf("\n\nErro!\nTamanho do texto excede o limite de caracteres (%u bits)\n\n", TAM_TEXTO)
#define CLS system("cls")
#define PAUSE system("pause")

#define DEFAULT_KEY "AbCd"

unsigned TAM_CHAVE = KEY_SIZE;
char CHAVE[KEY_SIZE];
char TEXTO[TAM_TEXTO];

typedef enum{ Mensagem, Arquivo }entradaTexto;
//--------------------------------------------

int TEXTO_CRIPT[TAM_TEXTO];

/*FUNÇÕES*/
bool set_chave(char chave[]);
bool criptografar(void);
bool descriptografar(void);
void apagarTudo(void);
void receberTexto(entradaTexto tipo);
void menuCriptografar(void);
void receberArquivoCriptografado(void);
void menu(void);
void lerString(char stringVar[], int tamanho);
/*********/

int main(){
	setlocale(LC_ALL, "Portuguese");
	system("color f");
	system("title MiCript * Criptografia de Textos");

	char defaultKey[] = DEFAULT_KEY;
	if(set_chave(defaultKey)) menu();

	return 0;
}



bool set_chave(char novaChave[]){
	if(strlen(novaChave) < KEY_SIZE){
		strcpy(CHAVE, novaChave);
		TAM_CHAVE = strlen(CHAVE);
		return true;
	}
	return false;
}

/*--------------------------------*/
bool criptografar(){
	int CHAVE_int;
	unsigned TEXTO_size = strlen(TEXTO);
	unsigned i, aux;

	for (i = 0; i < TEXTO_size; ++i) TEXTO_CRIPT[i] = TEXTO[i];

	for (aux = 0; aux < TEXTO_size;){
		for (i = 0; i < TAM_CHAVE; ++i){
			CHAVE_int = CHAVE[i];
			TEXTO_CRIPT[aux] *= CHAVE_int;
			aux++;
		}
	}
	return true;
}

bool descriptografar(){
	int valor;
	unsigned pos_chave = 0, pos_texto = 0;
	FILE* arquivo = fopen("c:\\MiCript\\arquivos_recebidos\\criptografado", "r");

	if (!arquivo){ perror("to open file1"); return false; }

	while (!feof(arquivo)){
        fscanf(arquivo, "%d", &valor);

		valor /= CHAVE[pos_chave];
		TEXTO[pos_texto] = (char)valor;
		pos_texto++;

		if (pos_chave == TAM_CHAVE - 1) pos_chave = 0;
		else pos_chave++;
	}

	fclose(arquivo);
	return true;
}
/*--------------------------------*/

void apagarTudo(){
	remove("c:\\MiCript\\arquivos_gerados\\descriptografado.txt");
	remove("c:\\MiCript\\arquivos_gerados\\criptografado");
	remove("c:\\MiCript\\arquivos_originais\\original.txt");
	remove("c:\\MiCript\\arquivos_recebidos\\criptografado");
}


void receberTexto(entradaTexto tipo){
	char aux[TAM_TEXTO], pause, palavra[100];
	bool ready = false;
	unsigned TEXTO_size = 0, i;
	FILE* arquivo;

	switch (tipo){
	case Mensagem:
		printf("\n\t Receber Texto Para Criptografar");
		printf("\n>> Digite o texto: \n\n");
		lerString(aux, TAM_TEXTO);

		if (strlen(aux) <= TAM_TEXTO){
			strcpy(TEXTO, aux);
			printf("\n\nTexto recebido com sucesso!!\a");
			printf("\n\nCriptografando texto...\n\n");
			ready = true;
		}
		else ERROR_MSG;
		break;

	case Arquivo:
		printf("\n\t Instruções Para Importar um Arquivo de Texto:");
		printf("\n\n 1º Renomeie o arquivo para 'original'");
		printf("\n 2º Copie o arquivo para a pasta que será aberta a seguir");
		printf("\n 3º Feche o explorador de arquivo e retorne à aplicação");

		printf("\n\n\n Pressione ENTER Para Abrir a Pasta...");
		scanf("%c", &pause);
		setbuf(stdin, NULL);

		system("explorer c:\\MiCript\\arquivos_originais\\"); // abrindo pasta

		printf("\n\n Pressione ENTER Após Colar o Arquivo na Pasta...\n");
		scanf("%c", &pause);

		setbuf(stdin, NULL);
		printf("\n\nImportando Arquivo...\n");

		arquivo = fopen("c:\\MiCript\\arquivos_originais\\original.txt", "r");

		if (!arquivo) perror("ao abrir file2");
		else{
			while (!feof(arquivo)){
				fscanf(arquivo, "%s", palavra); 
				strcat(aux, " ");      
				strcat(aux, palavra);
			}
			fclose(arquivo);

			if (strlen(aux) <= TAM_TEXTO){
				strcpy(TEXTO, aux);
				printf("Arquivo Recebido Com Sucesso!\a");
				printf("\n\nCriptografando Texto...\n\n");
				ready = true;
			}
			else ERROR_MSG;
		}
		break;

	default:break;
	}

	if (ready){
		if (criptografar()){
			TEXTO_size = strlen(TEXTO);
			printf("\n\nTexto Criptografado Com Sucesso!");
			remove("c:\\MiCript\\arquivos_originais\\original.txt");

			arquivo = fopen("c:\\MiCript\\arquivos_gerados\\criptografado", "w");

			if (!arquivo) perror("ao criar file3");
			else{
				for (i = 0; i < TEXTO_size; ++i) fprintf(arquivo, "%d ", TEXTO_CRIPT[i]);
				fclose(arquivo);
			}

			printf("\n\nPressione ENTER Para Abrir a Pasta do Arquivo Gerado!\n");
			scanf("%c", &pause);
			setbuf(stdin, NULL);
			system("explorer c:\\MiCript\\arquivos_gerados\\");
		}
		else printf("\n\nNão foi Possível Criptografar o Texto!!\n\n");
	}
	PAUSE;
}


void menuCriptografar(){
	int opcao;
	printf("\n\t Criptografar Texto ou Arquivo\n");
	printf("\n 1 - Digitar Texto");
	printf("\n 2 - Importar Arquivo de Texto");
	printf("\n 3 - Voltar ao Menu Principal");
	printf("\n\n Informe a Opção Desejada: ");
	scanf("%d", &opcao);
	setbuf(stdin, NULL); // limpar buffer do teclado

	switch (opcao){
	case 1:
		CLS;
		receberTexto(Mensagem);
		break;

	case 2:
		receberTexto(Arquivo);
		break;

	case 3:break;

	default: printf("Opção inválida! Tente novamente...");
	}
}


void receberArquivoCriptografado(){
	FILE* arquivo;
	char pause;

	printf("\n\t Instruções Para Importar um Arquivo Criptografado:");
	printf("\n\n 1º Renomeie o Arquivo Para 'criptografado'");
	printf("\n\n 2º Copie o Arquivo Para a Pasta que Será Aberta a Seguir");
	printf("\n\n 3º Feche o Explorador e Retorne à Aplicação");

	printf("\n\n\n\n\n Pressione ENTER Para Abrir a Pasta");
	scanf("%c", &pause);
	setbuf(stdin, NULL);

	system("explorer c:\\MiCript\\arquivos_recebidos\\");

	printf("\n\nPressione ENTER Após Colar o Arquivo na Pasta...\n");
	scanf("%c", &pause);
	setbuf(stdin, NULL);
	printf("\nImportando Arquivo...\n\n");

	if (descriptografar()){
		printf("\n Arquivo Descriptografado com Sucesso!\n\a");
		PAUSE;

		CLS;
		printf("\n%s\n\n", TEXTO);
		scanf("%c", &pause);

		arquivo = fopen("c:\\MiCript\\arquivos_gerados\\descriptografado.txt", "w");

		if (!arquivo) perror("ao criar file4");
		else{
			fprintf(arquivo, "%s", TEXTO);
			fclose(arquivo);
		}

		printf("\n\n\tPressione ENTER para Abrir a Pasta do Arquivo Descriptografado!\n");
		scanf("%c", &pause);
		setbuf(stdin, NULL);

		system("explorer c:\\MiCript\\arquivos_gerados\\");
	}
	else{
		printf("\n Não foi Possível Descriptografar o Arquivo!\n\n");
		PAUSE;
	}

}



void menu(){
	char chave[500];
	int opcao;
	//apagarTudo();

	while (1){
		CLS;
		printf("\n\t ººº CHAVE: {%s} ººº \n", CHAVE);
		printf("\n1 - Criptografar texto");
		printf("\n2 - Receber arquivo criptografado");
		printf("\n3 - Configurar Chave");
		printf("\n4 - Apagar Todos Os Arquivos");
		printf("\n5 - Sair\n");
		printf("\n\nInforme a Opção Desejada: ");
		scanf("%d", &opcao);
		setbuf(stdin, NULL); // limpar buffer do teclado

		switch (opcao){
		case 1:
			CLS;
			menuCriptografar();
			break;

		case 2:
			CLS;
			receberArquivoCriptografado();
			break;

		case 3:
			CLS;
			printf("Informe a Chave: ");
			gets(chave);
			if (set_chave(chave)) printf("\nChave Modificada Com Sucesso!\n\n");
			else printf("\nChave Não foi Modificada!!\n\n");

			PAUSE;
			break;

		case 4:
			apagarTudo();
			break;

		case 5:
			printf("\nFinalizando...\n\n");
			//PAUSE;
			exit(0);
			break;

		default:
			printf("\nOpção inválida!\n\n");
			PAUSE;
		}
	}
}


void lerString(char stringVar[], int tamanho) {
	char ch;

	fgets(stringVar, tamanho, stdin);
	if (stringVar[strlen(stringVar) - 1] == '\n') stringVar[strlen(stringVar) - 1] = 0;
	else while ((ch = getchar()) != '\n' && ch != EOF);
}

