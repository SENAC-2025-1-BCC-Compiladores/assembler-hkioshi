#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 128
#define MAX_INSTRUCOES 128

int memoria[516];

typedef struct {
    char nome[10];
    int valor;
    int pos;
} Variavel;

typedef struct {
    int codigo;
    int endereco;

} Instrucao;

int acharInstrucao(char *x)
{
    if (strncmp(x, "STA", 3) == 0) {
        return 0x10;
    } else if (strncmp(x, "LDA", 3) == 0) {
        return 0x20;
    } else if (strncmp(x, "ADD", 3) == 0) {
        return 0x30;
    } else if (strncmp(x, "OR", 2) == 0) {
        return 0x40;
    } else if (strncmp(x, "AND", 3) == 0) {
        return 0x50;
    } else if (strncmp(x, "NOT", 3) == 0) {
        return 0x60;
    } else if (strncmp(x, "JMP", 3) == 0) {
        return 0x80;
    } else if (strncmp(x, "JN", 2) == 0) {
        return 0x90;
    } else if (strncmp(x, "JZ", 2) == 0) {
        return 0xA0;
    } else if (strncmp(x, "HLT", 3) == 0) {
        return 0xF0;
    }
}

int acharEndereco(Variavel variaveis[], int varCount, char *nome) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variaveis[i].nome, nome) == 0) {
            return variaveis[i].pos;
        }
    }
    return -1;
}

int corrigirPos(int pos) {
    return pos * 2 + 4;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Variavel variaveis[MAX_VARS];
    Instrucao instrucoes[MAX_INSTRUCOES];
    int varCount = 0, instrCount = 0;
    int pos = -1; 
    int posVar = 128;
    char linha[256];
    int secao = 0; // 1 = .DATA, 2 = .CODE

    while (fgets(linha, sizeof(linha), file)) {
        if (linha[0] == ';' || linha[0] == '\n') continue; // Ignorar comentários e linhas vazias
        
        if (strncmp(linha, ".DATA", 5) == 0) {
            secao = 1;
            continue;
        }
        if (strncmp(linha, ".CODE", 5) == 0) {
            secao = 2;
            continue;
        }
        if (strncmp(linha, ".ORG", 4) == 0) {
            sscanf(linha, ".ORG %d", &pos);
            continue;
        }

        if (secao == 1) { // Processando .DATA
            char valorStr[10];  
            sscanf(linha, "%s %s %s", variaveis[varCount].nome, valorStr, valorStr);  
            variaveis[varCount].valor = atoi(valorStr);
            variaveis[varCount].pos = posVar;
            varCount++;
            posVar++;
        } else if (secao == 2) { // Processando .CODE
            char var[10];
            char instr[10];
            sscanf(linha, "%s %s", instr, var);
            instrucoes[instrCount].endereco = acharEndereco(variaveis, varCount, var);

            instrucoes[instrCount].codigo = acharInstrucao(instr);
            instrCount++;
        }
    }
    fclose(file);

    memoria[0] = 3;
    memoria[1] = 0x4E; 
    memoria[2] = 0x44;
    memoria[3] = 0x52; 
    int index = 4;
    for (int i = 0; i < instrCount; i++) {
        memoria[index] = instrucoes[i].codigo;
        memoria[index + 1] = 0x00;
        if (instrucoes[i].endereco == -1)
        {
            index += 2;
        }
        else
        {
            memoria[index + 2] = instrucoes[i].endereco;
            memoria[index + 3] = 0x00;
            index += 4;
        }
        
    }

    while (index < 260)
    {
        memoria[index] = 0x00;
        index++;
    }
    
    int num = 0;

    while (index < 516)
    {
        if (corrigirPos(variaveis[num].pos) == index && num < varCount)
        {
            memoria[index] = variaveis[num].valor;
            num++;       
            memoria[index + 1] = 0x00;
            index+=2;
        }
        else
        {
            memoria[index] = 0x00;
            index++;
        }
        
    }

    FILE *memFile = fopen("memoria.mem", "w");
    if (memFile == NULL) {
        perror("Erro ao criar o arquivo de memória");
        return 1;
    }
    for (int i = 0; i < 516; i++) {
        fprintf(memFile, "%d ", memoria[i]);
    }
    fclose(memFile);

    return 0;
}
