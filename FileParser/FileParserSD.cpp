/*
 * FileParserSD.cpp
 *
 *  Created on: 8. mar. 2022
 *      Author: Mikkel
 * 	Implementation of SD Card is inspired from Kim Bjerge, Aarhus University
 */
#include "FileParserSD.h"

/**
 * Initial Paths of the SD card is set
 */
FileParserSD::FileParserSD() {
	pathName = "0:/";  			/* Set Initial Path of SD Card */
	fileName = "";				/* Set Initial Filename to "null" */
}

FileParserSD::~FileParserSD() {
    closefile();
}

/**
 * Open the file with the @param filename
 */
int FileParserSD::openfile(std::string filename) {
	FRESULT result;

	/* Return Failure if card is not mounted */
	if(!isMounted){
		return XST_FAILURE;
	}

	/* Open the file in always read mode and only the existing file */
	result = f_open(&mFIL, filename.c_str(), FA_OPEN_EXISTING | FA_READ);
	if(result){
		return XST_FAILURE;
	}

	/* Set the file pointer to the start of the file */
	result = f_lseek(&mFIL, 0);
	if(result){
			return XST_FAILURE;
	}
	return XST_SUCCESS;
}

/**
 * Mount the File in the system
 */
int FileParserSD::mount(bool remount)
{

	FRESULT result;
	if (!isMounted or remount) { /* Ensure that we aren't already mounted */
		result = f_mount(&mFatFS, pathName.c_str(), 0);

		if (result != FR_OK) { /* If Mounts fails, return error */
			return XST_FAILURE;
		}
		isMounted = true;
	}
	return XST_SUCCESS;
}

/**
 * Close the file descriptor correctly
 */
int FileParserSD::closefile() {
	FRESULT result = f_close(&mFIL);
	if (result) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

std::string FileParserSD::readfile(bool fromStart) {

	//TODO FIX THE STATIC BUFFER SIZE
	char buf[MAX_INPUT_FILE_CHAR_SIZE];

	FRESULT result;
	if (fromStart) { /* Move filepointer to start */
		result = f_lseek(&mFIL, 0);
		if (result) {
			return "FF";
		}
	}
	result = f_read(&mFIL, (void*)buf, sizeof(buf), &NumberOfBytesRead);
	if (result) {
		return "FF";
	}

	std::string ret(buf, buf+NumberOfBytesRead);

	return ret;
}

/**
 * Parse the whole string from config file to a nnLayer Vector
 */
std::vector<nnLayer> FileParserSD::parseString(std::string inString) {

    std::string temp = inString;

    unsigned int numbersOfNewline = std::count(temp.begin(), temp.end(), 'A');

    // Allocate the numbers of nnLayers Needed
    std::vector<nnLayer> nnLayerVector;

    // Find first newline pointer
    unsigned int newLinePointer = temp.find("\r\n");

    for (unsigned int i = 0; i<numbersOfNewline; i++) {

        std::string workString = temp.substr(0, newLinePointer);

        nnLayer buf = parseline(workString);
        nnLayerVector.push_back(buf);

        // Update Temp TO Be without Parsed line and move newlinePointer
        temp = temp.substr(newLinePointer+2, temp.size()-newLinePointer);
        if (!temp.empty()){
            newLinePointer = temp.find("\r\n");
        }else{
            break; // TODO PROB NOT NEEDED
        }
    }
    return nnLayerVector;
}

nnLayer FileParserSD::parseline(const std::string inLine) {

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

std::shared_ptr<CUSTOMTYPE> FileParserSD::getWeightsFromSMatch(std::string weightString, unsigned int numberOfWeights) {

    std::string buf;
    std::stringstream sstream(weightString);

    std::shared_ptr<CUSTOMTYPE> w(new CUSTOMTYPE[numberOfWeights]);
    for (unsigned int i = 0; i < numberOfWeights; ++i) {
        std::getline(sstream, buf, ',');
        // TODO REMEMBER TO FIX WHEN FIXED-POINT
        w.get()[i] = std::stof(buf);
    }

    return w;
}

std::shared_ptr<CUSTOMTYPE> FileParserSD::getBiasFromSMatch(std::string biasString, unsigned int numberOfBias) {
    // Remove the "FB," from the string
    biasString.replace(biasString.begin(), biasString.begin()+3, "");

    std::string buf;
    std::stringstream sstream(biasString);

    std::shared_ptr<CUSTOMTYPE> b(new CUSTOMTYPE[numberOfBias]);
    for (unsigned int i = 0; i < numberOfBias; ++i) {
        std::getline(sstream, buf, ',');
        // TODO REMEMBER TO FIX WHEN FIXED-POINT
        b.get()[i] = std::stof(buf);
    }

    return b;
}
