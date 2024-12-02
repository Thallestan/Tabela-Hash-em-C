#ifndef HASHTABLE_H
#define HASHTABLE_H

#define INITIAL_TABLE_SIZE 10
#define MAX_INPUT_SIZE 100  
#define LOAD_FACTOR_THRESHOLD 0.7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para armazenar os dados da pessoa
typedef struct {
    char nome[MAX_INPUT_SIZE];
    char data_nascimento[11];  // Formato: "DD/MM/AAAA"
    char cpf[12];              // CPF com 11 dígitos + '\0'
} DadosPessoa;

// Estrutura da tabela hash
typedef struct Node {
    char cpf[12];
    DadosPessoa value;
    struct Node *next;
} Node;

// Protótipos das funções
int cpf_ja_cadastrado(const char *cpf);
int validar_data(const char *data);
int validar_cpf(const char *cpf);
int calcular_dv1(const char *cpf);
int calcular_dv2(const char *cpf, int dv1);
void insert(const char *cpf, const char *nome, const char *data_nascimento);
DadosPessoa* search(const char *cpf);
void delete(const char *cpf);
void initialize_table();
void resize_table();
void display_table();
void save_to_file(const char *filename);
void load_from_file(const char *filename);
int validar_nome(const char *nome);

char confirmacao;
Node **hash_table; 
int TABLE_SIZE = INITIAL_TABLE_SIZE;  // Tamanho inicial da tabela
int element_count = 0;  // Número de elementos na tabela

#endif

