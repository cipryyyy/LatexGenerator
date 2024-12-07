#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Latex.h"
using namespace std;

std::vector<std::string> fileReader(std::string path);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        std::vector<std::string> lines = fileReader(path);
        
    } else {
        std::vector<std::any> table = {1,2,3,4,"testo", 'c', 5, 9};
        Latex doc("/Users/macbook/Documents/Github/LatexGenerator", "Prova", "Cipriani", "Oggi");
        doc.newSection("This is my first latex project");
        Table myTable (3,3);
        myTable.add_elements({1,2,3,"testa", "Coda", '5', 3, 'j', "testo"});
        doc.addTable(myTable, true, "", 2);

        doc.save();
    }
    return 0;
}

std::vector<std::string> fileReader(std::string path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot read the file" + path);
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return(lines);
}