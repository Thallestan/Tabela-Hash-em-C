#include "HashTable.h"
#include "Validacoes.c"


// Função hash (djb2)
unsigned int hash_function(const char *cpf) {
    unsigned int hash = 5381;
    int c;
    while ((c = *cpf++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

// Inicializa a tabela 
void initialize_table() {
    hash_table = (Node **)malloc(TABLE_SIZE * sizeof(Node *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

// Insere o cadastro na tabela
void insert(const char *cpf, const char *nome, const char *data_nascimento) {
    unsigned int index = hash_function(cpf);

    Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->cpf, cpf) == 0) { 
            // Atualiza o nó existente
            strcpy(current->value.nome, nome);
            strcpy(current->value.data_nascimento, data_nascimento);
            strcpy(current->value.cpf, cpf);
            return;
        }
        current = current->next;
    }

    // Adiciona um novo nó, pois o CPF não foi encontrado
    Node *new_node = (Node *)malloc(sizeof(Node));
    strcpy(new_node->cpf, cpf);
    strcpy(new_node->value.nome, nome);
    strcpy(new_node->value.data_nascimento, data_nascimento);
    strcpy(new_node->value.cpf, cpf);
    new_node->next = hash_table[index];
    hash_table[index] = new_node;

    element_count++;
    if ((float)element_count / TABLE_SIZE > LOAD_FACTOR_THRESHOLD) {
        resize_table();
    }
}

// Funcao para verificar se um numero e primo
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Funcao para encontrar o proximo numero primo maior ou igual a n
int next_prime(int n) {
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

// Redimensiona a tabela
void resize_table() {
    int old_size = TABLE_SIZE;
    TABLE_SIZE = next_prime(TABLE_SIZE *2);
    
    Node **old_table = hash_table;

    // Aloca nova tabela com o tamanho atualizado
    hash_table = (Node **)malloc(TABLE_SIZE * sizeof(Node *));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }

    // Reinsere os elementos da tabela antiga na nova tabela
    for (int i = 0; i < old_size; i++) {
        Node *current = old_table[i];
        while (current != NULL) {
            insert(current->cpf, current->value.nome, current->value.data_nascimento);
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(old_table);
}

// Busca os dados pelo CPF
DadosPessoa *search(const char *cpf) {
    unsigned int index = hash_function(cpf);

    Node *current = hash_table[index];
    while (current != NULL) {
        if (strcmp(current->cpf, cpf) == 0) {
            return &current->value;
        }
        current = current->next;
    }

    return NULL;
}

// Remove um cadastro da tabela
void delete(const char *cpf) {
    unsigned int index = hash_function(cpf);

    Node *current = hash_table[index];
    Node *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->cpf, cpf) == 0) {
            if (prev == NULL) {
                hash_table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            element_count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Exibe o conteúdo da tabela hash
void display_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Indice %d: ", i);
        Node *current = hash_table[i];
        while (current != NULL) {
            printf("( CPF = %s, Nome = %s, Data Nascimento = %s ) -> ",
                   current->cpf, current->value.nome, current->value.data_nascimento);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Salva tabela em um arquivo
void save_to_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = hash_table[i];
        while (current != NULL) {
            fprintf(file, "%s-%s-%s\n", current->cpf, current->value.nome, current->value.data_nascimento);
            current = current->next;
        }
    }

    fclose(file);
    printf("Dados salvos no arquivo %s.\n", filename);
}

// Carrega os dados de um arquivo na tabela
void load_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo para carregar.\n");
        return;
    }

    char linha[MAX_INPUT_SIZE], cpf[12], nome[MAX_INPUT_SIZE], data_nascimento[11];
    int linhas_invalidas = 0, linhas_validas = 0;

    while (fgets(linha, sizeof(linha), file)) {
        // Remove a quebra de linha, se existir
        linha[strcspn(linha, "\n")] = '\0';

        // Usa strtok para dividir a linha em partes com base no delimitador '-'
        char *token = strtok(linha, "-");
        if (token == NULL) {
            printf("\nAviso: Linha com formato incorreto encontrada e ignorada: %s\n", linha);
            linhas_invalidas++;
            continue;
        }
        strncpy(cpf, token, 11);
        cpf[11] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL) {
            printf("\nAviso: Linha com formato incorreto encontrada e ignorada: %s\n", linha);
            linhas_invalidas++;
            continue;
        }
        strncpy(nome, token, MAX_INPUT_SIZE);
        nome[MAX_INPUT_SIZE - 1] = '\0';

        token = strtok(NULL, "-");
        if (token == NULL) {
            printf("\nAviso: Linha com formato incorreto encontrada e ignorada: %s\n", linha);
            linhas_invalidas++;
            continue;
        }
        strncpy(data_nascimento, token, 10);
        data_nascimento[10] = '\0';

        // Validação dos dados
        if (!validar_cpf(cpf)) {
            printf("\nAviso: CPF invalido encontrado e ignorado: %s\n", cpf);
            linhas_invalidas++;
            continue;
        }
        if (!validar_nome(nome)) {
            printf("\nAviso: Nome invalido encontrado e ignorado: %s\n", nome);
            linhas_invalidas++;
            continue;
        }
        if (!validar_data(data_nascimento)) {
            printf("\nAviso: Data de nascimento invalida encontrada e ignorada: %s\n", data_nascimento);
            linhas_invalidas++;
            continue;
        }

        // Dados válidos são inseridos na tabela
        insert(cpf, nome, data_nascimento);
        linhas_validas++;
    }

    fclose(file);

    printf("\nDados carregados do arquivo %s (apenas dados validos).\n", filename);
    printf("\nLinhas validas carregadas: %d. \nLinhas ignoradas por erro: %d.\n", linhas_validas, linhas_invalidas);
}








