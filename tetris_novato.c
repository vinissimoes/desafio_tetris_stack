#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5   // Tamanho máximo da fila (fila circular)


// Estrutura que representa uma peça

typedef struct {
    char tipo;  // I, O, T ou L
    int id;     // identificador único da peça
} Peca;


// Estrutura da fila circular

typedef struct {
    Peca itens[MAX];
    int inicio;  // posição de remoção
    int fim;     // posição de inserção
    int total;   // quantidade de elementos na fila
} Fila;



// Inicializa a fila vazia

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}


// Verifica se a fila está cheia

int filaCheia(Fila *f) {
    return f->total == MAX;
}


// Verifica se a fila está vazia

int filaVazia(Fila *f) {
    return f->total == 0;
}


// Gera automaticamente uma peça nova

Peca gerarPeca(int id) {
    char tipos[4] = {'I','O','T','L'};

    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = id;

    return p;
}


// Insere uma peça no final da fila

void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n⚠️  A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;  // lógica circular
    f->total++;
}


// Remove peça do início (jogar peça)

Peca jogarPeca(Fila *f) {
    Peca vazia = {'-', -1};

    if (filaVazia(f)) {
        printf("\n⚠️  A fila está vazia! Nenhuma peça para jogar.\n");
        return vazia;
    }

    Peca retirada = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX; // lógica circular
    f->total--;

    return retirada;
}


// Mostra todas as peças da fila

void mostrarFila(Fila *f) {
    printf("\nFila de peças: ");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int idx = f->inicio;

    for (int i = 0; i < f->total; i++) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX;
    }

    printf("\n");
}


// Programa Principal

int main() {

    Fila fila;
    inicializarFila(&fila);

    srand(time(NULL)); // para gerar peças aleatórias

    int opcao;
    int id = 0; // contador de peças criadas

    // Preenche fila inicial com 5 peças (fila cheia)
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca(id++));
    }

    // Loop do menu
    do {
        mostrarFila(&fila);

        printf("\n=== MENU - TETRIS NÍVEL NOVATO ===\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha sua opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = jogarPeca(&fila);

            if (jogada.id != -1) {
                printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);
            }
        }
        else if (opcao == 2) {
            inserir(&fila, gerarPeca(id++));
        }

    } while (opcao != 0);

    printf("\nEncerrando programa...\n");
    return 0;
}
