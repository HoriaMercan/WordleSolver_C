#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "strings_manipulation.h"
#include "list_define.h"
#define WORDS (int)(11454)
char * get_random_word(){
    List *words = readfile();
    List *word_to_guess = words;
    srand(time(NULL));
    int r = rand() % WORDS;
    while(r--){
        word_to_guess = word_to_guess->next;
    }
    char *ans;
    ans = (char*)malloc(7 * sizeof(char));
    strcpy(ans, word_to_guess->value);
    delete_word(&words, NULL);
    return ans;
}
int main(void){
    
    char *WORD = get_random_word();
    printf("WORD to guess: %s\n", WORD);
    char INPUT[7] = "00000", OUTPUT[7] = "00000";
    while(strcmp(WORD, INPUT) != 0){
        scanf("%s", INPUT);
        // printf("%s\n", INPUT);
        OUTPUT[0] = '0'; OUTPUT[1] = '0'; OUTPUT[2] = '0'; OUTPUT[3] = '0'; OUTPUT[4] = '0';
        for(int i = 0; i < 5; i++){
            if(check_letter_in_word(WORD, INPUT[i])){
                if(INPUT[i] == WORD[i]){
                    OUTPUT[i] = '2';
                }
                else{
                    OUTPUT[i] = '1';
                }
            }
        }
        for(int i = 0; i < 5; i++){
            printf("%c", OUTPUT[i]);
        }
        printf("\n");
    }
    return 0;
}