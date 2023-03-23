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

    printf("Enter the substring to search for: ");
    scanf("%s", word);

    FILE file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    while (fgets(buffer, 100, file) != NULL) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        column = 0;
        char ptr = buffer;
        while ((ptr = strstr(ptr, word)) != NULL) {
            count++;
            printf("'%s' found at row %d, column %d\n", word, row, column + (ptr - buffer));
            ptr++;
        }
        row++;
    }

    printf("The substring '%s' occurs %d times in the file.\n", word, count);

    fclose(file);
    return 0;
}
