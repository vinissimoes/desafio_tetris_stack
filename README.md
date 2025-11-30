Projeto Tetris – Estruturas de Dados (Fila e Pilha)

Esse repositório contém os três níveis do meu projeto de Estrutura de Dados, onde eu fui evoluindo a lógica do Tetris conforme os requisitos de cada etapa. O foco principal é treinar o uso de fila circular, pilha, structs e a interação entre essas estruturas.

Eu tentei escrever tudo da forma mais simples e clara possível, porque a ideia foi realmente aprender mexendo.



 
 NIVEL NOVATO – tetris_novato.c

No primeiro nível eu trabalhei só com uma fila circular de peças.
Cada peça tem:

um tipo (I, O, T ou L)

um ID que cresce conforme as peças vão sendo criadas

Funcionalidades desse nível:

gerar peça nova automaticamente

inserir na fila (enqueue)

remover da fila (jogar peça)

mostrar o estado atual da fila

manter o tamanho máximo da fila

Esse nível é basicamente a base de tudo: entender como a fila circular funciona e como controlar o ponteiro de início, fim e o total.



NIVEL AVENTUREIRO – tetris_aventureiro.c

Aqui eu evoluí o programa adicionando uma pilha de peças reservadas.
A fila continua funcionando igual, mas agora temos:

Novas operações:

reservar peça (tirar da fila e colocar no topo da pilha)

usar peça reservada (tirar do topo da pilha)

continuar gerando novas peças automaticamente para a fila não ficar vazia

mostrar tanto a fila quanto a pilha no terminal

Esse nível foi o que conectou duas estruturas de dados diferentes e me fez pensar melhor no fluxo entre elas.



NIVELMESTRE – tetris_mestre.c

Esse foi o nível mais completo. Além de manter tudo dos níveis anteriores, aqui eu adicionei duas operações novas que exigem a interação direta entre fila e pilha:


- Troca simples

Troca a peça da frente da fila com a peça do topo da pilha.

- Troca múltipla

Troca os 3 primeiros elementos da fila com as 3 peças da pilha, na ordem certinha.
Só funciona quando realmente existem 3 peças em cada estrutura.

Continuam funcionando:

jogar peça

reservar

usar peça da reserva

mostrar fila e pilha

reposição automática da fila

Esse nível juntou tudo e deixou o programinha bem completo, simulando um mini gerenciador de peças do Tetris usando estruturas de dados clássicas.



Compilando: 

No terminal:

gcc arquivo.c -o programa
./programa


Exemplo:

gcc tetris_mestre.c -o mestre
./mestre
