//
// Created by Mikke on 24-02-2022.
//

#include "nnLayer.h"

#include <utility>


nnLayer::nnLayer(unsigned int n_neur, std::shared_ptr<ap_fixed<15, 1>> w,
                 std::shared_ptr<ap_fixed<15, 1>> b, unsigned int act_f) {

    act_function = act_f;
    n_neurons = n_neur;

    weights = std::move(w);
    bias = std::move(b);
}
