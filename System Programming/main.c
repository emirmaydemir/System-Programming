#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char filename[100];
    char word[100];
    char buffer[100];
    int count = 0, row = 1, column = 0;

    printf("Enter the filename: ");
    scanf("%s", filename);

    printf("Enter the word to search for: ");
    scanf("%s", word);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while (fscanf(file, "%s", buffer) != EOF) {
        column++;
        if (strcmp(buffer, word) == 0) {
            count++;
            printf("'%s' found at row %d, column %d\n", word, row, column - strlen(word));
        }
        if (buffer[strlen(buffer)-1] == '\n') {
            row++;
            column = 0;
        }
    }

    printf("The word '%s' occurs %d times in the file.\n", word, count);

    fclose(file);
    return 0;
}
