//
// Created by Mikke on 24-02-2022.
//

#ifndef FILEPARSER_NNLAYER_H
#define FILEPARSER_NNLAYER_H

//#include "include/ap_fixed.h"
#include <memory>
#include "globals.h"

class nnLayer {

public:
    nnLayer(unsigned int n_neur, std::shared_ptr<CUSTOMTYPE> w, std::shared_ptr<CUSTOMTYPE> b, unsigned int act_f);

    const std::shared_ptr<CUSTOMTYPE> getWeights() const;

    const std::shared_ptr<CUSTOMTYPE> getBias() const;

    unsigned int getActFunction() const;

    unsigned int getNNeurons() const;


private:
    std::shared_ptr<CUSTOMTYPE> weights;
    std::shared_ptr<CUSTOMTYPE> bias;
    unsigned int act_function;
    unsigned int n_neurons;
};


#endif //FILEPARSER_NNLAYER_H
