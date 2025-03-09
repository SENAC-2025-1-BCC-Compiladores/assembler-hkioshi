
README - Conversor de Assembly para Memória

Este programa em C converte um código em assembly simples para um formato de memória específico e gera um arquivo de memória (`memoria.mem`). O código suporta diretivas `.DATA`, `.CODE`, e `.ORG`, que são usadas para declarar variáveis e instruções, e para definir o endereço inicial da memória.

## Estrutura do Código

1. **Arquivos de entrada**: 
   - O programa aceita um arquivo de entrada com a extensão `.asm` que contém o código em assembly. O arquivo deve ser passado como argumento ao rodar o programa.
   - O código de assembly pode conter diretivas como:
     - `.DATA`: Para declarar variáveis.
     - `.CODE`: Para declarar instruções.
     - `.ORG`: Para definir o endereço de início na memória.

2. **Instruções de Assembly**:
   O programa reconhece as seguintes instruções de assembly e as converte para os respectivos códigos de operação:
   - `STA`, `LDA`, `ADD`, `OR`, `AND`, `NOT`, `JMP`, `JN`, `JZ`, `HLT`

3. **Processamento das Variáveis e Instruções**:
   - As variáveis são armazenadas com nome, valor e endereço, e são alocadas em posições de memória após a seção de código.
   - As instruções são processadas e convertidas para códigos de operação e endereços correspondentes.

4. **Saída**:
   - O arquivo de memória gerado contém 516 posições de memória, sendo preenchidas com os códigos de operação, endereços e valores das variáveis.

## Como Usar

1. Compile o código em C:
   ```
   gcc -o conversor conversor.c
   ```

2. Execute o programa passando o arquivo de código assembly como argumento:
   ```
   ./conversor arquivo.asm
   ```

   Exemplo de código em assembly:

   ```
   .DATA
   A DB 10
   B DB 20
   C DB ?
   
   .CODE
   LDA A
   ADD B
   STA A
   HLT
   ```

   O programa irá gerar o arquivo `memoria.mem` com o conteúdo da memória.

3. Verifique o arquivo `memoria.mem`, que conterá os valores de memória resultantes do código de assembly.

## Explicação do Código

- **Estruturas de Dados**:
  - `Variavel`: Representa uma variável com nome, valor e endereço de memória.
  - `Instrucao`: Representa uma instrução com código e endereço.
  
- **Funções**:
  - `acharInstrucao`: Converte uma instrução de assembly em seu código de operação correspondente.
  - `acharEndereco`: Retorna o endereço de uma variável na memória.
  - `corrigirPos`: Corrige a posição de memória de acordo com as variáveis.

- **Memória**:
  - A memória tem 516 posições e é preenchida com instruções e variáveis conforme o código de assembly.

## Licença

Este código é fornecido como está, sem garantias de qualquer tipo.
