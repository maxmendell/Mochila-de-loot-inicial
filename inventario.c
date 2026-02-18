#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// --- Definições de Estruturas ---
typedef struct {
  char nome[30];
  char tipo[20];
  int quantidade;
} Item;
// Nó para a Lista Encadeada
typedef struct No {
  Item dado;
  struct No *proximo;
} No;
// --- Variáveis Globais para Vetor ---
#define CAPACIDADE_MAX 50
Item vetorMochila[CAPACIDADE_MAX];
int totalVetor = 0;
int vetorOrdenado = 0; // Flag para indicar se o vetor está ordenado
// --- Variáveis Globais para Lista Encadeada ---
No *listaMochila = NULL;
// --- Contadores de Desempenho ---
long long comparacoesSequencialVetor = 0;
long long comparacoesBinariaVetor = 0;
long long comparacoesSequencialLista = 0;
// --- Funções Auxiliares ---
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}
void removerQuebraLinha(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}
// --- Operações com VETOR ---
void inserirItemVetor() {
  if (totalVetor >= CAPACIDADE_MAX) {
    printf("\n[VETOR] Erro: Mochila cheia!\n");
    return;
  }
  Item novo;
  printf("\n--- Novo Item (Vetor) ---\n");
  printf("Nome: ");
  limparBuffer();
  fgets(novo.nome, sizeof(novo.nome), stdin);
  removerQuebraLinha(novo.nome);
  printf("Tipo: ");
  fgets(novo.tipo, sizeof(novo.tipo), stdin);
  removerQuebraLinha(novo.tipo);
  printf("Quantidade: ");
  scanf("%d", &novo.quantidade);
  vetorMochila[totalVetor] = novo;
  totalVetor++;
  vetorOrdenado = 0; // Inserção desordena o vetor
  printf("[VETOR] Item inserido com sucesso.\n");
}
void removerItemVetor() {
  if (totalVetor == 0) {
    printf("\n[VETOR] Erro: Mochila vazia.\n");
    return;
  }
  char nome[30];
  printf("\nNome do item a remover (Vetor): ");
  limparBuffer();
  fgets(nome, sizeof(nome), stdin);
  removerQuebraLinha(nome);
  int indice = -1;
  for (int i = 0; i < totalVetor; i++) {
    if (strcmp(vetorMochila[i].nome, nome) == 0) {
      indice = i;
      break;
    }
  }
  if (indice != -1) {
    // Shift para a esquerda
    for (int i = indice; i < totalVetor - 1; i++) {
      vetorMochila[i] = vetorMochila[i + 1];
    }
    totalVetor--;
    printf("[VETOR] Item '%s' removido.\n", nome);
  } else {
    printf("[VETOR] Item '%s' nao encontrado.\n", nome);
  }
}
void listarVetor() {
  if (totalVetor == 0) {
    printf("\n[VETOR] Mochila vazia.\n");
    return;
  }
  printf("\n--- Itens no Vetor (%d) ---\n", totalVetor);
  for (int i = 0; i < totalVetor; i++) {
    printf("[%d] %s (%s) - Qtd: %d\n", i, vetorMochila[i].nome,
           vetorMochila[i].tipo, vetorMochila[i].quantidade);
  }
}
void buscarSequencialVetor() {
  if (totalVetor == 0) {
    printf("\n[VETOR] Mochila vazia.\n");
    return;
  }
  char nome[30];
  printf("\nBuscar (Sequencial Vetor): ");
  limparBuffer();
  fgets(nome, sizeof(nome), stdin);
  removerQuebraLinha(nome);
  comparacoesSequencialVetor = 0;
  int encontrado = 0;
  for (int i = 0; i < totalVetor; i++) {
    comparacoesSequencialVetor++;
    if (strcmp(vetorMochila[i].nome, nome) == 0) {
      printf("\n[VETOR] ENCONTRADO: %s (%s) - Qtd: %d\n", vetorMochila[i].nome,
             vetorMochila[i].tipo, vetorMochila[i].quantidade);
      encontrado = 1;
      break;
    }
  }
  if (!encontrado)
    printf("[VETOR] Item nao encontrado.\n");
  printf("Comparacoes realizadas: %lld\n", comparacoesSequencialVetor);
}
// Bubble Sort para ordenar vetor por nome
void ordenarVetor() {
  if (totalVetor <= 1)
    return;
  for (int i = 0; i < totalVetor - 1; i++) {
    for (int j = 0; j < totalVetor - i - 1; j++) {
      if (strcmp(vetorMochila[j].nome, vetorMochila[j + 1].nome) > 0) {
        Item temp = vetorMochila[j];
        vetorMochila[j] = vetorMochila[j + 1];
        vetorMochila[j + 1] = temp;
      }
    }
  }
  vetorOrdenado = 1;
  printf("\n[VETOR] Ordenado com sucesso.\n");
}
void buscarBinariaVetor() {
  if (totalVetor == 0) {
    printf("\n[VETOR] Mochila vazia.\n");
    return;
  }
  if (!vetorOrdenado) {
    printf("\n[AVISO] O vetor precisa estar ordenado para busca binaria. "
           "Ordenando agora...\n");
    ordenarVetor();
  }
  char nome[30];
  printf("\nBuscar (Binaria Vetor): ");
  limparBuffer();
  fgets(nome, sizeof(nome), stdin);
  removerQuebraLinha(nome);
  comparacoesBinariaVetor = 0;
  int inicio = 0;
  int fim = totalVetor - 1;
  int encontrado = 0;
  while (inicio <= fim) {
    comparacoesBinariaVetor++;
    int meio = (inicio + fim) / 2;
    int cmp = strcmp(vetorMochila[meio].nome, nome);
    if (cmp == 0) {
      printf("\n[VETOR] ENCONTRADO: %s (%s) - Qtd: %d\n",
             vetorMochila[meio].nome, vetorMochila[meio].tipo,
             vetorMochila[meio].quantidade);
      encontrado = 1;
      break;
    } else if (cmp < 0) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }
  if (!encontrado)
    printf("[VETOR] Item nao encontrado.\n");
  printf("Comparacoes realizadas: %lld\n", comparacoesBinariaVetor);
}
// --- Operações com LISTA ENCADEADA ---
void inserirItemLista() {
  No *novoNo = (No *)malloc(sizeof(No));
  if (!novoNo) {
    printf("[LISTA] Erro de alocacao de memoria.\n");
    return;
  }
  printf("\n--- Novo Item (Lista) ---\n");
  printf("Nome: ");
  limparBuffer();
  fgets(novoNo->dado.nome, sizeof(novoNo->dado.nome), stdin);
  removerQuebraLinha(novoNo->dado.nome);
  printf("Tipo: ");
  fgets(novoNo->dado.tipo, sizeof(novoNo->dado.tipo), stdin);
  removerQuebraLinha(novoNo->dado.tipo);
  printf("Quantidade: ");
  scanf("%d", &novoNo->dado.quantidade);
  // Inserção no início para O(1)
  novoNo->proximo = listaMochila;
  listaMochila = novoNo;
  printf("[LISTA] Item inserido com sucesso.\n");
}
void removerItemLista() {
  if (listaMochila == NULL) {
    printf("\n[LISTA] Mochila vazia.\n");
    return;
  }
  char nome[30];
  printf("\nNome do item a remover (Lista): ");
  limparBuffer();
  fgets(nome, sizeof(nome), stdin);
  removerQuebraLinha(nome);
  No *atual = listaMochila;
  No *anterior = NULL;
  int encontrado = 0;
  while (atual != NULL) {
    if (strcmp(atual->dado.nome, nome) == 0) {
      if (anterior == NULL) {
        // Remover o primeiro nó
        listaMochila = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }
      free(atual);
      encontrado = 1;
      printf("[LISTA] Item '%s' removido.\n", nome);
      break;
    }
    anterior = atual;
    atual = atual->proximo;
  }
  if (!encontrado)
    printf("[LISTA] Item nao encontrado.\n");
}
void listarLista() {
  if (listaMochila == NULL) {
    printf("\n[LISTA] Mochila vazia.\n");
    return;
  }
  printf("\n--- Itens na Lista Encadeada ---\n");
  No *temp = listaMochila;
  int i = 0;
  while (temp != NULL) {
    printf("[%d] %s (%s) - Qtd: %d\n", i++, temp->dado.nome, temp->dado.tipo,
           temp->dado.quantidade);
    temp = temp->proximo;
  }
}
void buscarItemLista() {
  if (listaMochila == NULL) {
    printf("\n[LISTA] Mochila vazia.\n");
    return;
  }
  char nome[30];
  printf("\nBuscar (Sequencial Lista): ");
  limparBuffer();
  fgets(nome, sizeof(nome), stdin);
  removerQuebraLinha(nome);
  comparacoesSequencialLista = 0;
  No *temp = listaMochila;
  int encontrado = 0;
  while (temp != NULL) {
    comparacoesSequencialLista++;
    if (strcmp(temp->dado.nome, nome) == 0) {
      printf("\n[LISTA] ENCONTRADO: %s (%s) - Qtd: %d\n", temp->dado.nome,
             temp->dado.tipo, temp->dado.quantidade);
      encontrado = 1;
      break;
    }
    temp = temp->proximo;
  }
  if (!encontrado)
    printf("[LISTA] Item nao encontrado.\n");
  printf("Comparacoes realizadas: %lld\n", comparacoesSequencialLista);
}
// --- Menus ---
void menuVetor() {
  int opcao;
  do {
    printf("\n=== MOCHILA: VERSAO VETOR ===\n");
    printf("1. Inserir Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item (Sequencial)\n");
    printf("5. Ordenar Vetor\n");
    printf("6. Buscar Item (Binaria)\n");
    printf("0. Voltar ao Menu Principal\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      inserirItemVetor();
      break;
    case 2:
      removerItemVetor();
      break;
    case 3:
      listarVetor();
      break;
    case 4:
      buscarSequencialVetor();
      break;
    case 5:
      ordenarVetor();
      break;
    case 6:
      buscarBinariaVetor();
      break;
    case 0:
      break;
    default:
      printf("Opcao invalida.\n");
    }
  } while (opcao != 0);
}
void menuLista() {
  int opcao;
  do {
    printf("\n=== MOCHILA: VERSAO LISTA ENCADEADA ===\n");
    printf("1. Inserir Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens\n");
    printf("4. Buscar Item (Sequencial)\n");
    printf("0. Voltar ao Menu Principal\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      inserirItemLista();
      break;
    case 2:
      removerItemLista();
      break;
    case 3:
      listarLista();
      break;
    case 4:
      buscarItemLista();
      break;
    case 0:
      break;
    default:
      printf("Opcao invalida.\n");
    }
  } while (opcao != 0);
}
int main() {
  int escolha;
  do {
    printf("\n#############################################\n");
    printf("#   SISTEMA COMPARATIVO DE INVENTARIO       #\n");
    printf("#############################################\n");
    printf("1. Acessar Mochila VETOR\n");
    printf("2. Acessar Mochila LISTA ENCADEADA\n");
    printf("0. Sair\n");
    printf("Escolha a estrutura: ");
    scanf("%d", &escolha);
    switch (escolha) {
    case 1:
      menuVetor();
      break;
    case 2:
      menuLista();
      break;
    case 0:
      printf("Saindo...\n");
      break;
    default:
      printf("Opcao invalida.\n");
    }
  } while (escolha != 0);
  // Liberar memoria da lista antes de sair
  No *atual = listaMochila;
  while (atual != NULL) {
    No *temp = atual;
    atual = atual->proximo;
    free(temp);
  }
  return 0;
}