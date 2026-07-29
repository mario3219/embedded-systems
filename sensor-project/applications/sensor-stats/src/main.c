#include "stats.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_value(const char *text, double *result)
{
    char *end = NULL;

    errno = 0;
    const double value = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0') {
        return -1;
    }

    *result = value;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s VALUE [VALUE ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const size_t count = (size_t)(argc - 1);
    double *values = malloc(count * sizeof(*values));

    if (values == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (parse_value(argv[i + 1], &values[i]) != 0) {
            fprintf(stderr, "Invalid number: %s\n", argv[i + 1]);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("Average: %.2f\n", calculate_average(values, count));

    free(values);
    return EXIT_SUCCESS;
}
