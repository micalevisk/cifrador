#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include "CharSpecs.h"

#define TAM_LINHA 100 // no máximo 100 caracteres por linha
using namespace std;

//  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
// [X, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z]
char alpha[27];

/*
||||||||   |||  |||      |||
|||               |||  |||
||||||||   |||       |||
|||        |||     ||| |||
|||        |||  |||      |||
TORNAR O ALFABETO CÍCLICO
*/

void lerString(char stringVar[], int tamanho) {
    char ch;

    fgets(stringVar,tamanho,stdin);
    if(stringVar[strlen(stringVar)-1] == '\n')
        stringVar[strlen(stringVar)-1] = 0;
    else
        while((ch = getchar())!='\n' && ch != EOF );
}

/**
void enter(){
    char frase[] = "abc a dasdadasd\n asd";
    int i=0;
    int chave=1, enc;

    system("cls");
    printf("\nDigite a frase a ser encriptada: ");
    //lerString(frase, 20);
    //  scanf("%s",frase);

    printf("\n\nEscreva uma chave: ");
    //scanf("%d",&chave); // numero de deslocamentos.

    printf("\n\nFrase encriptada com sucesso!\n\n");
    printf("Encriptacao:  ");
    int tamanhoFrase = strlen(frase);
    for(i=0; i < tamanhoFrase; ++i){
        enc = frase[i] + chave;

        if(frase[i] == 10) printf("|");         // enter
        else if(frase[i] != 32) printf("%c", enc);
        else printf("/");                       // espaço

    }
    printf("\n\n");
}
**/
/*
void criptografar(bool sim, char linha[], int chave)
{
    int charCript;
    int tamanhoLinha = strlen(linha);
    int i=0;

    if(sim){
        for(; i < tamanhoLinha; ++i){
            charCript = linha[i] + chave;

            if(linha[i] == 10) linha[i] = '0'; // =enter

            else if(linha[i] != 32) linha[i] = charCript; // =criptografado

            else linha[i] = '1'; // =espaço
        }
    }
    else{
        for(i=0; i < tamanhoLinha; ++i){
            charCript = linha[i] - chave;

            if(linha[i] == '0') linha[i] = '\n';
            else if(linha[i] != '1') linha[i] = charCript;
            else linha[i] = ' ';
        }
    }
}
*/

void criptografarChar(bool sim, char *caractere, int chave)
{
    int charCript;

    if(sim){
        charCript  = *caractere + chave; // criptografar
        *caractere = charCript;

        if((toupper(charCript) > 90) && (chave <= 25)) *caractere -= 26; /// [FUNCIONA ATÉ +25]

//        char x = toupper(charCript);
//        while(x > 90){ /// FUNCIONA ATÉ +5
//            *caractere -= 26;
//            x = toupper(*caractere);
//        }

    }
    else{
        charCript = *caractere - chave; // descriptografar

    }
}



void processar()
{
    char fileDir[37] = ""; ///C:\\Users\\user\\desktop\\'
    char fileName[10];
    ifstream arquivoDeLeitura;  // read from files
    ofstream resultado;         // write on files
    string linhaStr, result;
    char linhaChr[TAM_LINHA];
    int limite;                 // de leitura da linha
    bool cript, trash=0;
    int key;
    char caractere;

    cout << ">> Nome do arquivo a ser criptografado (sem .txt) no \\desktop\\ ";
    lerString(fileName, 10);
    //scanf("%s", fileName);
    //setbuf(stdin, NULL);
    strcat(fileDir, fileName); // concatena em 'fileDir' o 'fileName'
    strcat(fileDir, ".txt");

    cout << ">> Chave: ";
    cin >> key;
    //scanf("%d", &key);

    cout << ">> Criptografar?    (0 = NAO): ";
    cin >> cript;
/*
    cout << ">> Apagar original? (0 = NAO): ";
    cin >> trash;
*/
    arquivoDeLeitura.open(fileDir);
    if(arquivoDeLeitura.is_open()){
        resultado.open("C:\\Users\\user\\desktop\\cript.txt");

        //while((getline(arquivoDeLeitura, linhaStr)) && (!arquivoDeLeitura.eof())){ // ANALIZA LINHA A LINHA (NÃO CARACTERES)
        while(arquivoDeLeitura >> noskipws >> caractere){
            //limite = linhaStr.find('\n');
            //if(limite<0)
            /*
            limite = linhaStr.length(); // cada caracter equivale a 1 Byte
            linhaStr.copy(linhaChr, limite+1, 0);     // copy to array, how many char, start position from 'linhaStr'
            linhaChr[limite]   = '\n';
            linhaChr[limite+1] = '\0';
            criptografar(cript, linhaChr, key);
            */

            if(isalpha(caractere))
                criptografarChar(cript, &caractere, key);

            resultado << caractere;
        }
        resultado.close();
        arquivoDeLeitura.close();

        if(trash) remove(fileDir);
        cout << "\a Arquivo CRIADO COM SUCESSO!" << endl << endl;
    }
    else
        cout << " O arquivo '" << fileName << "' nao foi encontrado no \\desktop " << endl;

    system("pause");
}



int main(){

    /*
    string str = "12i4";
    int limite = str.find('i');
    printf("%d %d \n", limite, str.length()); //out: 2, 4
    */


    //PREENCHENDO VETOR QUE CONTÉM O ALFABETO MAIÚSCULO
    alpha[0] = 'X';
    int i=1;
    char c = 'A';
    for(; i<27; i++, c++) alpha[i] = c;


    processar();

    /** TESTANDO A CLASSE
    c = 'A';
    CharSpecs T = CharSpecs(c);
    cout << T.getCaractere() << endl;
    */


    return 0;
}
/*
    dado 0 <= toUpper(charCript) < 91,
    caracter = alpha[charCript - 64]

*/
