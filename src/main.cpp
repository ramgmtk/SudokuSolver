#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "board.h"

int main(int argc, char** argv) {
    std::ifstream infile;
    std::string data, numbers;
    if (argc < 2) throw std::invalid_argument("./main <input file>\n");
    infile.open(argv[1]);
    while(std::getline(infile, data)) {
        numbers += data;
    }
    board b(numbers);
    b.print();
    
    return 0;
}