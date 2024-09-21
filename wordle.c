#include "wordle.h"

wordlist_t load_words(char *str)
{
    FILE *fp = fopen(str, "r");

    char buffer[BUF_SIZE] = { 0 };
    wordlist_t w = { 0 };

    if (!fp) {
        return w;
    }

    while (fgets(buffer, BUF_SIZE, fp)) {
        trim(buffer);
        w.words = realloc(w.words,sizeof(void*) * (w.num_words + 1));
        w.words[w.num_words] = malloc(strlen(buffer) + 1);
        w.num_words = w.num_words;
        strcpy(w.words[w.num_words++], buffer);
    }
    fclose(fp);
    return w;
}
