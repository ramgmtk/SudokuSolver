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
        int initial_num;
        unsigned int size;
        struct number {
            unsigned int num;
            unsigned int row;
            unsigned int col;
            unsigned int box;
            unsigned int value;
            number(int n, int r, int c, int b, int v) : num(n), row(r), col(c), box(b), value(v) {}
            number() {}
        };
        linked_list<number>* stack;
    protected:
        bool valid(number entry);
        void insert_num(number entry);
        void remove_num(number entry);
    public:
        board() : size(9), initial_num(0), stack(nullptr) {}
        board(const std::string& numbers);
        ~board();
        void print();
        void solver();
};