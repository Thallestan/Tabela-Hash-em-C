#include "HashTable.h"

// Funcao para validar se o cpf ja foi cadastrado
int cpf_ja_cadastrado(const char *cpf) {
    DadosPessoa *result = search(cpf);
    return result != NULL;
}

// Função para validar se uma string representa uma data válida no formato DD/MM/AAAA
int validar_data(const char *data) {
    if (data == NULL || strlen(data) != 10) {
        return 0; 
    }
    
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (data[i] != '/') {
                return 0; 
            }
        } else {
            if (!isdigit(data[i])) {
                return 0; 
            }
        }
    }

    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12) {
        return 0; 
    }

    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return 0; // Abril, Junho, Setembro e Novembro têm no máximo 30 dias
    }

    if (mes == 2) {
        int bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if ((bissexto && dia > 29) || (!bissexto && dia > 28)) {
            return 0; 
        }
    }

    return 1;
}

// Função para validar se o nome é composto apenas por letras
int validar_nome(const char *nome) {
    if (nome == NULL || strlen(nome) == 0) {
        return 0; 
    }
    
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0; 
        }
    }

    return 1;
}

// Função para calcular o primeiro dígito verificador do CPF
int calcular_dv1(const char *cpf) {
    int pesos[] = {10, 9, 8, 7, 6, 5, 4, 3, 2};
    int soma = 0;

    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * pesos[i];
    }

    int dv1 = 11 - (soma % 11);
    if (dv1 >= 10) {
        dv1 = 0;
    }

    return dv1;
}

// Função para calcular o segundo dígito verificador do CPF
int calcular_dv2(const char *cpf, int dv1) {
    int pesos[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    int soma = 0;

    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * pesos[i];
    }
    soma += dv1 * pesos[9];

    int dv2 = 11 - (soma % 11);
    if (dv2 >= 10) {
        dv2 = 0;
    }

    return dv2;
}
//Verifica se todos os digitos do cpf sao iguais
int cpf_todos_digitos_iguais(const char *cpf) {
    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) {
            return 0; 
        }
    }
    return 1;
}

// Função para validar o CPF
int validar_cpf(const char *cpf) {
    if (strlen(cpf) != 11) {
        return 0; 
    }

    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return 0; 
        }
    }

    if (cpf_todos_digitos_iguais(cpf)) {
        return 0; 
    }

    int dv1 = calcular_dv1(cpf);
    int dv2 = calcular_dv2(cpf, dv1);

    if (cpf[9] - '0' == dv1 && cpf[10] - '0' == dv2) {
        return 1; 
    }

    return 0; 
}
