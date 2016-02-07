#include <stdio.h>

int main(){
  FILE* arq = fopen("pages/1","r");
  unsigned short chave;
  char texto[8];
  
  if(!arq) return -1;

  fscanf(arq, "%hhu %s", &chave, texto);

  printf("\n>%hhu\n", chave);
  printf(">%s", texto);

  fclose(arq);
  return 0;
}
