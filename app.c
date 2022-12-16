#include <stdio.h>
#include "strings_manipulation.h"
#include "optim_word.h"
#include "list_define.h"
#include <string.h>

#define MAX_STRING 7

int main(void){
    List *words = readfile();
    const char found_word[] = "22222";
    char input[MAX_STRING];
    List *optim = words;
    int unused_letters['z'-'a'+1] = {0};
    char guess[MAX_STRING] = "00000";
    char used_letters[MAX_STRING] = "\0";
    char in_word_not_position[MAX_STRING]['z' - 'a' + 2] = {"\0","\0","\0","\0","\0","\0","\0"};
    double entropy, optim_entropy = get_entropy(words, words);
    int number_of_guess = 0;
    do{
        optim_entropy = get_entropy(words, words);
        optim = words;
        for(List *candidate = words->next; candidate != NULL; candidate = candidate->next){
            entropy = get_entropy(candidate, words);
            //printf("entropy = %lf\tword = %s\n", entropy, candidate->value);
            if(entropy > optim_entropy){
                optim_entropy = entropy;
                optim = candidate;
            }
        }
        printf("guess no. %d = %s\n", ++number_of_guess,optim->value);
        scanf("%s", input);
        // TO DO : parse the input and based on it evaluate the letters that cannot be used
        // Eliminate the words that doesn't have the fixed letters on the same position, or that doesn't contain
        // yellow letters.
        if(strcmp(input, "22222\0") == 0){
            break;
        }
        for(int i = 0; i < 5; i++){
            if(input[i] == '2'){
                guess[i] = optim->value[i];
            }
            else if(input[i] == '1'){
                if(check_letter_in_word(used_letters, optim->value[i] )== 0){
                    strncat(used_letters, &optim->value[i], 1);
                }
                if(check_letter_in_word(in_word_not_position[i], optim->value[i]) == 0){
                    strncat(in_word_not_position[i], &optim->value[i], 1);
                }
            }
            else{
                unused_letters[optim->value[i] - 'A'] = 1;
            }
        }
        filter_words(&words, unused_letters, guess, used_letters, in_word_not_position);
        for(List *candidate = words; candidate != NULL; candidate = candidate->next){
            printf("%s\n", candidate->value);
        }
        printf("used letters = %s\n", used_letters);
        for(int _i = 0; _i < 5; _i++){
            printf("iwnp[%d] : %s\n", _i, in_word_not_position[_i]);
        }
    }while(1);
    printf("Hooray! The guessed word is : %s\n", optim->value);
    return 0;
}
