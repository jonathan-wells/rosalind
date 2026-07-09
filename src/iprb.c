float prob_dominant_phenotype(int k, int m, int n) {
    m = (float)m;
    n = (float)n;
    float t = (float)(k + m + n);
    return
        1 -
        (n * (n-1))/(t * (t-1)) -
        (n * m)/(t * (t-1)) -
        (m * (m-1))/(4 * t * (t-1));
}
