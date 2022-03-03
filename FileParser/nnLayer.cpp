//
// Created by Mikke on 24-02-2022.
//

#include "nnLayer.h"


nnLayer::nnLayer(unsigned int n_neur, std::shared_ptr<CUSTOMTYPE> w,
                 std::shared_ptr<CUSTOMTYPE> b, unsigned int act_f) {

    if (n_neur >= MAX_NN_SIZE){
        n_neurons = MAX_NN_SIZE;
    } else{
        n_neurons = n_neur;
    }

    act_function = act_f;
    weights = w;
    bias = b;

}

const std::shared_ptr<CUSTOMTYPE> nnLayer::getWeights() const {
    return weights;
}

const std::shared_ptr<CUSTOMTYPE> nnLayer::getBias() const {
    return bias;
}

unsigned int nnLayer::getActFunction() const {
    return act_function;
}

unsigned int nnLayer::getNNeurons() const {
    return n_neurons;
}
