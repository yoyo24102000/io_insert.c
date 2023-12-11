#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int simple_fnmatch(const char *pattern, const char *string) {
    while (*pattern != '\0' && *string != '\0') {
        if (*pattern == '?') {
            pattern++;
            string++;
        } else if (*pattern == '*')  {
            while (*(pattern + 1) == '*')
                pattern++;

            if (*(pattern + 1) == '\0')
                return 0; // Matched

            const char *nextPattern = pattern + 1;
            const char *nextString = string;

            while (*nextString != '\0') {
                int result = simple_fnmatch(nextPattern, nextString);
                if (result == 0)
                    return 0;

                nextString++;
            }

            return -1;
        } else if (*pattern == '\\') {
            pattern++; // Skip the escape character

            if (*pattern != *string)
                return -1;

            pattern++;
            string++;
        } else {
            if (*pattern != *string)
                return -1;

            pattern++;
            string++;
        }
    }

    if (*pattern == '\0' && *string == '\0')
        return 0; // Matched

    return -1; // No match found
}

int main(void) {
    const char *pattern = "te?t*";
    const char *string = "test123";

    int result = simple_fnmatch(pattern, string);

    printf("Result: %d\n", result);

    return 0;
}
