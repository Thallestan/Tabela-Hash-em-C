Projeto elaborado pelos alunos da UFABC:
- Thalles Stanziola
- Victor Hugo Almeida

Implementação de uma tabela hash em C:
- Tabela Hash para armazenamento de dados pessoais (Nome, CPF, data de nascimento);
- Inserção, Busca e remoção de cadastros na tabela;
- Função hash utilizada é a djb2;
- Solução de colisão por encadeamento;
- Validações dos dados de entrada;
- Redimensionamento automático do tamanho da tabela (dobra a tabela quando a capacidade/Número de registros for maior que 0,7);
- Existe a tabela atual com todos os registros e encadeamentos;
- Exporta a tabela para um arquivo ".txt";
- Importa uma tabela através de um arquivo ".txt" formatado (CPF-NOME SOBRENOME-DATA DE NASCIMENTO [dd/mm/aaaA]);
- Valida os dados importados do arquivo e só registra as informações válidas.

Para executar, necessário apenas instalar o GCC.


