#include <iostream>
#include "FileParser.h"
#include "nnLayer.h"


int main() {

    std::string out;

    FileParser *fileP = new FileParser();
    if (fileP->openfile("C:\\Users\\Mikke\\OneDrive - Aarhus Universitet\\Skrivebord\\CIVIL_3_SEMESTER\\RnD\\FileParser\\testFile.txt") != -1){
        out = fileP->readfile();
        fileP->closefile();
    }

    int leng = 3;
    std::shared_ptr<ap_fixed<15,1>> weights(new ap_fixed<15,1>[leng]);
    std::shared_ptr<ap_fixed<15,1>> bias(new ap_fixed<15,1>[leng]);

    weights.get()[2] = 0.72321;
    bias.get()[2] = 0.232131;
    std::shared_ptr<nnLayer> layer1(new nnLayer(3, weights, bias, 1));

    std::cout << weights.get()[2]  << std::endl;


    return 0;
}
