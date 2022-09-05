#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void parseData(const std::string& data) {
    //std::stringstream ss;
    std::cout << data << std::endl;
}

int main(int argc, char** argv) {
    std::ifstream infile;
    std::string data;
    if (argc < 2) throw std::invalid_argument("./main <input file>\n");
    infile.open(argv[1]);
    while(std::getline(infile, data)) {
        parseData(data);
    }
    
    return 0;
}