#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// Aqui eu só represento a peça com tipo e id.
// O tipo vai ser um desses: I, O, T ou L.
// O id é só pra saber qual foi criada antes ou depois.
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura básica da fila circular.
// A lógica é a mesma do nível novato, só reaproveitei.
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Estrutura da pilha, usada pra guardar peças reservadas.
typedef struct {
    Peca itens[MAX_PILHA];
    int topo; // começa em -1 pra indicar que está vazia
} Pilha;


// ----------- Funções da Fila -----------

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

// Gera automaticamente uma nova peça.
// Só escolhe um tipo aleatório e coloca o id sequencial.
Peca gerarPeca(int id) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;
    return p;
}

void inserirFila(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nA fila está cheia, não dá pra inserir agora.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

Peca removerFila(Fila *f) {
    Peca vazia = {'-', -1};

    if (filaVazia(f)) {
        printf("\nA fila está vazia, nada pra remover.\n");
        return vazia;
    }

    Peca retirada = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;

    return retirada;
}

void mostrarFila(Fila *f) {
    printf("\nFila de peças: ");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int i = f->inicio;
    for (int c = 0; c < f->total; c++) {
        printf("[%c %d] ", f->itens[i].tipo, f->itens[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}


// ----------- Funções da Pilha -----------

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Coloca peça no topo da pilha
void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("\nA pilha está cheia, não dá pra reservar mais nada.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = x;
}

// Remove peça do topo da pilha
Peca pop(Pilha *p) {
    Peca vazia = {'-', -1};

    if (pilhaVazia(p)) {
        printf("\nA pilha está vazia, não tem peça reservada.\n");
        return vazia;
    }

    return p->itens[p->topo--];
}

// Mostra a pilha no formato "Topo -> Base"
void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");

    if (pilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}


// ----------- PROGRAMA PRINCIPAL -----------

int main() {

    Fila fila;
    Pilha reserva;

    inicializarFila(&fila);
    inicializarPilha(&reserva);

    srand(time(NULL));

    int opcao;
    int id = 0;

    // Preenche a fila inicial com 5 peças, como manda o PDF.
    for (int i = 0; i < MAX_FILA; i++) {
        inserirFila(&fila, gerarPeca(id++));
    }

    do {
        printf("\n===== ESTADO ATUAL =====\n");
        mostrarFila(&fila);
        mostrarPilha(&reserva);

        printf("\n===== MENU - NÍVEL AVENTUREIRO =====\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            // Jogar peça da fila
            Peca jogada = removerFila(&fila);
            if (jogada.id != -1) {
                printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);

                // Reposição automática
                inserirFila(&fila, gerarPeca(id++));
            }
        }

        else if (opcao == 2) {
            // Reservar peça
            Peca retirada = removerFila(&fila);
            if (retirada.id != -1) {
                printf("\nPeça reservada: [%c %d]\n", retirada.tipo, retirada.id);
                push(&reserva, retirada);

                // repõe automaticamente
                inserirFila(&fila, gerarPeca(id++));
            }
        }

        else if (opcao == 3) {
            // Usar peça da pilha
            Peca usada = pop(&reserva);
            if (usada.id != -1) {
                printf("\nPeça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
            }
        }

    } while (opcao != 0);

    printf("\nEncerrando programa...\n");
    return 0;
}
