//
// Created by Mikke on 24-02-2022.
//

#include <sstream>
#include "FileParser.h"
#include <vector>

FileParser::FileParser() {}

FileParser::~FileParser() {
    filedescrip_.close();
}

unsigned int FileParser::openfile(std::string filename) {

    filedescrip_.open(filename);

    if(!filedescrip_){
        return -1;
    } else{
        return 0;
    }
}

unsigned int FileParser::closefile() {
    if (filedescrip_){
        filedescrip_.close();
        return 0;
    } else{
        return -1;
    }
}

std::string FileParser::readfile() {
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(filedescrip_, line)){
        lines.push_back(line);
        lines.push_back("\n"); // Add fake newline, the SD card driver will do this for us
    }

    std::string s;
    for (const auto &piece : lines) s += piece;
    return s;
}

std::vector<nnLayer> FileParser::parseString(std::string inString) {


    std::string temp = inString;

    unsigned int numbersOfNewline = std::count(temp.begin(), temp.end(), '\n');

    // Allocate the numbers of nnLayers Needed
    // TODO NEEDS A CHECK
    auto *layerArray = new std::shared_ptr<nnLayer>[numbersOfNewline];
    std::vector<nnLayer> nnLayerVector;


    // Find first newline pointer
    unsigned int newLinePointer = temp.find('\n');

    for (int i = 0; i<numbersOfNewline; i++) {

        std::string workString = temp.substr(0, newLinePointer);

        nnLayer test = parseline(workString);
        nnLayerVector.push_back(test);
        //layerArray->get()[i] = parseline(workString);

        // Update Temp TO Be without Parsed line and move newlinePointer
        temp = temp.substr(newLinePointer+1, temp.size()-newLinePointer);
        if (!temp.empty()){
            newLinePointer = temp.find('\n');
        }else{
            break;
        }
    }
    return nnLayerVector;
}

nnLayer FileParser::parseline(const std::string inLine) {

    std::smatch SmatchWeights;
    std::smatch SmatchBias;
    std::smatch SmatchAct;

    std::regex_search(inLine.begin(), inLine.end(), SmatchWeights, std::regex("^(.*?)\\FA")); // Weights Regex
    std::regex_search(inLine.begin(), inLine.end(), SmatchBias, std::regex("\\FB(.*?)$")); // Bias Regex
    std::regex_search(inLine.begin(), inLine.end(), SmatchAct, std::regex("\\FA(.*?)\\FB")); // Act function

    std::string weightString = SmatchWeights.str();
    std::string biasString = SmatchBias.str();
    std::string actFunc = SmatchAct.str();

    unsigned int numberOfBias = std::count(biasString.begin(), biasString.end(), ',');
    unsigned int numberOfWeights = std::count(weightString.begin(), weightString.end(), ',');

    unsigned int act = std::stoi(actFunc.substr(actFunc.find(',', 0)+1,
                                                actFunc.find(',', actFunc.find(',', 0))-1));

    std::shared_ptr<CUSTOMTYPE> weights(getWeightsFromSMatch(weightString, numberOfWeights));
    std::shared_ptr<CUSTOMTYPE> bias(getBiasFromSMatch(biasString, numberOfBias));




    nnLayer* bufLayer = new nnLayer(numberOfWeights, weights, bias, act);
    return *bufLayer;
}

std::shared_ptr<CUSTOMTYPE> FileParser::getWeightsFromSMatch(std::string weightString, unsigned int numberOfWeights) {

    std::string buf;
    std::stringstream sstream(weightString);

    std::shared_ptr<CUSTOMTYPE> w(new CUSTOMTYPE[numberOfWeights]);
    for (int i = 0; i < numberOfWeights; ++i) {
        std::getline(sstream, buf, ',');
        // TODO REMEMBER TO FIX WHEN FIXED-POINT
        w.get()[i] = std::stof(buf);
    }

    return w;
}

std::shared_ptr<CUSTOMTYPE> FileParser::getBiasFromSMatch(std::string biasString, unsigned int numberOfBias) {
    // Remove the "FB," from the string
    biasString.replace(biasString.begin(), biasString.begin()+3, "");

    std::string buf;
    std::stringstream sstream(biasString);


    std::shared_ptr<CUSTOMTYPE> b(new CUSTOMTYPE[numberOfBias]);
    for (int i = 0; i < numberOfBias; ++i) {
        std::getline(sstream, buf, ',');
        // TODO REMEMBER TO FIX WHEN FIXED-POINT
        b.get()[i] = std::stof(buf);
    }

    return b;
}



/*int len = 3;
std::shared_ptr<CUSTOMTYPE> weights(new CUSTOMTYPE[len]);
std::shared_ptr<CUSTOMTYPE> bias(new CUSTOMTYPE[len]);

weights.get()[2] = 0.72321;
std::shared_ptr<nnLayer> layer1(new nnLayer(3, weights, bias, 1));

std::cout << layer1->getWeights().get()[2] << std::endl;*/