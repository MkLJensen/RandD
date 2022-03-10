#include <iostream>
#include "xstatus.h"
#include "FileParserSD.h"
#include "nnLayer.h"



int main(int argc, char *argv[])
{

	std::string out;

	FileParserSD *fileP = new FileParserSD();
	if(fileP->mount()){
		return 0;
	}
	if(fileP->openfile("testFile.txt")){
		return 0;
	}
	out = fileP->readfile();
	if(out == "FF"){
		fileP->closefile();
		return 0;
	}

	if(fileP->closefile()){
		return 0;
	}
	std::vector<nnLayer> nnV = fileP->parseString(out);

	/*
	for (int i = 0; i < nnV.size(); ++i) {
		std::cout << "Layer " << i << ": ";
	    for (int j = 0; j < nnV.at(i).getNNeurons(); ++j) {
	    	std::cout << (nnV.at(i).getWeights().get()[j]) << ", ";
	    }
	    std::cout << std::endl;
	}
	*/

	unsigned int test = nnV.size();

	return 0;
}
