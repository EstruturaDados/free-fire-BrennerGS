#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define TAM_NOME 30
#define TAM_TIPO 20

// Struct para representar um item do inventário
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Variáveis globais
Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para cadastrar um novo item
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("ERRO: Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }

    printf("\n=== CADASTRAR NOVO ITEM ===\n");

    printf("Nome do item: ");
    scanf("%s", mochila[totalItens].nome);

    printf("Tipo (arma, municao, cura, ferramenta): ");
    scanf("%s", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Nome do item a remover: ");
    scanf("%s", nomeBusca);

    // Busca sequencial para encontrar o item
    int posicao = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("ERRO: Item nao encontrado na mochila.\n");
        return;
    }

    // Remove o item deslocando os elementos
    for (int i = posicao; i < totalItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    totalItens--;
    printf("Item removido com sucesso!\n");
}

// Função para listar todos os itens
void listarItens() {
    if (totalItens == 0) {
        printf("Mochila vazia! Comece coletando recursos.\n");
        return;
    }

    printf("\n=== ITENS NA MOCHILA (%d/%d) ===\n", totalItens, MAX_ITENS);
    printf("----------------------------------------------\n");
    printf("Nome                         | Tipo               | Quantidade\n");
    printf("----------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-28s | %-18s | %-10d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }

    printf("----------------------------------------------\n");
}

// Função de busca sequencial por nome
void buscarItem() {
    if (totalItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Nome do item a buscar: ");
    scanf("%s", nomeBusca);

    // Busca sequencial
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nITEM ENCONTRADO:\n");
            printf("   Nome: %s\n", mochila[i].nome);
            printf("   Tipo: %s\n", mochila[i].tipo);
            printf("   Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("ERRO: Item nao encontrado na mochila.\n");
    }
}

// Função para exibir o menu principal
void exibirMenu() {
    printf("\n=== SISTEMA DE INVENTARIO FREE FIRE ===\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    printf("BEM-VINDO AO MODO SOBREVIVENCIA FREE FIRE!\n");
    printf("Voce acabou de pousar na ilha. Organize seu inventario para sobreviver!\n");

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
                buscarItem();
                break;
            case 5:
                printf("\nFim do jogo! Boa sorte na ilha, sobrevivente!\n");
                break;
            default:
                printf("ERRO: Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 5);

    return 0;
}
