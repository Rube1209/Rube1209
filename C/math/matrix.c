#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    double *data;
} Matrix;

Matrix* createMatrix(int row, int col) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed for matrix structure.\n");
        exit(EXIT_FAILURE);
    }
    matrix->row = row;
    matrix->col = col;
    matrix->data = (double*)malloc(row * col * sizeof(double));
    if (!matrix->data) {
        fprintf(stderr, "Memory allocation failed for matrix data.\n");
        free(matrix);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < row * col; i++) {
        matrix->data[i] = 0.0; // Initialize elements to 0
    }

    return matrix;
}

void freeMatrix(Matrix* matrix) {
    if (matrix) {
        free(matrix->data);
        free(matrix);
    }
}

void setElement(Matrix* matrix, int row, int col, double value) {
    if (row >= 0 && row < matrix->row && col >= 0 && col < matrix->col) {
        matrix->data[row * matrix->col + col] = value;
    }
}

double getElement(Matrix* matrix, int row, int col) {
    if (row >= 0 && row < matrix->row && col >= 0 && col < matrix->col) {
        return matrix->data[row * matrix->col + col];
    }
    fprintf(stderr, "Index out of bounds when accessing matrix element.\n");
    return 0.0; // 或者其他适当的错误处理
}

void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            printf("%lf ", matrix->data[i * matrix->col + j]);
        }
        printf("\n");
    }
}

void inputMatrixByRow(Matrix* matrix) {
    for (int i = 0; i < matrix->row; i++) {
        printf("Enter elements for row %d: ", i + 1);
        for (int j = 0; j < matrix->col; j++) {
            scanf("%lf", &matrix->data[i * matrix->col + j]);
        }
    }
}

Matrix* getMinor(Matrix* matrix, int row, int col) {
    Matrix* minor = createMatrix(matrix->row - 1, matrix->col - 1);
    int minorRow = 0, minorCol;

    for (int i = 0; i < matrix->row; i++) {
        if (i == row) continue;
        minorCol = 0;
        for (int j = 0; j < matrix->col; j++) {
            if (j == col) continue;
            minor->data[minorRow * minor->col + minorCol] = matrix->data[i * matrix->col + j];
            minorCol++;
        }
        minorRow++;
    }
    return minor;
}

double calculateDeterminant(Matrix* matrix) {
    if (matrix->row != matrix->col) {
        fprintf(stderr, "Determinant can only be calculated for square matrices.\n");
        return 0.0;
    }

    if (matrix->row == 1) {
        return matrix->data[0];
    }

    if (matrix->row == 2) {
        return matrix->data[0] * matrix->data[3] - matrix->data[1] * matrix->data[2];
    }

    double determinant = 0.0;
    for (int col = 0; col < matrix->col; col++) {
        Matrix* minor = getMinor(matrix, 0, col);
        determinant += (col % 2 == 0 ? 1 : -1) * matrix->data[col] * calculateDeterminant(minor);
        freeMatrix(minor);
    }
    return determinant;
}

int main() {
    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    Matrix* matrix = createMatrix(rows, cols);
    inputMatrixByRow(matrix);
    printMatrix(matrix);

    if (rows == cols) {
        double determinant = calculateDeterminant(matrix);
        printf("Determinant: %lf\n", determinant);
    } else {
        printf("Determinant calculation skipped for non-square matrix.\n");
    }

    freeMatrix(matrix);
    return 0;
}
