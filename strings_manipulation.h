typedef struct __list List; 

List *readfile();
void delete_word(List **list, List *word);
int check_letter_in_word(char string[], char c);