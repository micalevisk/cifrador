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

/* 4.294.967.296 (=2^32) key options. */
#define MAIOR_CHAVE 4294967295

//////////////////FUNCTIONS////////////////////////////////////////////////////
void readString(char stringVar[], int tamanho);
void criptografarCaracter(bool sim, char* caractere, int chave);
void process(char fileDir[], bool cript, bool delOriginal, unsigned key);
void menu(void);
//////////////////////////////////////////////////////////////////////////////


int main(){
    setlocale(LC_ALL, "Portuguese");
    system("title Criptografia Cifra de César");
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


void criptografarCaracter(bool sim, char* caractere, int chave){
    int charCript;
    char currChar = *caractere;
    short limiteTeto, limiteChao;

    if(isupper(currChar)){  limiteTeto='Z'; limiteChao='A'; }
    else{                   limiteTeto='z'; limiteChao='a'; }

    if(sim){
        charCript = currChar + chave;
        while(charCript > limiteTeto) charCript -= 26;
    }
    else{
        charCript = currChar - chave;
        while(charCript < limiteChao) charCript += 26;
    }

    *caractere = charCript;
}

void process(char fileDir[], bool cript, bool delOriginal, unsigned key){
    ifstream inputFile;
    ofstream outputFile;
    char currChar;

    inputFile.open(fileDir);
    if(inputFile.is_open()){
        outputFile.open(OUTPUT_DIR);

        while(inputFile >> noskipws >> currChar){
            if(isalpha(currChar)) criptografarCaracter(cript, &currChar, key);
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
    bool criptografar, apagarOriginal=false;
    unsigned chave;

    cout << endl << ">> Nome do arquivo a ser criptografado em " << INPUT_DIR;
    readString(nomeArquivo, TAM_FILENAME);
    strcat(diretorioArquivoEntrada, nomeArquivo);

    if(!strcmp(diretorioArquivoEntrada, OUTPUT_DIR)){ printf("\n\t Renomeie o arquivo de entrada!\n\n"); exit(1); }

    cout << ">> Chave: ";                        cin >> chave;
    cout << ">> Criptografar?    (0 = NAO): ";   cin >> criptografar;
    cout << ">> Apagar original? (0 = NAO): ";   cin >> apagarOriginal;

    process(diretorioArquivoEntrada, criptografar, apagarOriginal, chave);
}
