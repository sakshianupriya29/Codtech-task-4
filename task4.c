#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Compress the file
void compressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("File error during compression!\n");
        return;
    }

    char ch, prev = '\0';
    int count = 1;

    while ((ch = fgetc(in)) != EOF) {
        if (ch == prev) {
            count++;
        } else {
            if (prev != '\0') {
                fputc(prev, out);
                fprintf(out, "%d", count);
            }
            prev = ch;
            count = 1;
        }
    }

    if (prev != '\0') {
        fputc(prev, out);
        fprintf(out, "%d", count);
    }

    fclose(in);
    fclose(out);
    printf("Compression complete. Output saved to: %s\n", outputFile);
}

// Decompress the file
void decompressFile(const char* inputFile, const char* outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("File error during decompression!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(in)) != EOF) {
        if (isalpha(ch) || ispunct(ch) || ch == ' ') {
            int count = 0;
            char numStr[10];
            int i = 0;
            char digit;

            while ((digit = fgetc(in)) != EOF && isdigit(digit)) {
                numStr[i++] = digit;
            }
            numStr[i] = '\0';
            ungetc(digit, in);

            count = atoi(numStr);
            for (int j = 0; j < count; j++)
                fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression complete. Output saved to: %s\n", outputFile);
}

// Main menu
int main() {
    int choice;
    char inputFile[100], outputFile[100];

    while (1) {
        printf("\n--- Run-Length Encoding Tool ---\n");
        printf("1. Compress a file\n");
        printf("2. Decompress a file\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        switch (choice) {
            case 1:
                printf("Enter input file name: ");
                scanf("%s", inputFile);
                printf("Enter output (compressed) file name: ");
                scanf("%s", outputFile);
                compressFile(inputFile, outputFile);
                break;
            case 2:
                printf("Enter compressed file name: ");
                scanf("%s", inputFile);
                printf("Enter output (decompressed) file name: ");
                scanf("%s", outputFile);
                decompressFile(inputFile, outputFile);
                break;
            case 3:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
