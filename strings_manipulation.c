#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_define.h"

#define MAX_STRING 7


List *readfile()
{
    List *first, *list, *new_list;
    first = (List *)malloc(sizeof(List));
    first->next = NULL;
    list = first;
    char buffer[MAX_STRING];
    FILE *file_in = fopen("cuvinte_wordle.txt", "r");
    if(file_in == NULL){
        printf("ERROR: Couldn't open file\n");
        exit(0);
    }
    while(fgets(buffer, MAX_STRING, file_in)){
        new_list = (List *)malloc(sizeof(List));
        list->next = new_list;
        strncpy(new_list->value, buffer, 5);
        new_list->value[5] = '\0';
        new_list->next = NULL;
        list = new_list;
    }
    list = first->next;
    free(first);
    return list;
}
void delete_word(List **list, List *word){
    if(word == NULL){
        List *aux = *list;
        *list = (*list)->next;
        free(aux);
    }
    else{
        List *aux = word->next;
        if(aux == NULL)
            return ;
        word->next = word->next->next;
        free(aux);
    }
}
int check_letter_in_word(char string[], char c){
    // if(string[0] == c || string[1] == c || string[2] == c || string[3] == c || string[4] == c)
    //     return 1;
    // return 0;
    int ans = 0;
    for(int i = 0; i < strlen(string); i++){
        if(string[i] == c)
            ans++;
    }
    return ans;
}
int string_equal(char a[MAX_STRING], char b[MAX_STRING]){
    if(a[0]==b[0] && a[1]==b[1] && a[2]==b[2] && a[3]==b[3] && a[4]==b[4])
        return 1;
    return 0;
}
// int main(void){
//     // List *words = readfile();
//     // for(int i = 0; i<10;i++){
//     //     printf("%s\n", words->value);
//     //     words = words->next;
//     // }
//     return 0;
// }