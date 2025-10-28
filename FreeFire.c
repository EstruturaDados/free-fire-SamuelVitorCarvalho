#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Aventureiro
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_STR_NOME 30
#define MAX_STR_TIPO 20
#define TAM_MAX 10

typedef struct {
    char nome[MAX_STR_NOME];
    char tipo[MAX_STR_TIPO];
    int quantidade;
} Item;

typedef struct {
    Item itens[TAM_MAX];
    int totalItens;
} Mochila;

void inicializarMochila(Mochila *mochila);
void cadastrarItem(Mochila *mochila);
void removerItem(Mochila *mochila);
void listarItens(Mochila *mochila);
void buscarItem(Mochila *mochila);
int buscarSequencial(Mochila *mochila, const char *nome);
void exibirMenu();

int main() {
    Mochila mochila;
    inicializarMochila(&mochila);
    int opcao;

    printf("==========================================\n");
    printf("   MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("==========================================\n");
    printf("Itens na Mochila: %d/%d\n\n", mochila.totalItens, TAM_MAX);

    do {
        exibirMenu();
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarItem(&mochila);
                break;
            case 2:
                removerItem(&mochila);
                break;
            case 3:
                listarItens(&mochila);
                break;
            case 4:
                buscarItem(&mochila);
                break;
            case 0:
                printf("Saindo do jogo. Boa sorte na ilha!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
            printf("\n");
        }
    } while (opcao != 0);

    return 0;
}

void inicializarMochila(Mochila *mochila) {
    mochila->totalItens = 0;
}

void exibirMenu() {
    printf("1 - Adicionar Item (Loot)\n");
    printf("2 - Remover Item\n");
    printf("3 - Listar Itens na Mochila\n");
    printf("4 - Buscar Item especifico\n");
    printf("0 - Sair\n");
}

void cadastrarItem(Mochila *mochila) {
    if (mochila->totalItens >= TAM_MAX) {
        printf("\n[ERRO] Mochila cheia! Capacidade maxima de %d itens atingida.\n", TAM_MAX);
        return;
    }

    Item novoItem;

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novoItem.nome);
    
    printf("Tipo do item (ex: arma, municao, cura, etc.): ");
    scanf(" %[^\n]", novoItem.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila->itens[mochila->totalItens] = novoItem;
    mochila->totalItens++;
    printf("\nItem '%s' adicionado com sucesso!\n", novoItem.nome);
    
    listarItens(mochila);
}

void removerItem(Mochila *mochila) {
    if (mochila->totalItens == 0) {
        printf("\nMochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeItem[MAX_STR_NOME];
    printf("\n=== REMOVER ITEM ===\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeItem);

    int indice = buscarSequencial(mochila, nomeItem);
    
    if (indice == -1) {
        printf("\n[ERRO] Item '%s' nao encontrado na mochila.\n", nomeItem);
        return;
    }

    // Remover item - deslocar elementos
    for (int i = indice; i < mochila->totalItens - 1; i++) {
        mochila->itens[i] = mochila->itens[i + 1];
    }
    
    mochila->totalItens--;
    printf("\nItem '%s' removido da mochila!\n", nomeItem);
    
    listarItens(mochila);
}

void listarItens(Mochila *mochila) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", mochila->totalItens, TAM_MAX);
    printf("\n--------------------------------------------------\n");
    
    if (mochila->totalItens == 0) {
        printf("Mochila vazia! Colete alguns itens na ilha.\n");
        return;
    }

    printf("%-25s | %-15s | %s\n", "NOME", "TIPO", "QTD");
    printf("--------------------------+-----------------+-----\n");
    
    for (int i = 0; i < mochila->totalItens; i++) {
        printf("%-25s | %-15s | %d\n",
               mochila->itens[i].nome,
               mochila->itens[i].tipo, 
               mochila->itens[i].quantidade);
    }
    printf("\n");
}

void buscarItem(Mochila *mochila) {
    if (mochila->totalItens == 0) {
        printf("\n[INFO] Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeItem[MAX_STR_NOME];
    printf("\n=== BUSCAR ITEM ===\n");
    printf("Digite o nome do item a ser buscado: ");
    scanf(" %[^\n]", nomeItem);

    int indice = buscarSequencial(mochila, nomeItem);
    
    if (indice == -1) {
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeItem);
    } else {
        printf("\nItem encontrado!\n");
        printf("Posicao na mochila: %d\n", indice + 1);
        printf("Nome: %s\n", mochila->itens[indice].nome);
        printf("Tipo: %s\n", mochila->itens[indice].tipo);
        printf("Quantidade: %d\n", mochila->itens[indice].quantidade);
    }
}

int buscarSequencial(Mochila *mochila, const char *nome) {
    for (int i = 0; i < mochila->totalItens; i++) {
        if (strcmp(mochila->itens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}
