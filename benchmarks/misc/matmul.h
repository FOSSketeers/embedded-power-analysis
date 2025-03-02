void matmul(int *A, int *B, volatile int *result, int rowsA, int colsA, int rowsB, int colsB) {
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            *(result + i * colsB + j) = 0;
        }
    }

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                *(result + i * colsB + j) += *(A + i * colsA + k) * *(B + k * colsB + j);
            }
        }
    }
}
