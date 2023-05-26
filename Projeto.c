/*
Algoritmos e Programação II
Nome: Gustavo Garabetti Munhoz - Grupo 13
Turma: 02N12
Complexidade do Algoritmo: O(N)
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// VARIÁVEIS UTILIZADAS NO CÓDIGO:
#define MAX_SIZE 1007 // Número máximo de palavras na entrada 
#define MAX_WL 207 // Tamanho máximo de uma palavra no texto

// ENDEREÇOS DOS ARQUIVOS UTILIZADOS:
const char INPUT[] = "entrada.txt", OUTPUT[] = "saida.txt";

// CONVERTE AS LETRAS DA PALAVRA PARA CAIXA BAIXA:
void strlwr(char word[]){ 
    for(int i = 0; i < strlen(word); i++) word[i] = tolower(word[i]);
}

// GUARDA PALAVRA NO DICIONÁRIO EM O(N):
void save(char word[], char dic[][MAX_WL], int index, int last){
    for(int i = last; i >= index; i--) strcpy(dic[i+1], dic[i]); // Copia cada palavra pra posição seguinte
    strcpy(dic[index], word); // Insere a palavra na posição conveniente
}

// ENCONTRAR A POSIÇÃO PARA INSERÇÃO DA PALAVRA EM O(log N)
int find(char searched[], char dic[][MAX_WL], int begin, int end){
    if(begin > end) return begin; // Se os ponteiros se cruzam, retornamos o mais a direita
    
    int middle = (begin+end)/2, ans; 
    // Comparação lexicográfica entre o centro do dicionário e a palavra a ser inserida
    int comp = strcmp(searched, dic[middle]);

    // Guardar a posição -1 indica que ela já está no dicionário
    if(comp == 0) ans = -1;
    // Se a palavra vem antes do meio do dicionário, analise a metade inferior
    else if(comp < 0) ans = find(searched, dic, begin, middle-1);
    // Se a palavra vem depois do meio do dicionário, analise a metade superior
    else ans = find(searched, dic, middle+1, end);

    return ans; // Retorna a posição para inserção
}

// ESCREVER ORDENADAMENTE A PALAVRA NO DICIONARIO EM O(N)
int add_in_dic(char word[], char dic[][MAX_WL], int dic_length){
    strlwr(word); // Antes de guardar, converta-a para caixa baixa
    int index = find(word, dic, 0, dic_length-1); // Encontrar posição correta para inserir a palavra
    if(index != -1){ // Se a palavra não estiver no dicionário
        save(word, dic, index, dic_length); // Guarde a palavra
        dic_length++; // O número de palavras aumenta em uma unidade
    }
    return dic_length; // Retorne o novo tamanho do dicionário
}

// IMPRIMIR E GUARDAR NUM ARQUIVO DE TEXTO AS PALAVRAS DO DICIONÁRIO EM O(N)
void print_and_save(FILE* arq, char dic[][MAX_WL], int dic_length){
    printf("DICIONARIO:\n");
    fprintf(arq, "DICIONARIO:\n");
    for(int i = 0; i < dic_length; i++){ // Percorre cada palavra no dicionário
        printf("%s\n", dic[i]);
        fprintf(arq, "%s\n", dic[i]); // Guarda no arquivo
    }
    printf("total de palavras diferentes no dicionario=%d\n", dic_length);
    fprintf(arq, "total de palavras diferentes no dicionario=%d.", dic_length); // Guarda mensagem final e numero de palavras
}

int main(){
    FILE *input, *output; // Ponteiro para arquivo de entrada e saida.
    input = fopen(INPUT, "r"); // Abrir entrada como leitura
    output = fopen(OUTPUT, "w"); // Abre saida como escrita

    if(input == NULL){
        printf("Erro ao tentar abrir o arquivo.\n");
        return -1;
    }

    char dic[MAX_SIZE][MAX_WL];
    int words_in_dic = 0;

    while(!feof(input)){ // Enquanto não chegar no fim do arquivo de entrada
        char word[MAX_SIZE]; 
        fscanf(input, "%s", word); // Ler a palavra até chegar num carácter ' '
        // Atualiza o tamanho do dicionário e insere a palavra nele:
        words_in_dic = add_in_dic(word, dic, words_in_dic);
    }

    print_and_save(output, dic, words_in_dic); // Imprime e salva as palavras
  
    // Fechar os arquivos de entrada e saida
    fclose(output);
    fclose(input);

    return 0;
}