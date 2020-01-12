#define N 18
#define M 17

int main(int argc, char *argv[]) {
    int A[N][N];
    int B[N][N];
    int C[N][N];

    // GEMM
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = C[i][j] + N*C[i][j];
            for(int k = 0; k < N ;k++) {
                C[i][j] = C[i][j] + N*A[i][k]*B[k][j];
            }
        }
    }

    // Addition de matrices
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Produit de matrices
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = 0;
            for(int k = 0; k < N ;k++) {
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }

    // Transposee
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            B[j][i] = A[i][j];
        }
    }
}