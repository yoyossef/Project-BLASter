#define N 18
#define M 17

int main(int argc, char *argv[]) {
    int u[N];
    int v[N];
    int w[N];

    // Test 1
    for ( int i = 0; i < 1; i++) {
        v[i] = M;
    }

    // Test 2
    for (int i = 0; i < 1; i++) {
        int tmp = v[i];
        v[i] = u[i];
        u[i] = tmp;
    }

    // Test 3
    for (int i = 0; i < 1; i++) {
        w[i] = N * v[i] + w[i];
    }
}