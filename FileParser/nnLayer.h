//
// Created by Mikke on 24-02-2022.
//

#ifndef FILEPARSER_NNLAYER_H
#define FILEPARSER_NNLAYER_H

#include "include/ap_fixed.h"


class nnLayer {

public:
    nnLayer(unsigned int n_neur, std::shared_ptr<ap_fixed<15, 1>> w, std::shared_ptr<ap_fixed<15, 1>> b, unsigned int act_f);

private:
    std::shared_ptr<ap_fixed<15,1>> weights;
    std::shared_ptr<ap_fixed<15,1>> bias;
    unsigned int act_function;
    unsigned int n_neurons;
};


#endif //FILEPARSER_NNLAYER_H
