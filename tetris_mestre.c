#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Estrutura que representa uma peça

typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;    // identificador sequencial
} Peca;


// Fila circular

typedef struct {
    Peca itens[MAX_FILA];
    int inicio; // índice do primeiro elemento
    int fim;    // índice onde insere o próximo
    int total;  // quantos elementos tem
} Fila;


// Pilha simples

typedef struct {
    Peca itens[MAX_PILHA];
    int topo; // -1 quando vazia
} Pilha;


// ----------- Funções da fila ------------

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

// Insere no final (enqueue)
void inserirFila(Fila *f, Peca p) {
    if (filaCheia(f)) {
        // Não deveria acontecer se usamos reposição automática corretamente,
        // mas deixo a checagem por segurança.
        printf("\nAviso: fila cheia. Não foi possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

// Remove do início (dequeue) e retorna a peça removida.
// Se vazia, retorna peça com id = -1.
Peca removerFila(Fila *f) {
    Peca vazio = {'-', -1};
    if (filaVazia(f)) {
        printf("\nAviso: fila vazia. Nada para remover.\n");
        return vazio;
    }
    Peca ret = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
    return ret;
}

// Mostra fila na ordem do início até o fim (respeitando circularidade)
void mostrarFila(Fila *f) {
    printf("Fila de peças: ");
    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
    }
    printf("\n");
}


// ----------- Funções da pilha ------------

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("\nAviso: pilha cheia. Não foi possível empilhar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca vazio = {'-', -1};
    if (pilhaVazia(p)) {
        printf("\nAviso: pilha vazia. Nada para usar.\n");
        return vazio;
    }
    Peca ret = p->itens[p->topo];
    p->topo--;
    return ret;
}

// Mostra pilha no formato "Topo -> base"
void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}


// ----------- Gerador de peças ------------

// Gera peça com tipo aleatório e id passado
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}


// ----------- Operações de troca ------------

// Troca simples: troca a peça da frente da fila com o topo da pilha.
// Retorna 1 se troca feita, 0 caso não seja possível.
int trocaSimples(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("\nNão há peça na fila para trocar.\n");
        return 0;
    }
    if (pilhaVazia(p)) {
        printf("\nNão há peça na pilha para trocar.\n");
        return 0;
    }

    // índice do primeiro elemento na fila
    int idxFila = f->inicio;
    // topo da pilha é p->topo
    Peca tmp = f->itens[idxFila];
    f->itens[idxFila] = p->itens[p->topo];
    p->itens[p->topo] = tmp;

    return 1;
}

// Troca múltipla: troca os 3 primeiros elementos da fila (na ordem atual)
// com as 3 peças da pilha (Topo -> base).
// Só permite se fila tiver >=3 e pilha tiver >=3.
// Retorna 1 se troca feita, 0 caso contrário.
int trocaTripla(Fila *f, Pilha *p) {
    if (f->total < 3) {
        printf("\nA fila precisa ter pelo menos 3 peças para a troca múltipla.\n");
        return 0;
    }
    if (p->topo + 1 < 3) {
        printf("\nA pilha precisa ter pelo menos 3 peças para a troca múltipla.\n");
        return 0;
    }

    // Vamos trocar: os 3 primeiros da fila (ordem do início) com
    // as 3 peças da pilha: topo, topo-1, topo-2 (nessa ordem).
    // A ideia do PDF é que as peças vindas da pilha ocupem as 3 primeiras posições da fila,
    // e as peças da fila vão para a pilha preservando a ordem de topo->base.
    // Implementação simples: trocamos elemento a elemento:
    // fila[inicio + 0] <-> pilha[topo]
    // fila[inicio + 1] <-> pilha[topo-1]
    // fila[inicio + 2] <-> pilha[topo-2]

    int idx = f->inicio;
    for (int k = 0; k < 3; k++) {
        int idxFila = (f->inicio + k) % MAX_FILA;
        int idxPilha = p->topo - k; // topo, topo-1, topo-2
        Peca tmp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[idxPilha];
        p->itens[idxPilha] = tmp;
    }

    return 1;
}


// ----------- Programa principal ------------

int main() {
    Fila fila;
    Pilha reserva;

    inicializarFila(&fila);
    inicializarPilha(&reserva);

    srand((unsigned int) time(NULL));

    int id = 0; // contador de ids (0,1,2,...)
    int opcao;

    // Preenche fila inicial com 5 peças (como pede o PDF)
    for (int i = 0; i < MAX_FILA; i++) {
        inserirFila(&fila, gerarPeca(id++));
    }

    // Exemplo: podemos pré-popular a pilha se quisermos (não é obrigatório)
    // mas o PDF não pede pré-população, então deixamos vazia no começo.

    do {
        printf("\n===== ESTADO ATUAL =====\n");
        mostrarFila(&fila);
        mostrarPilha(&reserva);

        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha a opção: ");
        if (scanf("%d", &opcao) != 1) {
            // entrada inválida: limpa stdin e continua
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            opcao = -1;
        }

        if (opcao == 1) {
            // Jogar peça: remove da frente da fila. Reposiciona uma nova peça no final.
            Peca jogada = removerFila(&fila);
            if (jogada.id != -1) {
                printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                // reposição automática para manter fila cheia (quando possível)
                inserirFila(&fila, gerarPeca(id++));
            }
        }

        else if (opcao == 2) {
            // Reservar peça: move a peça da frente da fila para o topo da pilha, se houver espaço
            if (pilhaCheia(&reserva)) {
                printf("\nNão há espaço na pilha de reserva para guardar essa peça.\n");
            } else {
                Peca retirada = removerFila(&fila);
                if (retirada.id != -1) {
                    push(&reserva, retirada);
                    printf("\nPeça enviada para reserva: [%c %d]\n", retirada.tipo, retirada.id);
                    // reposição automática na fila
                    inserirFila(&fila, gerarPeca(id++));
                }
            }
        }

        else if (opcao == 3) {
            // Usar peça reservada: pop da pilha (essa peça é removida do jogo)
            Peca usada = pop(&reserva);
            if (usada.id != -1) {
                printf("\nPeça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
                // NÃO repomos a pilha nem a fila aqui, pois usar da pilha não remove da fila
                // (somente removemos quando tiramos da fila ou quando enviamos para a pilha)
            }
        }

        else if (opcao == 4) {
            // Troca simples: troca a frente da fila com o topo da pilha
            if (trocaSimples(&fila, &reserva)) {
                printf("\nTroca simples realizada entre frente da fila e topo da pilha.\n");
                // trocas não geram novas peças, pois não houve remoção permanente
            }
        }

        else if (opcao == 5) {
            // Troca múltipla de 3
            if (trocaTripla(&fila, &reserva)) {
                printf("\nTroca múltipla (3 peças) realizada com sucesso.\n");
            }
        }

        else if (opcao == 0) {
            // sai do loop
            printf("\nEncerrando programa...\n");
        }

        else {
            printf("\nOpção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
