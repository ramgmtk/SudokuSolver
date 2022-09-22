#include <string>
#include <iostream>

#include "board.h"

//Board Constructor
//Setup and initialize the starting array.
//Dynamically allocate the stack structure.
board::board(const std::string& numbers) {
    this->size = 9;
    if (numbers.length() != this->size * this->size) 
        throw std::invalid_argument("Input file character total != 81\n");

    //setup array
    this->arr = new int*[this->size];
    for (int i = 0; i < this->size; i++) {
        this->arr[i] = new int[this->size];
    }
    for (int i = 0; i < numbers.length(); i++) {
        this->arr[i / this->size][i % this->size] = numbers[i] - '0';
    }

    //setup data structure
    stack = new linked_list<number>();

    //setup arrays for validation check.
    //perform initial validation check.
    col_arr = new int*[this->size];
    row_arr = new int*[this->size];
    box_arr = new int*[this->size];

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
                throw "Constructing an invalid board.";
            } else {
                col_arr[j][num-1] = row_arr[i][num-1] = box_arr[box][num-1] = 1;
            }
        }
    }
}

//Board destructor
//Free memory of structures
board::~board() {
    if (this->arr) {
        for (int i = 0; i < this->size; i++) {
            delete[] arr[i];
            delete[] col_arr[i];
            delete[] row_arr[i];
            delete[] box_arr[i];
        }
        delete[] arr;
        delete[] col_arr;
        delete[] row_arr;
        delete[] box_arr;
    }
    if (stack) delete stack;
}

//Board print function
//output the data in the board
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

//Checks if the board is meets the condition for a sudoku solution.
//called multiple times from the solver function.
bool board::valid(number entry) {
    if (col_arr[entry.col][entry.num-1] || row_arr[entry.row][entry.num-1] || box_arr[entry.box][entry.num-1]) {
        return false;
    } else {
        col_arr[entry.col][entry.num-1] = row_arr[entry.row][entry.num-1] = box_arr[entry.box][entry.num-1] = 1;
        return true;
    }
}