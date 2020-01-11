
void int_gemv(int i0, int i1, int j0, int j1, int alpha, int beta, int** A, int* x, int* y) {
    for (int i = i0; i < i1; i++) {
        int tmp = 0;
        for (int j = j0; j < j1; j++) {
            tmp = A[i][j] * x[j];
        }
        y[i] = alpha*tmp + beta*y[i];
    }
}