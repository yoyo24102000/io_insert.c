#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int insert_line(const char *file_in, const char *file_out, const char *content, size_t n) {
    // Check for NULL parameters
    if (file_in == NULL || file_out == NULL || content == NULL) {
        return -1;
    }

    FILE *in = fopen(file_in, "r");
    if (in == NULL) {
        return -1;
    }

    FILE *out = fopen(file_out, "w");
    if (out == NULL) {
        fclose(in);
        return -1;
    }

    char *line = NULL;
    size_t line_len = 0;
    ssize_t read;
    size_t current_line = 0;

    while (current_line < n) {
        if (fputs("\n", out) == EOF) {
            fclose(in);
            fclose(out);
            free(line);
            return -1;
        }
        current_line++;
    }

    while ((read = getline(&line, &line_len, in)) != -1) {
        if (current_line == n) {
            if (fputs(content, out) == EOF) {
                fclose(in);
                fclose(out);
                free(line);
                return -1;
            }
        }
        if (fputs(line, out) == EOF) {
            fclose(in);
            fclose(out);
            free(line);
            return -1;
        }
        current_line++;
    }

    fclose(in);
    fclose(out);
    free(line);

    return current_line;
}

int compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        return -1;
    }

    int c1, c2;

    while ((c1 = fgetc(f1)) != EOF) {
        c2 = fgetc(f2);
        if (c1 != c2) {
            fclose(f1);
            fclose(f2);
            return 0;
        }
    }

    fclose(f1);
    fclose(f2);

    return 1;
}

int main() {
    const char *file_in = "input.txt";
    const char *file_out = "output.txt";
    const char *content = "This is the new content";
    size_t n = 2;

    int result = insert_line(file_in, file_out, content, n);

    if (result != -1) {
        printf("Operation successful. Number of lines in %s: %d\n", file_out, result);
    } else {
        printf("Operation failed.\n");
    }

    if (compare_files(file_out, "expected_output.txt") == 1) {
        printf("Test passed: Output matches expected result.\n");
    } else {
        printf("Test failed: Output does not match expected result.\n");
    }

    return 0;
}
