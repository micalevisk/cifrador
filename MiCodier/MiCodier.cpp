//
//  MiCodier.cpp
//  Created by Micael Levi on 02/03/16.
//  Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <limits.h>
using namespace std;

#define TAM_FILENAME 30 /* Limit number of characters in input filename. */
#define TAM_DIRNAME  65 /* Limit number of characters in input directory. */

#define INPUT_DIR  "C:\\Users\\user\\desktop\\"
#define OUTPUT_DIR "C:\\Users\\user\\desktop\\cript.txt"

/* 65.536 (=2^16)               valid key   (shift logic). */
/*     26 (alphabet characters) key options (Cesar logic). */
#define MAIOR_CHAVE1 USHRT_MAX
#define MAIOR_CHAVE2 25

//////////////////FUNCTIONS/////////////////////////////////////////////////////////////////////////////
void readString(char stringVar[], int tamanho);
void criptografarCaracter(bool criptografar, bool logicaCesar, char* caractere, unsigned short chave);
void process(char fileDir[], bool cript, bool shiftLogic, bool delOriginal, unsigned short key);
void menu(void);
////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){
  // setlocale(LC_ALL, "Portuguese");
  system("title MiCodier * Criptografia de Textos");
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


void criptografarCaracter(bool criptografar, bool logicaDeslocamento, char* caractere, unsigned short chave){
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

void process(char fileDir[], bool cript, bool shiftLogic, bool delOriginal, unsigned short key){
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
  int criptografar, apagarOriginal=false, logicaCesar=true;
  unsigned short chave; /* lógica de deslocamento. */
  char chave2;          /* lógica da Cifra de César. */

  cout << endl << ">> Nome do arquivo a ser criptografado em " << INPUT_DIR;
  readString(nomeArquivo, TAM_FILENAME);
  strcat(diretorioArquivoEntrada, nomeArquivo);

  if(!strcmp(diretorioArquivoEntrada, OUTPUT_DIR)){ printf("\n\t Renomeie o arquivo de entrada!\n\n"); system("pause"); exit(1); }

  cout << ">> Opcao de criptografia  (0 = SHIFT): "; cin >> logicaCesar;
  cout << ">> Criptografar?          (0 = NAO)  : "; cin >> criptografar;
  cout << ">> Apagar original?       (0 = NAO)  : "; cin >> apagarOriginal;
  if(!logicaCesar){ cout << ">> Chave (numero)  : "; cin >> chave;  }
  else{             cout << ">> Chave (letra)   : "; cin >> chave2; chave = toupper(chave2); }

  process(diretorioArquivoEntrada, criptografar, !logicaCesar, apagarOriginal, chave);
}
