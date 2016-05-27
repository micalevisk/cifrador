<!--
algoritmos.md
Created by Micael Levi on 02/03/2016 (update: 05/27/2016).
Copyright (c) 2016 Micael Levi L. Cavalcante. All rights reserved.
-->

Programa de criptografia simples que funciona com os princípios da criptografia "Cifra de César". <br>
Sendo _X_ a chave, _CH_ um caractere no texto e _Y_ este caractere após a criptografia/descriptografia. <br>
Levando em consideração os intervalos: <br>
- [65; 90]  para valores decimais da tabela ASCII de 'A' a 'Z' (letras maiúsculas) <br>
- [97; 122] para valores decimais da tabela ASCII de 'a' a 'z' (letras minúsculas) <br>
i.e., 26 letras.

-----------------------
#### PARA CRIPTOGRAFAR:
1. Enquanto existirem caracteres a serem lidos, seguir;
2. Ler 1 caractere do texto (a ser criptografado) para CH;
3. Se CH for um caractere alfabético, seguir. Caso contrário, voltar para _[1]_;
4. __f(X) = Y = CH + X__;
5. Enquanto Y for maior que o maior valor representável (90/122), fazer __Y = Y - 26__;
5. __Y = (( Y + 65 ) % 26) + 65__;
6. __CH = Y__;
7. Voltar para _[1]_;

--------------------------
#### PARA DESCRIPTOGRAFAR:
1. Enquanto existirem caracteres a serem lidos, seguir;
2. Ler 1 caractere do texto (a ser descriptografado) para CH;
3. Se CH for um caractere alfabético, seguir. Caso contrário, voltar para _[1]_;
4. __g(X) = Z = CH - X__;
5. Enquanto Z for menor que o menor valor representável (65/97), fazer __Z = Z + 26__;
6. __CH = Z__;
7. Voltar para _[1]_;
