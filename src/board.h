#include <string>
#include "structure.h"

//Board class
//has struct number which keeps track of the position in the board a number is at.
//the number 0 denotes an empty space in the board/
class board {
    private:
        //containers for checking the board
        int **arr;
        int **col_arr;
        int **row_arr;
        int **box_arr;
        unsigned int size;
        struct number {
            unsigned int num;
            unsigned int row;
            unsigned int col;
            unsigned int box;
        };
        linked_list<number>* stack;
    public:
        board() : size(9), stack(nullptr) {}
        board(const std::string& numbers);
        ~board();
        void print();
        bool valid(number entry);
};