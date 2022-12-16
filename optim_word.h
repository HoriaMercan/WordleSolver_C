#include "strings_manipulation.h"


double get_entropy(List *word, List *words);
void filter_words(List **words, int unused_letters[], char guess[], char used_letters[], char in_word_not_position[7][27]);