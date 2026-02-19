#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// --- Definições ---
typedef struct {
  char nome[30];
  char tipo[20];
  int quantidade;
  int prioridade;
} Componente;
#define MAX_COMPONENTES 20
Componente torre[MAX_COMPONENTES];
int totalComponentes = 0;
long long comparacoes = 0; // Contador global de comparações
int ordenadoPorNome = 0;   // Flag para validar busca binária
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
void mostrarComponentes() {
  if (totalComponentes == 0) {
    printf("\n[AVISO] Nenhum componente na torre.\n");
    return;
  }
  printf("\n--- Componentes da Torre (%d/%d) ---\n", totalComponentes,
         MAX_COMPONENTES);
  printf("%-20s | %-15s | %-5s | %s\n", "Nome", "Tipo", "Qtd", "Prioridade");
  printf("----------------------------------------------------------------\n");
  for (int i = 0; i < totalComponentes; i++) {
    printf("%-20s | %-15s | %-5d | %d\n", torre[i].nome, torre[i].tipo,
           torre[i].quantidade, torre[i].prioridade);
  }
}
// --- Cadastro ---
void cadastrarComponente() {
  if (totalComponentes >= MAX_COMPONENTES) {
    printf("\n[ERRO] Capacidade maxima da torre atingida!\n");
    return;
  }
  Componente novo;
  printf("\n--- Novo Componente ---\n");
  printf("Nome (ex: 'Chip Central'): ");
  limparBuffer();
  fgets(novo.nome, sizeof(novo.nome), stdin);
  removerQuebraLinha(novo.nome);
  printf("Tipo (ex: 'Controle'): ");
  fgets(novo.tipo, sizeof(novo.tipo), stdin);
  removerQuebraLinha(novo.tipo);
  printf("Quantidade: ");
  scanf("%d", &novo.quantidade);
  printf("Prioridade (1-10): ");
  scanf("%d", &novo.prioridade);
  torre[totalComponentes] = novo;
  totalComponentes++;
  ordenadoPorNome = 0; // Nova inserção desordena
  printf("[SUCESSO] Componente cadastrado.\n");
}
// --- Algoritmos de Ordenação ---
// Bubble Sort: Ordenar por NOME
void bubbleSortNome() {
  comparacoes = 0;
  if (totalComponentes <= 1)
    return;
  for (int i = 0; i < totalComponentes - 1; i++) {
    for (int j = 0; j < totalComponentes - i - 1; j++) {
      comparacoes++;
      if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
        Componente temp = torre[j];
        torre[j] = torre[j + 1];
        torre[j + 1] = temp;
      }
    }
  }
  ordenadoPorNome = 1;
}
// Insertion Sort: Ordenar por TIPO
void insertionSortTipo() {
  comparacoes = 0;
  if (totalComponentes <= 1)
    return;
  for (int i = 1; i < totalComponentes; i++) {
    Componente chave = torre[i];
    int j = i - 1;
    // Comparações ocorrem dentro do while
    while (j >= 0) {
      comparacoes++;
      if (strcmp(torre[j].tipo, chave.tipo) > 0) {
        torre[j + 1] = torre[j];
        j = j - 1;
      } else {
        break;
      }
    }
    torre[j + 1] = chave;
  }
  ordenadoPorNome = 0;
}
// Selection Sort: Ordenar por PRIORIDADE
void selectionSortPrioridade() {
  comparacoes = 0;
  if (totalComponentes <= 1)
    return;
  for (int i = 0; i < totalComponentes - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < totalComponentes; j++) {
      comparacoes++;
      // Ordenação crescente de prioridade (1 é menor que 10)
      if (torre[j].prioridade < torre[min_idx].prioridade) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      Componente temp = torre[min_idx];
      torre[min_idx] = torre[i];
      torre[i] = temp;
    }
  }
  ordenadoPorNome = 0;
}
// --- Busca Binária ---
void buscaBinariaNome() {
  if (totalComponentes == 0) {
    printf("\n[AVISO] Torre vazia.\n");
    return;
  }
  if (!ordenadoPorNome) {
    printf("\n[ERRO] A lista precisa estar ordenada por NOME para a busca "
           "binaria.\n");
    printf("Execute a ordenacao por NOME (Bubble Sort) primeiro.\n");
    return;
  }
  char chave[30];
  printf("\n--- Busca Binaria (Componente Chave) ---\n");
  printf("Digite o nome do componente: ");
  limparBuffer();
  fgets(chave, sizeof(chave), stdin);
  removerQuebraLinha(chave);
  comparacoes = 0;
  int inicio = 0;
  int fim = totalComponentes - 1;
  int encontrado = 0;
  clock_t inicioTempo = clock();
  while (inicio <= fim) {
    comparacoes++;
    int meio = (inicio + fim) / 2;
    int cmp = strcmp(torre[meio].nome, chave);
    if (cmp == 0) {
      clock_t fimTempo = clock();
      double tempoGasto =
          ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC * 1000.0;
      printf("\n[ENCONTRADO] Componente Chave Localizado!\n");
      printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
             torre[meio].nome, torre[meio].tipo, torre[meio].quantidade,
             torre[meio].prioridade);
      printf("Comparacoes: %lld | Tempo: %.4f ms\n", comparacoes, tempoGasto);
      encontrado = 1;
      break;
    } else if (cmp < 0) {
      inicio = meio + 1;
    } else {
      fim = meio - 1;
    }
  }
  if (!encontrado) {
    clock_t fimTempo = clock();
    double tempoGasto =
        ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC * 1000.0;
    printf("\n[INFO] Componente '%s' nao encontrado.\n", chave);
    printf("Comparacoes: %lld | Tempo: %.4f ms\n", comparacoes, tempoGasto);
  }
}
// Wrapper para medir tempo de ordenação
void executarOrdenacao(int tipo) {
  if (totalComponentes == 0) {
    printf("\n[AVISO] Nada para ordenar.\n");
    return;
  }
  clock_t inicio = clock();
  switch (tipo) {
  case 1: // Bubble Sort (Nome)
    printf("\nExecutando Bubble Sort (Por Nome)...\n");
    bubbleSortNome();
    break;
  case 2: // Insertion Sort (Tipo)
    printf("\nExecutando Insertion Sort (Por Tipo)...\n");
    insertionSortTipo();
    break;
  case 3: // Selection Sort (Prioridade)
    printf("\nExecutando Selection Sort (Por Prioridade)...\n");
    selectionSortPrioridade();
    break;
  }
  clock_t fim = clock();
  double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
  mostrarComponentes();
  printf("\n--- Relatorio de Desempenho ---\n");
  printf("Comparacoes realizadas: %lld\n", comparacoes);
  printf("Tempo de execucao: %.4f ms\n", tempoGasto);
}
int main() {
  int opcao;
  do {
    printf("\n#############################################\n");
    printf("#       TORRE DE RESGATE - NIVEL 3          #\n");
    printf("#############################################\n");
    printf("1. Cadastrar Componente\n");
    printf("2. Ordenar por NOME (Bubble Sort)\n");
    printf("3. Ordenar por TIPO (Insertion Sort)\n");
    printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
    printf("5. Buscar Componente (Busca Binaria - Requer Nome Ordenado)\n");
    printf("6. Listar Componentes\n");
    printf("0. Sair\n");
    printf("Escolha uma estrategia: ");
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
      cadastrarComponente();
      break;
    case 2:
      executarOrdenacao(1);
      break;
    case 3:
      executarOrdenacao(2);
      break;
    case 4:
      executarOrdenacao(3);
      break;
    case 5:
      buscaBinariaNome();
      break;
    case 6:
      mostrarComponentes();
      break;
    case 0:
      printf("Encerrando missao...\n");
      break;
    default:
      printf("Opcao invalida!\n");
    }
  } while (opcao != 0);
  return 0;
}
