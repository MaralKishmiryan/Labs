#include <iostream>
#include <vector>

void transpose(const std::vector<std::vector<char>>& matrix, std::vector<std::vector<char>>& transposed) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    transposed.resize(cols, std::vector<char>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
}

int main() {
    int rows, cols;

    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols));
    std::vector<std::vector<char>> transposed;

    std::cout << "Enter the matrix elements (single characters):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << "Element[" << i << "][" << j << "]: ";
            std::cin >> matrix[i][j];
        }
    }

    transpose(matrix, transposed);

    std::cout << "Transposed matrix:\n";
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            std::cout << transposed[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
