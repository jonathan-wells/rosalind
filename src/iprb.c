#include <stdio.h>

#include "../include/file_utils.h"
#include "../include/iprb.h"

float prob_dominant_phenotype(int k, int m, int n) {
    m = (float)m;
    n = (float)n;
    float t = (float)(k + m + n);
    return 1 - (n * (n - 1)) / (t * (t - 1)) - (n * m) / (t * (t - 1)) -
           (m * (m - 1)) / (4 * t * (t - 1));
}

void iprb(const char *filename) {
    int k;
    int m;
    int n;
    char *input_str = read_single_line_input(filename);
    sscanf(input_str, "%d %d %d", &k, &m, &n);
    double p_dom_phenotype = prob_dominant_phenotype(k, m, n);
    printf("%f\n", p_dom_phenotype);
}
