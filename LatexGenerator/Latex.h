#include <fstream>  //Handles the file stream

#ifndef Latex_h
#define Latex_h

class Latex {
    private:
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
    void newSubSubsection(std::string sub_sub_section);
    void addText(std::string text);
    void addTOC(bool page_break = true);
    void addPagebreak();

    void save();
};

#endif //Latex_h