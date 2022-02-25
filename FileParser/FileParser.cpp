//
// Created by Mikke on 24-02-2022.
//

#include <string>
#include "FileParser.h"

FileParser::FileParser() {}

FileParser::~FileParser() {
    filedescrip_.close();
}

unsigned int FileParser::openfile(std::string filename) {

    filedescrip_.open(filename);

    //std::ifstream input_file(filename);

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
    unsigned int buf_index = 0;
    char buf;
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(filedescrip_, line)){
        //filedescrip_ >> buf;
        //outbuf[buf_index++] = buf;
        lines.push_back(line);
        lines.push_back("\n"); // Add fake newline, the SD card driver will do this for us
    }

    std::string s;
    for (const auto &piece : lines) s += piece;
    return s;


}

