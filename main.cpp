#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include "Latex.h"
using namespace std;

bool isBlank(const std::string& str);
std::vector<std::string> fileReader(std::string path);
std::string imageCheck(const std::string& line);
void texGen(std::vector<std::string> lines, std::string outputName);

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string path = argv[1];
        std::string output;
        std::vector<std::string> lines = fileReader(path);
        if (argc > 2) {
            output = argv[2];
        } else {
            output = "source";
        }
        texGen(lines, output);
    } else {
        std::string path;
        std::string output;
        cout << "Source file: ";
        cin >> path;
        std::vector<std::string> lines = fileReader(path);
        cout << "Output file name: ";
        cin >> output;
        
        texGen(lines, output);
    }
    return 0;
}

void texGen(std::vector<std::string> lines, std::string outputName) {
    std::string title, author, date;
    bool tableMode = false;
    Table table;

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
        if (isBlank(line)) {
            continue;
        }
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
            if (line.substr(1, 3) == "IMG") {
                std::string path = imageCheck(line);
                doc.addImage(path);
            }
            if (line.substr(1, 5) == "TABLE") {
                if (!tableMode) {
                    int cols;

                    std::stringstream ss(line);
                    ss.ignore(7, ' ');
                    ss >> cols;
                    table.setColumns(cols);
                    tableMode = true;
                } else {
                    doc.addTable(table, true);  
                    tableMode = false;
                }
            }
        } else {
            if (tableMode) {
                std::vector<std::string> elems;
                std::stringstream ss(line);
                std::string temp;

                while (std::getline(ss, temp, ',')) {
                    temp.erase(0, temp.find_first_not_of(' '));
                    temp.erase(temp.find_last_not_of(' ') + 1);
                    elems.push_back(temp);
                }

                if (elems.size() > 5) {
                    elems.resize(5);
                }

                table.addRow();
                table.addElements(elems);
            } else {
                doc.addText(line);
            }
        }
    }
    
    doc.save(outputName); 
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
bool isBlank(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    for (char ch : str) {
        if (!std::isspace(ch)) {
            return false;
        }
    }
    return true;
}
std::string imageCheck(const std::string& line) {
    return "";
    //TODO
}