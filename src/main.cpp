#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "board.h"

int main(int argc, char** argv) {
    //Read input file and store data inside of the board object.
    std::ifstream infile;
    std::string data, numbers;
    if (argc < 2) throw std::invalid_argument("./main <input file>\n");
    infile.open(argv[1]);
    while(std::getline(infile, data)) {
        numbers += data;
    }
    try {
        board b(numbers);
        b.print();
    } catch(const std::invalid_argument& msg) {
        std::cout << msg.what() << std::endl;
    } catch(const char* msg) {
        std::cout << msg << std::endl;
    }

    return 0;
}