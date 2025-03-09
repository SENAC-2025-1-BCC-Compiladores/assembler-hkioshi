[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/FLG6_3H5)
# Henrique Kioshi Yamauchi 

# README - Simulador de Processador Simples

Este é um simulador de um processador simples que lê um arquivo de assembly, interpreta as instruções e variáveis definidas e cria uma memória simulada. O código suporta duas seções no arquivo de assembly: `.DATA` (para dados/variáveis) e `.CODE` (para instruções do processador). Após processar o arquivo de entrada, o programa gera um arquivo de memória contendo os valores codificados no formato binário.

## Funcionalidades
- **Leitura de Arquivo Assembly**: O programa processa um arquivo de assembly com as seções `.DATA` (variáveis) e `.CODE` (instruções).
- **Mapeamento de Instruções**: O código converte as instruções de assembly para códigos de operação (opcodes) do processador.
- **Ajuste de Posições de Memória**: O programa ajusta a posição da memória para armazenar as variáveis e instruções de maneira adequada.
- **Criação de Arquivo de Memória**: O simulador gera um arquivo de memória (`memoria.mem`) com os dados em formato numérico, que pode ser visualizado por editores hexadecimais ou de texto.

## Estrutura do Código

### Definições e Estruturas:
- **`Variavel`**: Estrutura que armazena o nome, valor e posição de uma variável.
- **`Instrucao`**: Estrutura que armazena o código de operação e o endereço de uma instrução.

### Funções:
- **`acharInstrucao(char *x)`**: Função que mapeia as instruções de assembly para os códigos de operação correspondentes.
- **`acharEndereco(Variavel variaveis[], int varCount, char *nome)`**: Função que retorna o endereço de uma variável, dada pelo nome.
- **`corrigirPos(int pos)`**: Função que ajusta a posição das variáveis na memória para um formato específico.

### Leitura do Arquivo de Assembly:
- O arquivo é processado linha por linha. As seções `.DATA` e `.CODE` são identificadas, e as variáveis e instruções são armazenadas em arrays correspondentes.
- A seção `.ORG` define o valor de posição de memória onde as instruções ou variáveis devem ser armazenadas.

### Geração do Arquivo de Memória:
- As variáveis e instruções são armazenadas em um array de memória.
- O arquivo de memória é gerado em formato numérico, com cada valor sendo representado por um número inteiro.
- Valores `0` são preenchidos nas posições não utilizadas para garantir que a memória esteja alinhada corretamente.

## Como Usar

1. **Preparação do Arquivo de Assembly**:
   Crie um arquivo de texto com a extensão `.asm` que contenha seu código de assembly. O arquivo deve seguir a seguinte estrutura:

   ```
   .DATA
   variavel1 10
   variavel2 20

   .CODE
   LDA variavel1
   ADD variavel2
   HLT
   ```

   Onde:
   - **`.DATA`**: Define as variáveis e seus valores.
   - **`.CODE`**: Define as instruções a serem executadas.

2. **Compilação**:
   Compile o código com o compilador C de sua escolha.

   Exemplo com GCC:
   ```bash
   gcc -o simulador simulador.c
   ```

3. **Execução**:
   Execute o programa passando o arquivo de assembly como entrada.

   Exemplo:
   ```bash
   ./simulador
   ```

4. **Resultado**:
   O programa gerará um arquivo chamado `memoria.mem`, que contém os valores da memória simulada.

## Estrutura de Memória

O arquivo `memoria.mem` contém os dados codificados em formato numérico (hexadecimal) com a seguinte estrutura:

- **Primeiras 4 posições (memória[0] até memória[3])**: Cabeçalhos de controle.
- **Instruções (até memória[259])**: Códigos de operação e endereços.
- **Memória de Variáveis (a partir de memória[260])**: Valores das variáveis definidas na seção `.DATA`.

## Exemplo de Arquivo de Memória Gerado
O arquivo `memoria.mem` gerado terá um conteúdo semelhante ao seguinte:

```
3 78 44 52 16 00 10 00 00 00 00 ...
```

Onde os números representam os valores armazenados em cada posição da memória simulada.

## Contribuições

Contribuições para o projeto são bem-vindas. Para relatar bugs ou enviar melhorias, abra um issue ou um pull request neste repositório.

## Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.
