//
// Created by Mikke on 24-02-2022.
//

#ifndef FILEPARSER_FILEPARSER_H
#define FILEPARSER_FILEPARSER_H
#include <iostream>
#include <fstream>
#include <vector>



class FileParser {

public:
    FileParser();
    virtual ~FileParser();

    //Should be reimplemented with SD Card Methods
    unsigned int openfile(std::string filename);
    unsigned int closefile();
    std::string readfile();

    char** parseString(std::string);


private:
    std::ifstream filedescrip_;

};


#endif //FILEPARSER_FILEPARSER_H
