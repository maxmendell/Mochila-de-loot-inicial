#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Definição da struct Item: armazena informações de cada objeto no inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;
// Vetor para armazenar até 10 itens (capacidade da mochila)
Item mochila[10];
// Variável global para controlar a quantidade atual de itens na mochila
int totalItens = 0;
// Função auxiliar para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Função para remover a quebra de linha ('\n') do final de strings lidas com fgets
void removerQuebraLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}
// Função para cadastrar um novo item na mochila
void inserirItem() {
    if (totalItens >= 10) {
        printf("\n[ERRO] A mochila esta cheia! Remova algum item antes de adicionar novos.\n");
        return;
    }
    Item novoItem;
    printf("\n--- Cadastrar Novo Item ---\n");
    
    printf("Nome do item: ");
    limparBuffer(); // Garante buffer limpo antes de ler string
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    removerQuebraLinha(novoItem.nome);
    printf("Tipo do item (ex: arma, municao, cura): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    removerQuebraLinha(novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    // Adiciona o item ao vetor a incrementa contador
    mochila[totalItens] = novoItem;
    totalItens++;
    printf("[SUCESSO] Item '%s' adicionado a mochila.\n", novoItem.nome);
}
// Função para listar todos os itens cadastrados
void listarItens() {
    if (totalItens == 0) {
        printf("\n--- Mochila Vazia ---\n");
        return;
    }
    printf("\n--- Conteudo da Mochila (%d/10) ---\n", totalItens);
    printf("%-5s | %-20s | %-15s | %s\n", "ID", "Nome", "Tipo", "Qtd");
    printf("----------------------------------------------------------\n");
    
    for (int i = 0; i < totalItens; i++) {
        printf("%-5d | %-20s | %-15s | %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}
// Função para buscar um item pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("\n[AVISO] A mochila esta vazia. Nada para buscar.\n");
        return;
    }
    char termoBusca[30];
    printf("\n--- Buscar Item ---\n");
    printf("Digite o nome do item: ");
    limparBuffer();
    fgets(termoBusca, sizeof(termoBusca), stdin);
    removerQuebraLinha(termoBusca);
    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        // Comparação de strings ignorando maiúsculas/minúsculas poderia ser feita, 
        // mas strcmp é padrão C para busca exata.
        if (strcmp(mochila[i].nome, termoBusca) == 0) {
            printf("\n[ITEM ENCONTRADO]\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break; // Para a busca após encontrar
        }
    }
    if (!encontrado) {
        printf("[INFO] Item '%s' nao encontrado na mochila.\n", termoBusca);
    }
}
// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("\n[AVISO] A mochila esta vazia. Nada para remover.\n");
        return;
    }
    char nomeRemover[30];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    limparBuffer();
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    removerQuebraLinha(nomeRemover);
    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        // Remove o item deslocando os elementos subsequentes para a esquerda
        // Ex: [A, B, C, D] -> Remover B (índice 1) -> [A, C, D, D] -> total-- -> [A, C, D]
        for (int i = encontrado; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("[SUCESSO] Item '%s' removido da mochila.\n", nomeRemover);
    } else {
        printf("[ERRO] Item '%s' nao encontrado.\n", nomeRemover);
    }
}
int main() {
    int opcao;
    do {
        printf("\n=== SISTEMA DE INVENTARIO: MOCHILA DE LOOT ===\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch(opcao) {
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
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}
