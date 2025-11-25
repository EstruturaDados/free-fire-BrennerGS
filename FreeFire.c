
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre

#define MAX_COMPONENTES 10
#define TAM_NOME 30
#define TAM_TIPO 20

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos componentes
typedef enum {
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

// Enum AlgoritmoOrdenacao:
// Define os algoritmos de ordenação disponíveis
typedef enum {
    BUBBLE_SORT,
    INSERTION_SORT,
    SELECTION_SORT
} AlgoritmoOrdenacao;

// Struct Componente:
// Representa um componente com nome, tipo e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade; // 1-5 (1 = mais importante)
} Componente;

// Vetor mochila:
Componente mochila[MAX_COMPONENTES];
int numComponentes = 0;
int comparacoes = 0;
int trocas = 0;
bool ordenadaPorNome = false;

void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

void exibirMenu() {
    printf("\n=== SISTEMA DE CONSTRUCAO DA TORRE DE FUGA ===\n");
    printf("Componentes coletados: %d/%d\n", numComponentes, MAX_COMPONENTES);
    printf("Status ordenacao: %s\n", ordenadaPorNome ? "ORDENADA POR NOME" : "NAO ORDENADA");
    printf("1. Adicionar um componente\n");
    printf("2. Remover um componente\n");
    printf("3. Listar todos os componentes\n");
    printf("4. Ordenar componentes (escolher algoritmo e criterio)\n");
    printf("5. Realizar busca binaria por nome\n");
    printf("6. Ativar torre de fuga (buscar componente-chave)\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

void adicionarComponente() {
    if (numComponentes >= MAX_COMPONENTES) {
        printf("ERRO: Capacidade maxima atingida! Nao e possivel adicionar mais componentes.\n");
        return;
    }

    printf("\n=== ADICIONAR COMPONENTE ===\n");
    printf("Nome do componente: ");
    scanf("%s", mochila[numComponentes].nome);

    printf("Tipo (controle, suporte, propulsao, energia): ");
    scanf("%s", mochila[numComponentes].tipo);

    printf("Prioridade (1-5, onde 1 e mais importante): ");
    scanf("%d", &mochila[numComponentes].prioridade);

    numComponentes++;
    ordenadaPorNome = false;
    printf("Componente adicionado com sucesso!\n");
}

void removerComponente() {
    if (numComponentes == 0) {
        printf("ERRO: Nenhum componente disponivel para remover.\n");
        return;
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== REMOVER COMPONENTE ===\n");
    printf("Nome do componente a remover: ");
    scanf("%s", nomeBusca);

    int posicao = -1;
    for (int i = 0; i < numComponentes; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("ERRO: Componente nao encontrado.\n");
        return;
    }

    for (int i = posicao; i < numComponentes - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    numComponentes--;
    printf("Componente removido com sucesso!\n");
}

void listarComponentes() {
    if (numComponentes == 0) {
        printf("Nenhum componente coletado. Comece a explorar a ilha!\n");
        return;
    }

    printf("\n=== COMPONENTES COLETADOS ===\n");
    printf("-------------------------------------------------\n");
    printf("Nome                         | Tipo               | Prioridade\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < numComponentes; i++) {
        printf("%-28s | %-18s | %-9d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
    }

    printf("-------------------------------------------------\n");
}

void trocarComponentes(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

// Algoritmos de ordenação
void bubbleSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    trocas = 0;

    for (int i = 0; i < numComponentes - 1; i++) {
        for (int j = 0; j < numComponentes - 1 - i; j++) {
            comparacoes++;
            bool deveTrocar = false;

            switch (criterio) {
                case POR_NOME:
                    deveTrocar = strcmp(mochila[j].nome, mochila[j + 1].nome) > 0;
                    break;
                case POR_TIPO:
                    deveTrocar = strcmp(mochila[j].tipo, mochila[j + 1].tipo) > 0;
                    break;
                case POR_PRIORIDADE:
                    deveTrocar = mochila[j].prioridade > mochila[j + 1].prioridade;
                    break;
            }

            if (deveTrocar) {
                trocarComponentes(&mochila[j], &mochila[j + 1]);
            }
        }
    }
}

void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    trocas = 0;

    for (int i = 1; i < numComponentes; i++) {
        Componente chave = mochila[i];
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
                trocas++;
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

void selectionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    trocas = 0;

    for (int i = 0; i < numComponentes - 1; i++) {
        int indiceExtremo = i;

        for (int j = i + 1; j < numComponentes; j++) {
            comparacoes++;
            bool deveSelecionar = false;

            switch (criterio) {
                case POR_NOME:
                    deveSelecionar = strcmp(mochila[j].nome, mochila[indiceExtremo].nome) < 0;
                    break;
                case POR_TIPO:
                    deveSelecionar = strcmp(mochila[j].tipo, mochila[indiceExtremo].tipo) < 0;
                    break;
                case POR_PRIORIDADE:
                    deveSelecionar = mochila[j].prioridade < mochila[indiceExtremo].prioridade;
                    break;
            }

            if (deveSelecionar) {
                indiceExtremo = j;
            }
        }

        if (indiceExtremo != i) {
            trocarComponentes(&mochila[i], &mochila[indiceExtremo]);
        }
    }
}

void menuDeOrdenacao() {
    if (numComponentes < 2) {
        printf("ERRO: E necessario pelo menos 2 componentes para ordenar.\n");
        return;
    }

    printf("\n=== SELECAO DE ORDENACAO ===\n");
    printf("Algoritmos disponiveis:\n");
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("Escolha o algoritmo: ");

    int algoOpcao;
    scanf("%d", &algoOpcao);

    printf("\nCriterios de ordenacao:\n");
    printf("1. Por nome (ordem alfabetica)\n");
    printf("2. Por tipo (ordem alfabetica)\n");
    printf("3. Por prioridade (1 = mais importante)\n");
    printf("Escolha o criterio: ");

    int criterioOpcao;
    scanf("%d", &criterioOpcao);

    AlgoritmoOrdenacao algoritmo;
    CriterioOrdenacao criterio;
    char* algoritmoStr;
    char* criterioStr;

    // Definir algoritmo
    switch (algoOpcao) {
        case 1: algoritmo = BUBBLE_SORT; algoritmoStr = "Bubble Sort"; break;
        case 2: algoritmo = INSERTION_SORT; algoritmoStr = "Insertion Sort"; break;
        case 3: algoritmo = SELECTION_SORT; algoritmoStr = "Selection Sort"; break;
        default: printf("ERRO: Algoritmo invalido!\n"); return;
    }

    // Definir critério
    switch (criterioOpcao) {
        case 1: criterio = POR_NOME; criterioStr = "nome"; break;
        case 2: criterio = POR_TIPO; criterioStr = "tipo"; break;
        case 3: criterio = POR_PRIORIDADE; criterioStr = "prioridade"; break;
        default: printf("ERRO: Criterio invalido!\n"); return;
    }

    clock_t inicio = clock();

    // Executar algoritmo selecionado
    switch (algoritmo) {
        case BUBBLE_SORT:
            bubbleSort(criterio);
            break;
        case INSERTION_SORT:
            insertionSort(criterio);
            break;
        case SELECTION_SORT:
            selectionSort(criterio);
            break;
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    if (criterio == POR_NOME) {
        ordenadaPorNome = true;
    }

    printf("\n=== RESULTADO DA ORDENACAO ===\n");
    printf("Algoritmo: %s\n", algoritmoStr);
    printf("Criterio: %s\n", criterioStr);
    printf("Tempo de execucao: %.6f segundos\n", tempo);
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    printf("Componentes ordenados com sucesso!\n");
}

void buscaBinariaPorNome() {
    if (numComponentes == 0) {
        printf("ERRO: Nenhum componente disponivel para busca.\n");
        return;
    }

    if (!ordenadaPorNome) {
        printf("AVISO: Os componentes nao estao ordenados por nome.\n");
        printf("Deseja ordenar automaticamente? (1 = Sim, 0 = Nao): ");
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            insertionSort(POR_NOME);
            ordenadaPorNome = true;
        } else {
            printf("Busca cancelada. E necessario ordenar por nome primeiro.\n");
            return;
        }
    }

    char nomeBusca[TAM_NOME];
    printf("\n=== BUSCA BINARIA ===\n");
    printf("Nome do componente a buscar: ");
    scanf("%s", nomeBusca);

    comparacoes = 0;
    int inicio = 0;
    int fim = numComponentes - 1;
    bool encontrado = false;
    int posicao = -1;

    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, nomeBusca);

        if (resultado == 0) {
            encontrado = true;
            posicao = meio;
            break;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (encontrado) {
        printf("\nCOMPONENTE ENCONTRADO (posicao %d):\n", posicao);
        printf("Nome: %s\n", mochila[posicao].nome);
        printf("Tipo: %s\n", mochila[posicao].tipo);
        printf("Prioridade: %d\n", mochila[posicao].prioridade);
    } else {
        printf("Componente '%s' nao encontrado.\n", nomeBusca);
    }

    printf("Comparacoes realizadas: %d\n", comparacoes);
}

void ativarTorreFuga() {
    if (numComponentes == 0) {
        printf("ERRO: Nenhum componente coletado! Nao e possivel ativar a torre.\n");
        return;
    }

    printf("\n=== ATIVACAO DA TORRE DE FUGA ===\n");
    printf("A torre de fuga requer um COMPONENTE-CHAVE para ser ativada.\n");

    if (!ordenadaPorNome) {
        printf("Ordenando componentes por nome para busca otimizada...\n");
        insertionSort(POR_NOME);
        ordenadaPorNome = true;
    }

    char componenteChave[TAM_NOME];
    printf("Digite o nome do COMPONENTE-CHAVE: ");
    scanf("%s", componenteChave);

    comparacoes = 0;
    int inicio = 0;
    int fim = numComponentes - 1;
    bool componenteEncontrado = false;

    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(mochila[meio].nome, componenteChave);

        if (resultado == 0) {
            componenteEncontrado = true;
            break;
        } else if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("\n");
    if (componenteEncontrado) {
        printf("TORRE DE FUGA ATIVADA COM SUCESSO! \n");
        printf("Componente-chave '%s' verificado e validado.\n", componenteChave);
        printf("Comparacoes realizadas: %d\n", comparacoes);
        printf("\n INICIANDO SEQUENCIA DE FUGA...\n");
        printf("Voce escapou da ilha! Missao cumprida!\n");
    } else {
        printf("FALHA NA ATIVACAO DA TORRE!\n");
        printf("Componente-chave '%s' nao encontrado.\n", componenteChave);
        printf("Comparacoes realizadas: %d\n", comparacoes);
        printf("Continue explorando a ilha para encontrar o componente necessario.\n");
    }
}

int main() {
    printf("BEM-VINDO AO MODO SOBREVIVENCIA FREE FIRE - NIVEL MESTRE!\n");
    printf("Construa a torre de fuga com componentes estrategicos para escapar da ilha!\n");

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarComponente();
                break;
            case 2:
                removerComponente();
                break;
            case 3:
                listarComponentes();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 6:
                ativarTorreFuga();
                break;
            case 0:
                printf("\nSaindo do sistema de construcao da torre.\n");
                printf("Que a estrategia esteja com voce, sobrevivente!\n");
                break;
            default:
                printf("ERRO: Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
