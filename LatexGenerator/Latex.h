#include <fstream>  //Handles the file stream
#include <any>
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef Latex_h
#define Latex_h

class Table;

class Latex {
    private:
    std::vector<std::string> libs;
    std::string path;
    std::vector<std::string> lines;

    public:
    Latex(std::string p, std::string title = "", std::string author = "", std::string date = "");
    Latex(Latex& obj);
    Latex(Latex&& obj);

    //Copy and move assignment
    Latex& operator= (Latex& copy) noexcept;
    Latex& operator= (Latex&& move) noexcept;

    //methods
    void newSection(std::string section);
    void newSubSection(std::string sub_section);
    void newSubSubSection(std::string sub_sub_section);
    void addText(std::string text);

    void addTOC(bool page_break = true);
    void addPagebreak();
    void addLibrary(std::string Library_name);
    void addTable(Table table, bool black_title = false, std::string caption = "", double padding = 1.5, bool textwidth = false);
    void addImage(std::string image_path, double size = 0.5, std::string caption = "");

    void setA4layout();
    void save(std::string file_name = "source");
};

class Table {
    int rows;
    int cols;
    std::vector<std::string> elem;
public:
    class OutOfIndexException : public std::exception {
        const char* what() const noexcept override {
            return "Index out of bound";
        }
    };
    Table(int column_number = 0, int rows_number = 0);

    void addElements(std::initializer_list<std::any> list);
    void addElements(const std::vector<std::string>& list);
    std::string operator[](int index) noexcept;
    const std::string operator[](int index) const noexcept;
    void setColumns(int column_number = 1);
    void setRows(int row_number = 1);
    int getColumns() const noexcept;
    int getRows() const noexcept;
    void addRow(int row_number = 1) noexcept;
    void clear();
    std::vector<std::string> get_table() noexcept;
};
#endif //Latex_h