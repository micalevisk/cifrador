# MiCodier
Copyright (c) 2016 Micael Levi L. Cavalcante

---

## Objetivo do programa
Codificar/Decodificar caracteres alfabéticos a partir de uma **chave**. <br>
Existem duas opções de criptografia:<br>
1. __Lógica de deslocamento__ <br>
A chave deve ser um número natural que esteja definida no intervalo fechado _[0, 65535]_, ou seja, temos 65.536 opções de chave para esta lógica porém esse número é reduzido a _26_ devido a [artimética modular](https://pt.wikipedia.org/wiki/Aritm%C3%A9tica_modular). <br>
Tendo em mente que os caracteres do alfabeto estão dispostos sequencialmente em um vetor em artitmética modular de _26_ posições iniciando com a letra 'A' e terminando com a letra 'Z', i.e., a primeira letra está na posição _0_ do vetor e a última está na posição _25_. <br>
Tomamos a primeira letra e somamos com a chave, assim, a primeira letra do alfabeto corresponderá a letra da posição indicada pela chave. Ou seja, a chave será a posição (no vetor) da letra 'A' codificada e com isso as outras letras vão sendo "deslocadas" de acordo com a primeira letra. <br>
**e.g.:** Se chave = 2 então a letra 'A' codificada será 'C' (que é a letra da posição 2 do vetor), a letra 'B' codificada será 'D' e assim sucessivamente. Como mostra a tabela:

| Original  | Codificada|
| ----------|-----------|
| A         | C         |
| B         | D         |
| C         | E         |
| (...)     | (...)     |
| Z         | B         |

2. __Lógica da [Cifra de César](https://pt.wikipedia.org/wiki/Cifra_de_C%C3%A9sar)__ <br>
A chave deve ser uma letra do alfabeto, ou seja, temos 26 opções únicas de chave para esta lógica. <br>
Esta chave indicará qual a será a letra codificada do caractere 'A'. Assim, as letras subsequentes (ordem alfabética) são "deslocadas" de acordo com a chave. <br>
**e.g.:** Se chave = 'D' então a letra 'A' codificada será 'D' (que é a chave), a letra 'B' codificada será 'E' e assim sucessivamente. Como mostra a tabela:<br>

| Original  | Codificada|
| ----------|-----------|
| A         | D         |
| B         | E         |
| C         | F         |
| (...)     | (...)     |
| Z         | C         |
