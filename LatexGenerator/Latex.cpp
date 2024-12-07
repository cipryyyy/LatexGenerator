#include "Latex.h"

Latex::Latex(std::string p, std::string title, std::string author, std::string date) : path{p} {
    lines.push_back("\\documentclass{article}");
    lines.push_back("");
    lines.push_back("\\title{" + title + "}");
    lines.push_back("\\author{" + author + "}");
    lines.push_back("\\date{" + date + "}");
    lines.push_back("");
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
    lines.push_back("");
    lines.push_back("\\section{" + name + "}");
}
void Latex::newSubSection(std::string name) {
    lines.push_back("");
    lines.push_back("\\subsection{" + name + "}");
}
void Latex::newSubSubSection(std::string name) {
    lines.push_back("");
    lines.push_back("\\subsubsection{" + name + "}");
}
void Latex::addText(std::string text) {
    lines.push_back(text);
}
void Latex::addTOC(bool page_break) {
    lines.insert(lines.begin() + 8, "\\tableofcontents");
    if (page_break) {
        lines.insert(lines.begin() + 9, "\\pagebreak");
    }
}
void Latex::addPagebreak() {
    lines.push_back("\\pagebreak");
}
void Latex::addLibrary(std::string Library_name) {
    libs.push_back(Library_name);
    lines.insert(lines.begin() + 1, "\\usepackage{"+Library_name+"}");
}
void Latex::addTable(Table table, bool black_title, std::string caption, double padding){
    lines.push_back("\\def\\arraystretch{" + std::to_string(padding) + "}");
    lines.push_back("\\begin{table}[htb]");
    lines.push_back("\\centering");
    std::string line = "\\begin{tabular}{";
    for (int i = 0; i < table.getColumns(); i++) {
        line += "|c";
    }
    lines.push_back(line + "|} \\hline");
    line = "";
    for (int i = 0; i < (table.getColumns() * table.getRows()); i++) {
        if (black_title && i < table.getColumns()) {
            line += "\\textbf{" + table[i] + "}";
        } else {
            line += table[i];
        }
        if ((i + 1) % table.getColumns() != 0) {
            line += "&";
        } else {
            line += "\\\\ \\hline";
            lines.push_back(line);
            line = "";
        }
    }

    if (caption != "") {
        lines.push_back("\\caption{" + caption + "}");
    }
    lines.push_back("\\end{tabular}");
    lines.push_back("\\end{table}");
}
void Latex::addImage(std::string image_path, double size, std::string caption) {
    //TODO
}
void Latex::save(std::string file_name) {
    lines.push_back("\\end{document}");
    std::string filePath = path + "/" + file_name + ".tex";
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


// TABLE


Table::Table(int column_number, int rows_number) : cols{column_number}, rows{rows_number} {}

void Table::addElements(std::initializer_list<std::any> list) {
    for (const auto& item : list) {
        std::string value;

        if (item.type() == typeid(std::string)) {
            value = std::any_cast<std::string>(item);
        } else if (item.type() == typeid(const char*)) {
            value = std::string(std::any_cast<const char*>(item));
        } else if (item.type() == typeid(int)) {
            value = std::to_string(std::any_cast<int>(item));
        } else if (item.type() == typeid(double)) {
            value = std::to_string(std::any_cast<double>(item));
        } else if (item.type() == typeid(char)) {
            value = std::string(1, std::any_cast<char>(item));
        } else {
            throw std::runtime_error("Unsupported data type in initializer list.");
        }

        elem.push_back(value);
    }
}
void Table::addElements(const std::vector<std::string>& list) {
    for (const auto& item : list) {
        std::string value = item;
        elem.push_back(value);
    }
}

std::string Table::operator[](int index) noexcept {
    if (index < 0 || index >= elem.size()) {
        return "";
    }
    return elem[index];
}
const std::string Table::operator[](int index) const noexcept{
    if (index < 0 || index >= elem.size()) {
        return "";
    }
    return elem[index];
}

void Table::setColumns(int column_number) {
    cols = column_number;
}
void Table::setRows(int row_number) {
    rows = row_number;
}
int Table::getColumns() const noexcept {
    return cols;
}
int Table::getRows() const noexcept {
    return rows;
}
void Table::addRow(int row_number) noexcept {
    if (row_number < 1) {
        return;
    } else {
        rows += row_number;
    }
}
std::vector<std::string> Table::get_table() noexcept {
    return elem;
}