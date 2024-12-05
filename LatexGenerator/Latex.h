#include <fstream>  //Handles the file stream

#ifndef Latex_h
#define Latex_h

class Latex {
    private:
    std::string path;
    std::vector<std::string> lines;

    public:
    Latex(std::string p) : path{p} {}
    Latex(Latex& obj) : path{obj.path} {
        lines = obj.lines;
    }
    Latex(Latex&& obj) : path{obj.path} {
        lines = obj.lines;

        obj.path = "";
        obj.lines.clear();
    }

    //Copy and move assignment
    Latex& operator= (Latex& copy) noexcept {
        if (this == &copy) {
            return *this;
        }
        path = copy.path;
        lines = copy.lines;
        
        return *this;
    }
    Latex& operator= (Latex&& move) noexcept {
        if (this == &move) {
            return *this;
        }
        path = move.path;
        lines = move.lines;
        
        move.path = "";
        move.lines.clear();
        
        return *this;
    }

    //methods
    void newSection(std::string section);
    void newSubSection(std::string sub_section);
    void newSubSubsection(std::string sub_sub_section);
    void addText(std::string text);
};

#endif //Latex_h