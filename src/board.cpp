#include <string>
#include <iostream>

#include "board.h"

//Board Constructor
//Setup and initialize the starting array.
//Dynamically allocate the stack structure.
board::board(const std::string& numbers) {
    this->initial_num = 0;
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
            int value = this->arr[i][j];
            if (value == 0) continue;
            int box = (i/3)*3 + j/3;
            if (col_arr[j][value-1] || row_arr[i][value-1] || box_arr[box][value-1]) {
                throw "Constructing an invalid board.";
            } else {
                col_arr[j][value-1] = row_arr[i][value-1] = box_arr[box][value-1] = 1;
                this->initial_num += 1;
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
    if (this->col_arr[entry.col][entry.value-1] || this->row_arr[entry.row][entry.value-1] || this->box_arr[entry.box][entry.value-1])
        return false;
    else return true;
}

void board::insert_num(number entry) {
    if (this->valid(entry)) {
        this->arr[entry.row][entry.col] = entry.value;
        this->col_arr[entry.col][entry.value-1] = this->row_arr[entry.row][entry.value-1] = 
            this->box_arr[entry.box][entry.value-1] = 1;
    }
    else throw std::domain_error("Not a valid location on board for number.\n");
}

void board::remove_num(number removal) {
    this->arr[removal.row][removal.col] = 0;
    this->row_arr[removal.row][removal.value - 1] = 0;
    this->col_arr[removal.col][removal.value - 1] = 0;
    this->box_arr[removal.box][removal.value - 1] = 0;
}

//Main function which will attempts to fill out the board.
void board::solver() {
    bool success = true;
    int new_numbers = (this->size * this->size) - this->initial_num;
    int i = 0;
    int j = 0;
    int n = 1;
    for (int k = 0; k < new_numbers; k++) {
        for (; i < this->size; i++) {
            success = false;
            for (; j < this->size; j++) {
                for (; n < this->size+1; n++) {
                    try {
                        number num(k, i, j, ((i/3)*3 + j/3), n);
                        this->insert_num(num);
                        stack->insert_head(num);
                        success = true;
                        break;
                    } catch (const std::domain_error) {
                        continue;
                    }
                }
                n = 1;
                if (success) break;
            }
            j = 0;
            if (success) break;
        }
        if (!success) {
            if (stack->is_empty()) throw std::domain_error("No solution exists.\n");
            number r_num = stack->delete_head();
            k = r_num.num - 1;
            i = r_num.row;
            j = r_num.col;
            n = r_num.value + 1;
            this->remove_num(r_num);
        } else i = 1; //is this necessary?
    }
}