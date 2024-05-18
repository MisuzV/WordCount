#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countCharacters(const char *filename);
int countWords(const char *filename);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] <input_file_name>\n", argv[0]);
        return 1;
    }

    
    if (strcmp(argv[1], "-c") == 0) {
        int charCount = countCharacters(argv[2]);
        if (charCount >= 0) {
            printf("字符数：%d\n", charCount);
        } else {
            fprintf(stderr, "Error reading file: %s\n", argv[2]);
            return 1;
        }
    } else if (strcmp(argv[1], "-w") == 0) {
        int wordCount = countWords(argv[2]);
        if (wordCount >= 0) {
            printf("单词数：%d\n", wordCount);
        } else {
            fprintf(stderr, "Error reading file: %s\n", argv[2]);
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid parameter: %s\n", argv[1]);
        fprintf(stderr, "Usage: %s [-c|-w] <input_file_name>\n", argv[0]);
        return 1;
    }

    return 0;
}

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int charCount = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        charCount++;
    }

    fclose(file);
    return charCount;
}


int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int wordCount = 0;
    int inWord = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (inWord) {
                inWord = 0;
                wordCount++;
            }
        } else {
            inWord = 1;
        }
    }


    if (inWord) {
        wordCount++;
    }

    fclose(file);
    return wordCount;
}
