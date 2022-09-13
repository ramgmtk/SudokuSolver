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