#include <iostream>
#include "LatexGenerator/Latex.h"
using namespace std;

int main() {
    Latex doc("/Users/macbook/Documents/Github/LatexGenerator", "Prova", "Cipriani", "Oggi");
    doc.newSection("Sec");
    doc.addText("test");
    doc.newSubSection("Sub");
    doc.addText("Oh yeah");
    doc.newSubSubsection("Sub x 2");
    doc.addText("idk");
    doc.addTOC();

    doc.save();
    return 0;
}