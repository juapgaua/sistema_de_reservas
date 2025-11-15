## Sistema de Reservas com Tabela Hash em C

Aplicacao em C que simula um sistema de reservas de hotel utilizando Tabela Hash com tratamento de colisoes por encadeamento separado.  
O programa permite adicionar, buscar, listar e excluir reservas, controladas por numero de confirmacao.

## Funcionalidades

- Inserir nova reserva
- Buscar reserva por numero de confirmacao
- Excluir reserva
- Listar todas as reservas da tabela
- Tratamento de colisoes utilizando listas ligadas
- Menu interativo
- Estrutura separada em:
  - hash_reserva.h
  - hash_reserva.c
  - main.c

## Estrutura do Projeto
```bash
/projeto-reservas-hash
│
├── hash_reserva.h       // Arquivo header com definicoes e prototipos
├── hash_reserva.c       // Implementacao da tabela hash e operacoes
└── main.c               // Chama apenas executarPrograma()
```

## Conceitos Trabalhados

Este projeto aborda conceitos fundamentais de Estruturas de Dados e TAD:

- Tabela Hash
- Funcao hash
- Tratamento de colisoes (encadeamento separado)
- Listas ligadas
- Modularizacao em C (.h, .c e main)
- Manipulacao dinamica de memoria
- Desenvolvimento de TAD (Tipo Abstrato de Dado)

## Como funciona o tratamento de colisoes

A funcao hash utilizada:
  indice = numeroConfirmacao % TAM_TABELA;  
  Quando duas reservas caem no mesmo indice, elas sao organizadas em lista ligada, garantindo que todos os elementos possam ser acessados, buscados e removidos corretamente.

## Como compilar

```bash
gcc hash_reserva.c main.c -o hotel
```

Executar:
```bash
./hotel
```


## Exemplo de Uso

<img width="777" height="287" alt="image" src="https://github.com/user-attachments/assets/a8dd5d61-6a31-490e-a180-91c8c71f1517" />  

<img width="478" height="829" alt="image" src="https://github.com/user-attachments/assets/64ae4715-8a10-4c26-b188-6ed1eb11c02d" />  

<img width="783" height="295" alt="image" src="https://github.com/user-attachments/assets/fd8bfd0b-24c1-4d7b-a156-f04e9e0b8d20" />  

<img width="774" height="217" alt="image" src="https://github.com/user-attachments/assets/38d65f6b-fcfe-4ffe-b422-02d35c453fce" />  

<img width="777" height="223" alt="image" src="https://github.com/user-attachments/assets/c71d1314-e40b-4695-9af8-445b25b0b0d7" />  


## Tecnologias Utilizadas

- Linguagem C
- GCC
- Estruturas de Dados (Hash Table + Lista Ligada)

## Objetivo Educacional

Este projeto foi desenvolvido como exercicio pratico da disciplina de Algoritmos, Estruturas de Dados e TAD, reforcando:

- aplicacao pratica de TADs
- organizacao modular de codigo
- implementacao de tabela hash realista
- funcionamento de exclusao com colisao

## Autoria e Licenca

Este projeto foi desenvolvido por Juliana Apgaua Sant'Ana Vidigal e pode ser utilizado livremente para fins academicos.
