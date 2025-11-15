#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "hash_reserva.h"

//Inicializa todas as posiçoes da tabela com NULL
void inicializarTabela(TabelaHash* t) {
    int i;
    for (i = 0; i < TAM_TABELA; i++) {
        t->tabela[i] = NULL;
    }
}

//Função hash simples: resto da divisão pelo tamanho da tabela
int hash(int numeroConfirmacao) {
    return numeroConfirmacao % TAM_TABELA;
}

//Cria dinamicamente uma nova reserva (nó da lista ligada)
Reserva* criarReserva(int numero, const char* nome, const char* data, int quarto) {
    Reserva* novaReserva = (Reserva*)malloc(sizeof(Reserva));
    if (novaReserva == NULL) {
        printf("Erro ao alocar memoria para nova reserva.\n");
        return NULL;
    }

    novaReserva->numeroConfirmacao = numero;
    strncpy(novaReserva->nomeHospede, nome, sizeof(novaReserva->nomeHospede) - 1);
    novaReserva->nomeHospede[sizeof(novaReserva->nomeHospede) - 1] = '\0';

    strncpy(novaReserva->data, data, sizeof(novaReserva->data) - 1);
    novaReserva->data[sizeof(novaReserva->data) - 1] = '\0';

    novaReserva->numeroQuarto = quarto;
    novaReserva->proximo = NULL;

    return novaReserva;
}

//Insere a reserva na tabela, tratando colisões com lista ligada
int inserirReserva(TabelaHash* t, Reserva* r) {
    if(r == NULL) {
        return 0; // Falha na inserção
    }
    
    int indice = hash(r->numeroConfirmacao);

    //Verifica se já existealguma reserva com o mesmo número de confirmação
    Reserva* atual = t->tabela[indice];
    while (atual != NULL) {
        if (atual->numeroConfirmacao == r->numeroConfirmacao) {
            printf("Erro: Reserva com numero de confirmacao %d ja existe.\n", r->numeroConfirmacao);
            free(r); // Libera a memória alocada para a nova reserva
            return 0; // Falha na inserção
        }
        atual = atual->proximo;
    }

    //Insere no inicio da lista encadeada da posicao indice
    r->proximo = t->tabela[indice];
    t->tabela[indice] = r;

    return 1; // Sucesso na inserção
}

//Busca uma reserva pelo número de confirmação
Reserva* buscarReserva(TabelaHash* t, int numero) {
    int indice = hash(numero);
    Reserva* atual = t->tabela[indice];

    while (atual != NULL) {
        if (atual->numeroConfirmacao == numero) {
            return atual; // Reserva encontrada
        }
        atual = atual->proximo;
    }

    return NULL; // Reserva não encontrada
}

//Exclui uma reserva pelo número de confirmacao, tratando colisoes
int excluirReserva(TabelaHash* t, int numero) {
    int indice = hash(numero);
    Reserva* atual = t->tabela[indice];
    Reserva* anterior = NULL;

// Percorre a lista ligada na posição indice
    while (atual != NULL && atual->numeroConfirmacao != numero) {
        anterior = atual;
        atual = atual->proximo;
    }

    //se atual == Null, nao achou a reserva
    if (atual == NULL) {
        return 0; // Falha: nao encontrado
    }

    //Se anterior == NULL, a reserva a ser removida é a primeira da lista
    if (anterior == NULL) {
        t->tabela[indice] = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual); // Libera a memória da reserva removida
    return 1; // Sucesso na remoção
}

//Lista todas as reservas na tabela hash
void listarReservas(TabelaHash* t) {
    int i;
    printf("\n===== LISTA DE TODAS AS RESERVAS =====\n");
    for (i = 0; i < TAM_TABELA; i++) {
        printf("Indice %d:\n", i);
        Reserva* atual = t->tabela[i];

        if (atual == NULL) {
            printf("  (vazio)\n");
        }
            
        while (atual != NULL) {
            printf("  Numero de Confirmacao: %d\n", atual->numeroConfirmacao);
            printf("  Nome do Hospede: %s\n", atual->nomeHospede);
            printf("  Data da Reserva: %s\n", atual->data);
            printf("  Numero do Quarto: %d\n", atual->numeroQuarto);
            printf("---------------------------\n");
            atual = atual->proximo;
            }
        }
        printf("======================================\n");
    }

    //Funçao auxiliar para limpar o buffer de entrada quando necessario
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF){
    //apenas descarta os caracteres até o fim da linha
    }
}

void executarPrograma(void) {
    setlocale(LC_ALL, "Portuguese");

    TabelaHash tabela;
    inicializarTabela(&tabela);

    int opcao;

    do {
        printf("\n========== SISTEMA DE RESERVAS DO HOTEL (HASH TABLE) ==========\n");
        printf("1 - Adicionar reserva\n");
        printf("2 - Buscar reserva por numero de confirmacao\n");
        printf("3 - Excluir reserva\n");
        printf("4 - Listar todas as reservas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida! Tente novamente.\n");
            limparBuffer();
            continue;
        }

        switch (opcao) {

            case 1: {
                int numero, quarto;
                char nome[50];
                char data[11];

                printf("Numero de confirmacao: ");
                scanf("%d", &numero);

                printf("Nome do hospede (sem espacos): ");
                scanf("%49s", nome);

                printf("Data da reserva (dd/mm/aaaa): ");
                scanf("%10s", data);

                printf("Numero do quarto: ");
                scanf("%d", &quarto);

                Reserva* r = criarReserva(numero, nome, data, quarto);

                if (inserirReserva(&tabela, r)) {
                    printf("Reserva adicionada com sucesso!\n");
                } else {
                    free(r);
                }

                break;
            }

            case 2: {
                int numero;
                printf("Informe o numero de confirmacao: ");
                scanf("%d", &numero);

                Reserva* r = buscarReserva(&tabela, numero);

                if (r != NULL) {
                    printf("\nReserva encontrada:\n");
                    printf("Numero: %d | Hospede: %s | Data: %s | Quarto: %d\n",
                           r->numeroConfirmacao, r->nomeHospede,
                           r->data, r->numeroQuarto);
                } else {
                    printf("Reserva nao encontrada.\n");
                }

                break;
            }

            case 3: {
                int numero;
                printf("Informe o numero de confirmacao da reserva a excluir: ");
                scanf("%d", &numero);

                if (excluirReserva(&tabela, numero)) {
                    printf("Reserva excluida com sucesso!\n");
                } else {
                    printf("Nenhuma reserva encontrada com esse numero.\n");
                }

                break;
            }

            case 4:
                listarReservas(&tabela);
                break;

            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);
}

