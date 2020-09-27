#include <stdio.h>
#include <stdlib.h>

float pow(int power);
float *create_matrix(int dimension);
float *create_vector(int dimension);
float *transpose(int dimension, float *matrix);
float calculate_determinant(int dimension, float *matrix);
float *make_smaller_matrix(int n, int column, float *matrix);
float *matrix_vector_multiplication(int dimension, float *matrix, float *vector);
void show_matrix(int dimension, float *matrix);
void show_vector(int dimension, float *vector);
void first_task();
void second_task();
void third_task();

int main() {
    third_task();

    return 0;
}

void first_task() {
    int dimension = 2;

    float *matrix = create_matrix(dimension);

    float determinant = calculate_determinant(dimension, matrix);

    printf("%.2f", determinant);
}

void second_task() {
    int dimension = 3;

    float *matrix = create_matrix(dimension);

    float determinant = calculate_determinant(dimension, matrix);

    printf("%.2f", determinant);
}

void third_task() {
    float *vectors = create_matrix(3);
    float *basis_vectors = transpose(3, vectors);
    free(vectors);
    int amount_of_vectors;
    scanf("%d", &amount_of_vectors);

    float determinant = calculate_determinant(3, basis_vectors);

    float *vector;
    for (int i = 0; i < amount_of_vectors; i++) {
        vector = create_vector(3);
        if (determinant == 0) continue;
        vector = matrix_vector_multiplication(3, basis_vectors, vector);
        show_vector(3, vector);
        free(vector);
    }
    free(basis_vectors);

}

float *matrix_vector_multiplication(int dimension, float *matrix, float *vector) {
    float *resulting_vector = malloc(dimension * sizeof(float));
    float value;

    for (int i = 0; i < dimension; i++) {
        value = 0;
        for (int j = 0; j < dimension; j++) {
            value += *(matrix + dimension * i + j) * *(vector + j);
        }
        *(resulting_vector + i) = value;
    }

    return resulting_vector;
}

float calculate_determinant(int dimension, float *matrix) {
    if (dimension == 1) {
        return *(matrix);
    }

    float determinant = 0;

    for (int i = 0; i < dimension; i++) {
        float *smaller_matrix = make_smaller_matrix(dimension, i, matrix);
        float minor = calculate_determinant(dimension - 1, smaller_matrix);
        determinant += *(matrix + i) * pow(i) * minor;
        free(smaller_matrix);
    }

    return determinant;
}

float *create_matrix(int dimension) {
    float *matrix = malloc(dimension * dimension * sizeof(float));
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            scanf("%f", matrix + i * dimension + j);
        }
    }

    return matrix;
}

float *create_vector(int dimension) {
    float *vector = malloc(dimension * sizeof(float));
    for (int i = 0; i < dimension; i++) {
        scanf("%f", vector + i);
    }

    return vector;
}

float *transpose(int dimension, float *matrix) {
    float *transposed_matrix = malloc(dimension * dimension * sizeof(float));

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            *(transposed_matrix + dimension * i + j) = *(matrix + dimension * j + i);
        }
    }

    return transposed_matrix;
}

float *make_smaller_matrix(int n, int column, float *matrix) {
    int dimension = n - 1;
    float *temporary_matrix = malloc(dimension * dimension * sizeof(float));

    for (int i = 0; i < dimension; i++) {
        for (int j = 0, columns_in_old_matrix = 0; j < dimension; j++, columns_in_old_matrix++) {
            if (j == column) {
                columns_in_old_matrix++;
            }
            *(temporary_matrix + i * dimension + j) = *(matrix + (i + 1) * n + columns_in_old_matrix);
        }

    }

    return temporary_matrix;
}

void show_matrix(int dimension, float *matrix) {
    printf("-----------------------------------\n");
    printf("%dx%d matrix\n", dimension, dimension);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%.2f ", *(matrix + i * dimension + j));
        }
        printf("\n");
    }
    printf("-----------------------------------\n");
}

void show_vector(int dimension, float *vector) {
    for (int i = 0; i < dimension; i++) {
        printf("%f ", *(vector + i));
    }
}

float pow(int power) {
    float result = 1;

    for (int i = 0; i < power; i++) {
        result *= -1;
    }

    return result;
}