//
//  criptografiaDeCesar.cpp
//  Created by Micael Levi on 02/03/2016.
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define TAM_FILENAME 30 /* Limit number of characters in input filename. */
#define TAM_DIRNAME  65 /* Limit number of characters in input directory. */

#define INPUT_DIR  "C:\\Users\\user\\desktop\\"
#define OUTPUT_DIR "C:\\Users\\user\\desktop\\cript.txt"

/* 4.294.967.296  (=2^32) key options (shift logic). */
/*    67.108.864  (=2^26)  key options (Cesar logic). */
#define MAIOR_CHAVE1 4294967295
#define MAIOR_CHAVE2 67108864

//////////////////FUNCTIONS/////////////////////////////////////////////////////////////////////////////
void readString(char stringVar[], int tamanho);
void criptografarCaracter(bool criptografar, bool logicaDeslocamento, char* caractere, unsigned chave);
void process(char fileDir[], bool cript, bool shiftLogic, bool delOriginal, unsigned key);
void menu(void);
////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){
  // setlocale(LC_ALL, "Portuguese");
  system("title Criptografia de Textos");
  system("color f3");

  menu();

  return 0;
}


void readString(char stringVar[], int tamanho) {
  char ch;

  fgets(stringVar,tamanho,stdin);
  if(stringVar[strlen(stringVar)-1] == '\n')  stringVar[strlen(stringVar)-1] = 0;
  else
      while((ch = getchar())!='\n' && ch != EOF );
}


void criptografarCaracter(bool criptografar, bool logicaDeslocamento, char* caractere, unsigned chave){
  int charCript;
  char currChar = *caractere;
  short limiteTeto, limiteChao;

  if(isupper(currChar)){  limiteTeto='Z'; limiteChao='A'; }
  else{                   limiteTeto='z'; limiteChao='a'; chave += 32; }

  if(!logicaDeslocamento) chave = chave - limiteChao;

  if(criptografar){
      charCript = currChar + chave;
      while(charCript > limiteTeto) charCript -= 26;
  }
  else{
      charCript = currChar - chave;
      while(charCript < limiteChao) charCript += 26;
  }

  *caractere = charCript;
}

void process(char fileDir[], bool cript, bool shiftLogic, bool delOriginal, unsigned key){
  ifstream inputFile;
  ofstream outputFile;
  char currChar;

  inputFile.open(fileDir);
  if(inputFile.is_open()){
      outputFile.open(OUTPUT_DIR);

      while(inputFile >> noskipws >> currChar){
          if(isalpha(currChar)) criptografarCaracter(cript, shiftLogic, &currChar, key);
          outputFile << currChar;
      }
      outputFile.close();
      inputFile.close();

      if(delOriginal) remove(fileDir);
      cout << endl << "\a Arquivo CRIADO COM SUCESSO! " << OUTPUT_DIR << endl << endl;
  }
  else
      cout << endl << "O arquivo '" << fileDir << "' nao foi encontrado!" << endl;

  system("pause");
}

void menu(){
  char diretorioArquivoEntrada[TAM_DIRNAME] = INPUT_DIR;
  char nomeArquivo[TAM_FILENAME];
  int criptografar, apagarOriginal=false, logicaDeslocamento;
  unsigned chave;   /* lógica de deslocamento. */
  char chave2;      /* lógica da Cifra de César. */

  cout << endl << ">> Nome do arquivo a ser criptografado em " << INPUT_DIR;
  readString(nomeArquivo, TAM_FILENAME);
  strcat(diretorioArquivoEntrada, nomeArquivo);

  if(!strcmp(diretorioArquivoEntrada, OUTPUT_DIR)){ printf("\n\t Renomeie o arquivo de entrada!\n\n"); system("pause"); exit(1); }

  cout << ">> Opcao de criptografia  (0 = SHIFT): ";        cin >> logicaDeslocamento;
  cout << ">> Criptografar?          (0 = NAO)  : ";        cin >> criptografar;
  cout << ">> Apagar original?       (0 = NAO)  : ";        cin >> apagarOriginal;
  if(!logicaDeslocamento){ cout << ">> Chave (numero): ";   cin >> chave;  }
  else{                    cout << ">> Chave (letra) : ";   cin >> chave2; chave = toupper(chave2);}

  process(diretorioArquivoEntrada, criptografar, !logicaDeslocamento, apagarOriginal, chave);
}
