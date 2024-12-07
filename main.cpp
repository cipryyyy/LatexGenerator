#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include "Latex.h"
using namespace std;

std::vector<std::string> fileReader(std::string path);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        std::vector<std::string> lines = fileReader(path);
        std::string title, author, date;

        std::stringstream ss(lines[0]);
        std::getline(ss, title, ';');
        std::getline(ss, author, ';');
        std::getline(ss, date, ';');

        title = title.substr(title.find_first_not_of(" "), title.find_last_not_of(" ") + 1 - title.find_first_not_of(" "));
        author = author.substr(author.find_first_not_of(" "), author.find_last_not_of(" ") + 1 - author.find_first_not_of(" "));
        date = date.substr(date.find_first_not_of(" "), date.find_last_not_of(" ") + 1 - date.find_first_not_of(" "));

        lines.erase(lines.begin());

        Latex doc("/Users/macbook/Documents/Github/LatexGenerator", title, author, date);

        for (const std::string& line : lines) {
            if (line[0] == '#') {
                if (line.size() > 3 && line.substr(0, 3) == "###") {
                    doc.newSubSubSection(line.substr(4));
                } else if (line.size() > 2 && line.substr(0, 2) == "##") {
                    doc.newSubSection(line.substr(3));
                } else if (line.size() > 1 && line.substr(0, 1) == "#") {
                    doc.newSection(line.substr(2));
                }
            } else if (line[0] == '@') {
                if (line.substr(1, 3) == "TOC") {
                    doc.addTOC();
                }
            } else {
                doc.addText(line);
            }
        }

        doc.save();
    } else {
        std::vector<std::any> table = {1,2,3,4,"testo", 'c', 5, 9};
        Latex doc("/Users/macbook/Documents/Github/LatexGenerator", "Prova", "Cipriani", "Oggi");
        doc.newSection("This is my first latex project");
        Table myTable (3,3);
        myTable.add_elements({1,2,3,"testa", "Coda", '5', 3, 'j', "testo"});
        doc.addTable(myTable, true, "", 2);

        doc.save("File_name");
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