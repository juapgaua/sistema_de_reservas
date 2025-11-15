#ifndef HASH_RESERVA_H
#define HASH_RESERVA_H

#include <stdio.h>

//Tamanho da tabela hash
#define TAM_TABELA 10

//Estrutura que representa uma reserva
typedef struct Reserva {
    int numeroConfirmacao; //chave da reserva
    char nomeHospede[50]; //nome do hospede
    char data[11]; //data da reserva no formato "DD/MM/AAAA"
    int numeroQuarto; //numero do quarto reservado
    struct Reserva* proximo; //ponteiro para tratar colisões (lista ligada)
}Reserva;

//Estrutura que representa a tabela hash
typedef struct {
    Reserva* tabela[TAM_TABELA]; //array de ponteiros para reservas
}TabelaHash;

//Protótipos das funções básicas da tabela hash
void inicializarTabela(TabelaHash* t);
int hash(int nuimeroConfirmacao);
Reserva* criarReserva(int numero, const char* nome, const char* data, int quarto);
int inserirReserva(TabelaHash* t, Reserva* r);
Reserva* buscarReserva(TabelaHash* t, int numero);
int excluirReserva(TabelaHash* t, int numero);
void listarReservas(TabelaHash* t);

//Funçao que contem o menu e a interação com o usuário
void executarPrograma(void);

#endif //HASH_RESERVA_H