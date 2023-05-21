#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 1007
#define MAX_WL 200

const char INPUT[] = "entrada.txt", OUTPUT[] = "saida.txt";

bool is_letter(char letter){
    return (letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'); 
}

void strlwr(char word[]){
    for(int i = 0; i < strlen(word); i++) word[i] = tolower(word[i]);
}

void save(char word[], char dic[][MAX_WL], int index, int last){
    for(int i = last; i >= index; i--){
        strcpy(dic[i+1], dic[i]);
    }
    strcpy(dic[index], word);
}

int find(char searched[], char dic[][MAX_WL], int begin, int end){
    if(begin > end) return begin;
    int middle = (begin+end)/2, ans;
    int comp = strcmp(searched, dic[middle]);

    if(comp == 0) ans = -1;
    else if(comp < 0) ans = find(searched, dic, begin, middle-1);
    else ans = find(searched, dic, middle+1, end);

    return ans;
}

int concatenate_in_buffer(char buffer[], int index, char letter){
    buffer[index] = letter;
    return ++index;
}

int add_in_dic(char buffer[], char dic[][MAX_WL], int index, int dic_length){
    strlwr(buffer);
    index = find(buffer, dic, 0, dic_length-1);
    if(index != -1 || dic_length == 0){
        save(buffer, dic, index, dic_length);
        dic_length++;
    }
    return dic_length;
}

int main(){
    FILE *input, *output;
    input = fopen(INPUT, "a");
    output = fopen(OUTPUT, "w");

    fprintf(input, ".");
    fclose(input);

    input = fopen(INPUT, "r");

    if(input == NULL){
        printf("Erro ao tentar abrir o arquivo.\n");
        return -1;
    }

    char word[MAX_SIZE], dic[MAX_SIZE][MAX_WL];
    int words_in_dic = 0;

    while(!feof(input)){
        if(fgets(word, MAX_SIZE, input) == NULL){
            printf("Fim do arquivo!");
        }

        char buffer[MAX_WL] = "";
        int last_index = 0, index_dic = 0;

        for(int i = 0; i < strlen(word); i++){
            if(is_letter(word[i])){
                last_index = concatenate_in_buffer(buffer, last_index, word[i]);
            }else{
                if(!is_letter(buffer[0])){
                    memset(buffer, '\0', sizeof(buffer));
                }else{
                    last_index = 0;
                    words_in_dic = add_in_dic(buffer, dic, index_dic, words_in_dic);
                    memset(buffer, '\0', sizeof(buffer));
                }
            }
        }
    }

    fclose(input);

    printf("DICIONARIO:\n");
    fprintf(output, "DICIONARIO:\n");
    for(int i = 0; i < words_in_dic; i++){
        printf("%s\n", dic[i]);
        fprintf(output, "%s\n", dic[i]);
    }
    printf("total de palavras diferentes no dicionario=%d\n", words_in_dic);
    fprintf(output, "total de palavras diferentes no dicionario=%d.", words_in_dic);
    fclose(output);

    return 0;
}