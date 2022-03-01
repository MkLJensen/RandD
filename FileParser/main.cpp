#include <iostream>
#include <memory>
#include "globals.h"
#include "FileParser.h"
#include "nnLayer.h"


int main() {

    std::string out;

    FileParser *fileP = new FileParser();
    if (fileP->openfile("C:\\Users\\MIKKELJENSEN\\Desktop\\CIVIL_3_SEMESTER\\RnD\\RandD\\FileParser\\testFile.txt") != -1){
        out = fileP->readfile();
        fileP->closefile();
    }



    std::cout << out << std::endl;






    /*int len = 3;
    std::shared_ptr<CUSTOMTYPE> weights(new CUSTOMTYPE[len]);
    std::shared_ptr<CUSTOMTYPE> bias(new CUSTOMTYPE[len]);

    weights.get()[2] = 0.72321;
    std::shared_ptr<nnLayer> layer1(new nnLayer(3, weights, bias, 1));

    std::cout << layer1->getWeights().get()[2] << std::endl;*/


    return 0;
}
