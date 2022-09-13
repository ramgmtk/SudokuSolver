#include <string>

class board {
    private:
        int **arr;
        int size;
    public:
        board() : size(9) {}
        board(const std::string& numbers);
        ~board();
        void print();
};