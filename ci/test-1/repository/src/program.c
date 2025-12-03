#include <stdio.h>
#include <stdlib.h>

/* This program will run as root and get the flag! */
int main(void) {
    const char *filename = "/flag";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("\n\033[0m%s\n\n", buffer);
    }

    fclose(file);
    return 0;
}