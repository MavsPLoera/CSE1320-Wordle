#include "wordle.h"

void trim(char *str) {
    int len = strlen(str);
    if (str[len-1] == '\n') {
        str[len-1] = 0;
    }
}

char* select_random_answer(wordlist_t x)
{
    char *answer = "\0";
    time_t t = time(NULL);

    srand(t);
    int index = rand() % (x.num_words-1);
    answer = x.words[index];

    for (int i = 0; i < x.num_words; i++) {
        if(strcmp(answer,x.words[i]) != 0)
        free(x.words[i]);
    }
    free(x.words);

    return answer;
}

int main(int argc, char **argv) 
{
    if (argc != 2) {
        return 1;
    }

    char* wordle_word = select_random_answer(load_words(argv[1]));
    printf("%s\n",wordle_word);
    int num_tries = 0;
    char guess[6];

    while(num_tries < MAX_TRIES)
    {
        char correct[6] = {' ',' ',' ',' ',' ','\0'};
        bool checked[5] = {false, false , false, false, false};

        printf("Enter your guess (%d left): ",MAX_TRIES - num_tries);
        fgets(guess,6,stdin);
        //trim(guess);
        printf("%s\n",guess);
        while(getchar() != '\n');

        //checks if letter of guess is in the same position or if the letter is in the word
        for(int i = 0; i < 5; i++)
        {
            if(guess[i] == wordle_word[i])
            {
                correct[i] = '^';
                checked[i] = true;
            } 
        }

        for(int j = 0; j < 5; j++)
        {
            if(correct[j] == ' ')
            {
                for(int a = 0; a < 5; a++)
                {
                    if(guess[j] == wordle_word[a] && !(checked[a]))
                    {
                        correct[j] = '*';
                        checked[a] = true;
                        break;
                    }
                }
            }
        }
        printf("%s\n",correct);

        if(strcmp(guess,wordle_word) == 0)
        {
            printf("Correct Answer: %s\n", wordle_word);
            break;
        }
        num_tries++;
    }
    return 0;
}
