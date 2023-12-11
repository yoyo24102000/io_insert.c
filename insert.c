#define _POSIX_C_SOURCE 200809L
#include <stdio.h>

int insert_line(const char *file_in, const char *file_out, const char *content,
                size_t n) {
    if (file_in == NULL || file_out == NULL || content == NULL) {
        return -1;
    }

    FILE *input = fopen(file_in, "r");
    if (input == NULL) {
        warn("Error opening input file");
        return -1;
    }
    FILE *output = fopen(file_out, "w");
    if (output == NULL) {
        warn("Error opening output file");
        fclose(input);
        return -1;
    }
    size_t current_line = 0;
    char *line = NULL;
    size_t line_length = 0;
    while (current_line < n && getline(&line, &line_length, input) != -1) {
        fputs(line, output);
        current_line++;
    }

    fputs(content, output);
    while (current_line < n) {
        fputc('\n', output);
        current_line++;
    }
    while (getline(&line, &line_length, input) != -1) {
        fputs(line, output);
    }
    free(line);
    fclose(input);
    fclose(output);

    return current_line + 1;
