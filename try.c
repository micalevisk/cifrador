#include <stdio.h>
#define n 4 // fim - inicio + 1

unsigned f(int x){
  unsigned k = x/n;
  return (x - k*n);
}

int main(){

  //RETA: 0 - 1 - 2 - 3
  //RETA: 65 - ... - 90 [NAO FUNCIONA]
  int numero=0;
  
  while(numero > -1){
    printf("\n>> x = ");
    scanf("%d", &numero);

    printf("-> corresponde a %u \n", f(numero));
  }
}

/*
[0,1,2,3] 
n = 4
k = x/n  (numero de voltas++)

   f(x) = x - k*n

   

*/
