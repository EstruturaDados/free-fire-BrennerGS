#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Aventureiro
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens
typedef enum {
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
    int prioridade; // 1-5 (1 = mais importante)
} Item;

// Vetor mochila:
Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

void exibirMenu() {
    printf("\n=== SISTEMA DE INVENTARIO AVANCADO ===\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX_ITENS);
    printf("Status ordenacao: %s\n", ordenadaPorNome ? "ORDENADA POR NOME" : "NAO ORDENADA");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens por criterio\n");
    printf("5. Realizar busca binaria por nome\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("ERRO: Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n=== ADICIONAR ITEM ===\n");
    printf("Nome do item: ");
    scanf("%s", mochila[numItens].nome);

    printf("Tipo (arma, municao, cura, ferramenta): ");
    scanf("%s", mochila[numItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);

    printf("Prioridade (1-5, onde 1 e mais importante): ");
    scanf("%d", &mochila[numItens].prioridade);

    numItens++;
    ordenadaPorNome = false; // Nova inserção desfaz a ordenação
    printf("Item adicionado com sucesso!\n");
}

void removerItem() {
    if (numItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Nome do item a remover: ");
    scanf("%s", nomeBusca);

    int posicao = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("ERRO: Item nao encontrado na mochila.\n");
        return;
    }

    for (int i = posicao; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numItens--;
    printf("Item removido com sucesso!\n");
}

void listarItens() {
    if (numItens == 0) {
        printf("Mochila vazia! Comece coletando recursos.\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA ===\n");
    printf("-----------------------------------------------------------------\n");
    printf("Nome                         | Tipo               | Quantidade | Prioridade\n");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < numItens; i++) {
        printf("%-28s | %-18s | %-10d | %-9d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }

    printf("-----------------------------------------------------------------\n");
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            bool deveMover = false;

            switch (criterio) {
                case POR_NOME:
                    deveMover = strcmp(mochila[j].nome, chave.nome) > 0;
                    break;
                case POR_TIPO:
                    deveMover = strcmp(mochila[j].tipo, chave.tipo) > 0;
                    break;
                case POR_PRIORIDADE:
                    deveMover = mochila[j].prioridade > chave.prioridade;
                    break;
            }

            if (deveMover) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }

    if (criterio == POR_NOME) {
        ordenadaPorNome = true;
    }
}

void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("ERRO: Nao ha itens para ordenar.\n");
        return;
    }

    printf("\n=== ORDENAR ITENS ===\n");
    printf("1. Ordenar por nome (ordem alfabetica)\n");
    printf("2. Ordenar por tipo (ordem alfabetica)\n");
    printf("3. Ordenar por prioridade (1 = mais importante)\n");
    printf("Escolha o criterio: ");

    int opcao;
    scanf("%d", &opcao);

    CriterioOrdenacao criterio;
    char* criterioStr;

    switch (opcao) {
        case 1:
            criterio = POR_NOME;
            criterioStr = "nome";
            break;
        case 2:
            criterio = POR_TIPO;
            criterioStr = "tipo";
            break;
        case 3:
            criterio = POR_PRIORIDADE;
            criterioStr = "prioridade";
            break;
        default:
            printf("ERRO: Criterio invalido!\n");
            return;
    }

    insertionSort(criterio);
    printf("Itens ordenados por %s!\n", criterioStr);
    printf("Comparacoes realizadas: %d\n", comparacoes);
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    if (numItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }

    if (!ordenadaPorNome) {
        printf("AVISO: A mochila nao esta ordenada por nome. Ordenando automaticamente...\n");
        insertionSort(POR_NOME);
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCA BINARIA ===\n");
    printf("Nome do item a buscar: ");
    scanf("%s", nomeBusca);

    comparacoes = 0;
    int inicio = 0;
    int fim = numItens - 1;
    bool encontrado = false;

    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, nomeBusca);

        if (resultado == 0) {
            printf("\nITEM ENCONTRADO (posicao %d):\n", meio);
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }

    printf("Comparacoes realizadas: %d\n", comparacoes);
}

int main() {
    printf("BEM-VINDO AO MODO SOBREVIVENCIA FREE FIRE - NIVEL AVENTUREIRO!\n");
    printf("Organize seus recursos estrategicamente para aumentar suas chances de fuga!\n");

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\nSaindo do sistema. Boa sorte na sua jornada!\n");
                break;
            default:
                printf("ERRO: Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
