#include "stats.h"

double calculate_average(const double *values, size_t count)
{
    if (values == NULL || count == 0) {
        return 0.0;
    }

    double sum = 0.0;

    for (size_t i = 0; i < count; ++i) {
        sum += values[i];
    }

    return sum / (double)count;
}
