#define N 18
#define M 17

int main(int argc, char *argv[]) {
    int x[N];
    int y[N];
    int mat[N][N];

    // Test 1
    for (int i = 0; i < N; i++) {
        int tmp = 0;
        for (int j = 0; j < N; j++) {
            tmp = tmp + mat[i][j] * x[j];
        }
        y[i] = N*tmp + M*y[i];
    }
}