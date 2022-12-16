#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "strings_manipulation.h"
#include "list_define.h"
const int MAX_PATTERNS = 243;

int get_base3_digit(int position, int number){
    while(position--)
        number/=3;
    return number%3;
}

double get_entropy(List *word, List *words){
    List *candidate = words;
    int* frequence;
    frequence = (int *)calloc(MAX_PATTERNS, sizeof(int));
    int code;
    double entropy = 0.0;
    int count_words = 0;
    while(candidate != NULL){
        count_words++;
        code = 0;
        for(int i = 0; i < 5; i++){
            code *= 3;
            if(candidate->value[i] == word->value[i])
                code+=2;
            else if(check_letter_in_word(candidate->value, word->value[i]) > 0)
                code+=1;
        }
        frequence[code]++;
        candidate = candidate->next;
    }
    for(int i = 0; i < MAX_PATTERNS; i++){
        if(frequence[i] != 0)
            entropy -= 1.0 * frequence[i] / count_words * log2(1.0 * frequence[i] / count_words);
    }
    free(frequence);
    return entropy;
}
int is_fit(char word[7], int unused_letters[], char guess[], char used_letters[], char in_word_not_position[7][27]){
    for(int i = 0; i < 5; i++){
        if(unused_letters[ word[i] - 'A' ] == 1)
            return 0;
        if(guess[i] != '0' && word[i] != guess[i])
            return 0;
        if(check_letter_in_word(in_word_not_position[i], word[i]) > 0)
            return 0;
    }
    for(int i = 0; i < strlen(used_letters); i++){
        if(check_letter_in_word(word, used_letters[i]) == 0)
            return 0;
    }
    return 1;
}
void filter_words(List **words, int unused_letters[], char guess[], char used_letters[], char in_word_not_position[7][27]){
    List *candidate = *words, *temp, *_word;
    while(candidate->next != NULL){
        if(is_fit(candidate->next->value, unused_letters, guess, used_letters, in_word_not_position) == 0){
            delete_word(words, candidate);
        }
        else{
            candidate = candidate->next;
        }
    }
    if(is_fit((*words)->value, unused_letters, guess, used_letters, in_word_not_position) == 0)
        delete_word(words, NULL);
}