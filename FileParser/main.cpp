#include <iostream>
#include <memory>
#include "globals.h"
#include "FileParser.h"
#include "nnLayer.h"


int main() {

    std::string out;

    FileParser *fileP = new FileParser();
    if (fileP->openfile("C:\\Users\\Mikke\\OneDrive - Aarhus Universitet\\Skrivebord\\CIVIL_3_SEMESTER\\RnD\\repo\\RandD\\FileParser\\testFile.txt") != -1){
        out = fileP->readfile();
        fileP->closefile();
    }

    std::vector<nnLayer> nnV = fileP->parseString(out);

    for (int i = 0; i < nnV.size(); ++i) {
        std::cout << "Layer " << i << ": ";
        for (int j = 0; j < nnV.at(i).getNNeurons(); ++j) {
            std::cout << (nnV.at(i).getWeights().get()[j]) << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}
