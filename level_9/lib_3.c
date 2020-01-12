void int_gemm(int i0, int i1, int j0, int j1, int k0, int k1, int alpha, int beta, int** A, int** B, int** C) {
    for(int i = i0; i < i1; i++){
        for(int j = j0; j < j1; j++){
            C[i][j] = C[i][j] + beta*C[i][j];
            for(int k = k0; k < k1 ;k++){
                C[i][j] = C[i][j] + alpha*A[i][k]*B[k][j];
            }
        }
    }
}

void int_mat_prod(int i0, int i1, int j0, int j1, int k0, int k1, int** A, int** B, int** C) {
    for(int i = i0; i < i1; i++){
        for(int j = j0; j < j1; j++){
            C[i][j] = 0;
            for(int k = k0; k < k1 ;k++){
                C[i][j] = C[i][j] + A[i][k]*B[k][j];
            }
        }
    }
}

void int_mat_transpose(int i0, int i1, int j0, int j1, int** A, int** B) {
    for(int i = i0; i < i1; i++){
        for(int j = j0; j < j1; j++){
            B[j][i] = A[i][j];
        }
    }
}

void int_mat_addition(int i0, int i1, int j0, int j1, int** A, int** B, int** C) {
    for(int i = i0; i < i1; i++){
        for(int j = j0; j < j1; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}