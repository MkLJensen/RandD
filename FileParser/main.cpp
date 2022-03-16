#include <iostream>
#include <memory>
#include "globals.h"
#include "FileParser.h"
#include "nnLayer.h"


int main() {


    FileParser *fileP = new FileParser();
    /*
    std::string out;
    if (fileP->openfile("C:\\Users\\Mikke\\OneDrive - Aarhus Universitet\\Skrivebord\\CIVIL_3_SEMESTER\\RnD\\repo\\RandD\\FileParser\\testFile.txt") != -1){
        out = fileP->readfile();
        fileP->closefile();
    }*/

    std::string out = "0.1,0.12,0.31,0.45,0.21,0.87,0.9,FA,1,FB,0.1,0.2,0.3,0.4,0.5,0.6,0.7\r\n0.2,0.2,0.04,0.4,FA,1,FB,0.4,0.3,0.2,0.1\r\n0.5,0.1,0.9,0.2,0.9,0.7,FA,0,FB,0.2,0.4,0.6,0.8,0.5,0.3";

    std::vector<nnLayer> *nnV = fileP->parseString(out);

    for (int i = 0; i < nnV->size(); ++i) {
        std::cout << "Layer " << i << ":\r\nWeights: ";
        for (int j = 0; j < nnV->at(i).getNNeurons(); ++j) {
            std::cout << (nnV->at(i).getWeights().get()[j]) << ", ";
        }
        std::cout << std::endl << "ActivationFunction: " << nnV->at(i).getActFunction();

        std::cout << std::endl << "Bias: ";
        for (int j = 0; j < nnV->at(i).getNNeurons(); ++j) {
            std::cout << (nnV->at(i).getBias().get()[j]) << ", ";
        }
        std::cout << std::endl;
    }




    return 0;
}
