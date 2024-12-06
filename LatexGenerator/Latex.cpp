#include "Latex.h"
#include <iostream>
#include <vector>

Latex::Latex(std::string p, std::string title, std::string author, std::string date) : path{p} {
    lines.push_back("\\documentclass{article}");
    lines.push_back("\\title{" + title + "}");
    lines.push_back("\\author{" + author + "}");
    lines.push_back("\\date{" + date + "}");
    lines.push_back("\\begin{document}");
    lines.push_back("\\maketitle");


}
Latex::Latex(Latex& obj) : path{obj.path} {
    lines = obj.lines;
}
Latex::Latex(Latex&& obj) : path{obj.path} {
    lines = obj.lines;

    obj.path = "";
    obj.lines.clear();
}
Latex& Latex::operator= (Latex& copy) noexcept {
    if (this == &copy) {
        return *this;
    }
    path = copy.path;
    lines = copy.lines;
    
    return *this;
}
Latex& Latex::operator= (Latex&& move) noexcept {
    if (this == &move) {
        return *this;
    }
    path = move.path;
    lines = move.lines;
    
    move.path = "";
    move.lines.clear();
    
    return *this;
}

void Latex::newSection(std::string name) {
    lines.push_back("\\section{" + name + "}");
}
void Latex::newSubSection(std::string name) {
    lines.push_back("\\subsection{" + name + "}");
}
void Latex::newSubSubsection(std::string name) {
    lines.push_back("\\subsubsection{" + name + "}");
}
void Latex::addText(std::string text) {
    lines.push_back(text);
}
void Latex::addTOC(bool page_break) {
    lines.insert(lines.begin() + 6, "\\tableofcontents");
    if (page_break) {
        lines.insert(lines.begin() + 7, "\\pagebreak");
    }
}
void Latex::addPagebreak() {
    lines.push_back("\\pagebreak");
}

void Latex::save() {
    lines.push_back("\\end{document}");
    std::string filePath = path + "/source.tex";
    std::ofstream outFile(filePath);

    if (!outFile) {
        std::cout << "Errore";
        return;
    }

    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    std::cout << filePath;
    outFile.close();
}