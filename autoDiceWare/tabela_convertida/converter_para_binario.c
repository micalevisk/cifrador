#include <stdio.h>
#include <string.h>

//for i in `seq 1 1 36`; do mv -- "$i" "$i.bkp"; done
//for i in `seq 1 1 36`; do ./converter_para_binario "$i.bkp" "$i"; done 

#define TAM_CHARS 8
#define INPUT_FILE argv[1]
#define OUTPUT_FILE argv[2]

typedef struct{
  unsigned short key;
  char word[TAM_CHARS];
}tipoDados;

// ./programName <inputFile> <outputFile>
int main(int argc, char* argv[]){
  if(argc != 3) return 1;

  unsigned short chaveLida;
  char palavraLida[TAM_CHARS];
  tipoDados dadosLidos;
  
  FILE* arqLeitura = fopen(INPUT_FILE, "r");
  FILE* arqSaida = fopen(OUTPUT_FILE, "wb");
  
  if(!arqLeitura || !arqSaida){ perror("AO ABRIR"); return 1; }

  while( (fscanf(arqLeitura, "%hu %s", &chaveLida, palavraLida))==2 ){
    dadosLidos.key = chaveLida;
    strcpy(dadosLidos.word, palavraLida);

    fwrite(&dadosLidos, sizeof(tipoDados), 1, arqSaida);   
  }

  fclose(arqLeitura);
  fclose(arqSaida);
  
  return 0;
}
