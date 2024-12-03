/*
 * Projeto: Tabela Hash para armazenamento de dados pessoais
 * Autores: Thalles Stanziola e Victor Hugo Almeida
 * Data de Criação: 19/11/2024
 * Descrição: Este projeto implementa uma tabela hash em C para armazenar dados pessoais, como nome, CPF e data de nascimento;
 *            A chave de busca é o CPF;
 *            A função hash utilizada é a djb2;
 *            Valida as entradas (CPF,NOME e DATA DE NASCIMENTO).
 * Licença: Sem restrições
 * Versão: 3.0
 *
 * Dependências: Nenhuma biblioteca externa necessária.
 */

#include "HashTable.h"
#include "HashTable.c"

int main() {
    initialize_table();

    char nome[MAX_INPUT_SIZE];
    char cpf[12];
    char data_nascimento[11];
    char confirmacao;
    int choice;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Inserir cadastro;\n");
        printf("2. Buscar dados pelo CPF;\n");
        printf("3. Remover cadastro;\n");
        printf("4. Exibir tabela;\n");
        printf("5. Salvar tabela em arquivo;\n");
        printf("6. Carregar tabela de arquivo;\n");
        printf("7. Sair.\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        getchar();  // Limpa o caractere de nova linha do buffer

        switch (choice) {
            case 1:  // Inserir
                do {
                    printf("Digite o CPF: ");
                    fgets(cpf, 12, stdin);
                    cpf[strcspn(cpf, "\n")] = '\0';                    
                    getchar();

                    if (!validar_cpf(cpf)) {
                        do {
                            printf("\nCPF invalido! Deseja tentar novamente? (s/n): ");
                            scanf(" %c", &confirmacao);
                            getchar();
                        } while (confirmacao != 's' && confirmacao != 'S' && confirmacao != 'n' && confirmacao != 'N');
                        if (confirmacao == 'n' || confirmacao == 'N') {
                            printf("\nOperacao cancelada pelo usuario.\n");
                            break;
                        }
                    }
                } while (!validar_cpf(cpf) && (confirmacao == 's' || confirmacao == 'S'));

                if (!validar_cpf(cpf)) {
                    break;
                }

                if (cpf_ja_cadastrado(cpf)) {
                    do {
                        printf("\nCPF ja cadastrado! Deseja atualizar o cadastro? (s/n): ");
                        scanf(" %c", &confirmacao);
                        getchar();
                    } while (confirmacao != 's' && confirmacao != 'S' && confirmacao != 'n' && confirmacao != 'N');

                    if (confirmacao == 'n' || confirmacao == 'N') {
                        printf("\nAtualizacao de cadastro cancelada pelo usuario.\n");
                        break;
                    }
                }

                do {
                    printf("Digite o nome: ");
                    fgets(nome, MAX_INPUT_SIZE, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    if (!validar_nome(nome)) {
                        do {
                            printf("\nNome invalido! Deseja tentar novamente? (s/n): ");
                            scanf(" %c", &confirmacao);
                            getchar();
                        } while (confirmacao != 's' && confirmacao != 'S' && confirmacao != 'n' && confirmacao != 'N');
                        if (confirmacao == 'n' || confirmacao == 'N') {
                            printf("\nOperacao cancelada pelo usuario.\n");
                            break;
                        }
                    }
                } while (!validar_nome(nome) && (confirmacao == 's' || confirmacao == 'S'));

                if (!validar_nome(nome)) {
                    break;
                }

                do {
                    printf("Digite a data de nascimento (DD/MM/AAAA): ");
                    fgets(data_nascimento, 11, stdin);
                    data_nascimento[strcspn(data_nascimento, "\n")] = '\0';

                    if (!validar_data(data_nascimento)) {
                        do {
                            printf("\nData de nascimento invalida! Deseja tentar novamente? (s/n): ");
                            scanf(" %c", &confirmacao);
                            getchar();
                        } while (confirmacao != 's' && confirmacao != 'S' && confirmacao != 'n' && confirmacao != 'N');
                        if (confirmacao == 'n' || confirmacao == 'N') {
                            printf("\nOperacao cancelada pelo usuario.\n");
                            break;
                        }
                    }
                } while (!validar_data(data_nascimento) && (confirmacao == 's' || confirmacao == 'S'));

                if (!validar_data(data_nascimento)) {
                    break;
                }

                // Mostra os dados inseridos e pede confirmação
                printf("\nPor favor, confirme os dados inseridos:\n");
                printf("CPF: %s\n", cpf);
                printf("Nome: %s\n", nome);
                printf("Data de Nascimento: %s\n", data_nascimento);
                do {
                    printf("Os dados estao corretos? (s/n): ");
                    scanf(" %c", &confirmacao);
                    getchar();
                } while (confirmacao != 's' && confirmacao != 'S' && confirmacao != 'n' && confirmacao != 'N');

                if (confirmacao == 's' || confirmacao == 'S') {
                    insert(cpf, nome, data_nascimento);
                    printf("\nDados inseridos com sucesso!\n");
                } else {
                    printf("\nInsercao cancelada pelo usuario.\n");
                }
                break;

            case 2:  // Buscar
                printf("Digite o CPF para buscar: ");
                fgets(cpf, 12, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';

                if (validar_cpf(cpf)) {
                    DadosPessoa *result = search(cpf);
                    if (result) {
                        printf("\nCadastro encontrado:\nNome: %s.\nData de Nascimento: %s.\nCPF: %s.\n", result->nome, result->data_nascimento, cpf);
                    } else {
                        printf("\nCPF nao encontrado.\n");
                    }
                } else {
                    printf("\nCPF invalido: %s\n", cpf);
                }
                break;

            case 3:  // Remover
                printf("\nDigite o CPF para remover: ");
                fgets(cpf, 12, stdin);
                cpf[strcspn(cpf, "\n")] = '\0';

                delete(cpf);
                printf("\nCPF removido (se existia).\n");
                break;

            case 4:  // Exibir tabela
                display_table();
                break;

            case 5:  // Salvar em arquivo
                printf("Informe o nome do arquivo para salvar (com extensao): ");
                char nome_arquivo_salvar[MAX_INPUT_SIZE];
                fgets(nome_arquivo_salvar, MAX_INPUT_SIZE, stdin);
                nome_arquivo_salvar[strcspn(nome_arquivo_salvar, "\n")] = '\0';
                save_to_file(nome_arquivo_salvar);
                printf("\nTabela salva em \"%s\".\n", nome_arquivo_salvar);
                break;

            case 6:  // Carregar de arquivo
                printf("\nArquivo deve estar no formato CPF-NOME-DATA (XXXXXXXXXXX-NOME SOBRENOME-DD/MM/AAAA).\nUm cadastro por linha.\nSem linhas vazias.\nExtensao do arquivo deve ser .txt\nSem caracteres especiais ou acentos\n");
                printf("Informe o diretorio/mascara do arquivo para carregar (com extensao): ");
                char nome_arquivo_carregar[MAX_INPUT_SIZE];
                fgets(nome_arquivo_carregar, MAX_INPUT_SIZE, stdin);
                nome_arquivo_carregar[strcspn(nome_arquivo_carregar, "\n")] = '\0';
                load_from_file(nome_arquivo_carregar);
                break;


            case 7:  // Sair
                printf("\nEncerrando...\n");
                return 0;

            default:
                printf("\nNumero invalido. Tente novamente.\n");
        }
    }

    return 0;
}
