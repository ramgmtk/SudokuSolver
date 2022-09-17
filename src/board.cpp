#include <string>
#include <iostream>

#include "board.h"

board::board(const std::string& numbers) {
    this->size = 9;
    if (numbers.length() != this->size * this->size) 
        throw std::invalid_argument("Input file character total != 81\n");

    this->arr = new int*[this->size];
    for (int i = 0; i < this->size; i++) {
        this->arr[i] = new int[this->size];
    }
    for (int i = 0; i < numbers.length(); i++) {
        this->arr[i / this->size][i % this->size] = numbers[i] - '0';
    }
}

board::~board() {
    if (this->arr) {
        for (int i = 0; i < this->size; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
}

void board::print() {
    std::cout << "-------------------------" << std::endl;
    for (int i = 0; i < this->size; i++) {
        std::cout << "| ";
        for (int j = 0; j < this->size; j++) {
            std::cout << arr[i][j] << " ";
            if (j % 3 == 2) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
        if (i % 3 == 2) {
            std::cout << "-------------------------" << std::endl;
        }
    }
}

bool board::valid() {
    int** col_arr = new int*[this->size];
    int** row_arr = new int*[this->size];
    int** box_arr = new int*[this->size];

    for (int i = 0; i < this->size; i++) {
        col_arr[i] = new int[this->size]();
        row_arr[i] = new int[this->size]();
        box_arr[i] = new int[this->size]();
    }

    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            int num = this->arr[i][j];
            if (num == 0) continue;
            int box = (i/3)*3 + j/3;
            if (col_arr[j][num-1] || row_arr[i][num-1] || box_arr[box][num-1]) {
                //clearing memory
                for (int k = 0; k < this->size; k++) {
                    delete[] col_arr[k];
                    delete[] row_arr[k];
                    delete[] box_arr[k];
                }
                delete[] col_arr;
                delete[] row_arr;
                delete[] box_arr;
                return false;
            } else {
                col_arr[j][num-1] = row_arr[i][num-1] = box_arr[box][num-1] = 1;
            }
        }
    }

    //clearing memory
    for (int i = 0; i < this->size; i++) {
        delete[] col_arr[i];
        delete[] row_arr[i];
        delete[] box_arr[i];
    }
    delete[] col_arr;
    delete[] row_arr;
    delete[] box_arr;

    return true;
}