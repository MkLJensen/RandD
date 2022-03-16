# Simple Python Script for Converting bias.dat, test.dat and weights.dat
# files to a file structure used in Adaptive Neural Networks

import pandas as pd
import numpy as np
import keras
from keras.datasets import mnist
import keras.utils
from tensorflow import keras
from keras.utils.np_utils import to_categorical

from keras import layers
from sklearn.decomposition import PCA
import keras.initializers
import os

def JespersNN():
    # Model / data parameters
    num_classes = 10
    input_shape = 30

    # the data, split between train and test sets
    (x_train, y_train), (x_test, y_test) = mnist.load_data()

    # Scale images to the [0, 1] range
    x_train = x_train.astype("float32") / 255
    x_test = x_test.astype("float32") / 255

    reshaped_training_data = x_train.ravel().reshape(x_train.shape[0], x_train.shape[1] * x_train.shape[2])
    reshaped_test_data = x_test.ravel().reshape(x_test.shape[0], x_test.shape[1] * x_test.shape[2])

    print("x_train shape:", reshaped_training_data.shape)
    print(reshaped_training_data.shape[0], "train samples")
    print(reshaped_test_data.shape[0], "test samples")

    # convert class vectors to binary class matrices

    y_train = to_categorical(y_train, num_classes)
    y_test = to_categorical(y_test, num_classes)

    pca = PCA(n_components=input_shape)
    X_pca_train = pca.fit_transform(reshaped_training_data)
    X_pca_test = pca.transform(reshaped_test_data)

    model = keras.Sequential(
        [
            keras.Input(shape=input_shape),
            layers.Dense(30, activation="relu", kernel_initializer=keras.initializers.random_normal(mean=0.0, stddev=0.05, seed=1),
                         bias_initializer='zeros'),
            layers.Dense(30, activation="relu", kernel_initializer=keras.initializers.random_normal(mean=0.0, stddev=0.05, seed=1),
                         bias_initializer='zeros'),
            layers.Dense(num_classes, activation="softmax",
                         kernel_initializer=keras.initializers.random_normal(mean=0.0, stddev=0.05, seed=1), bias_initializer='zeros'),
        ]
    )

    model.summary()

    batch_size = 128
    epochs = 5

    model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])

    model.fit(X_pca_train, y_train, batch_size=batch_size, epochs=epochs)

    score = model.evaluate(X_pca_train, y_train, verbose=0)
    print("Test loss:", score[0])
    print("Test accuracy:", score[1])

    if os.path.exists("bias.csv"):
        os.remove("bias.csv")
    f = open("bias.csv", "a")
    for layer in model.layers:
        for bias in layer.get_weights()[1]:
            f.write(str(bias) + ",")
        f.write("\r\n")
    f.close()

    if os.path.exists("weights.csv"):
        os.remove("weights.csv")
    f = open("weights.csv", "a")
    for layer in model.layers:
        for neuron in layer.get_weights()[0]:
            for weight in neuron:
                f.write(str(weight) + ",")
        f.write("\r\n")
    f.close()


def load_dat_files(file_path):
    return pd.read_csv(file_path, header=None).iloc[:, :-1]


def createNNConfigFile(filename, bias, weights, act=1):

    # If File exists Make new
    if os.path.exists(filename):
        os.remove(filename)

    file1 = open(filename, "a")
    # for each layer
    for i in range(bias[0].size):
        layersWeights = weights.iloc[i]
        layersBias = bias.iloc[i]

        layersWeights = layersWeights.dropna()
        # Inputing the weights into string
        for j in range(layersWeights.size):
            if not np.isnan(layersWeights[j]):
                if j == layersWeights.size-1:
                    file1.write(str(float("{:.3f}".format(layersWeights[j]))))
                else:
                    file1.write(str(float("{:.3f}".format(layersWeights[j]))) + ",")


        # Adding the FA Seperator
        file1.write(",FA," + str(act) + ",FB,")

        # Adding the Biases

        layersBias = layersBias.dropna()
        for j in range(layersBias.size):
            if not np.isnan(layersBias[j]):
                if j == layersBias.size-1:
                    file1.write(str(float("{:.3f}".format(layersBias[j]))))
                else:
                    file1.write(str(float("{:.3f}".format(layersBias[j]))) + ",")

        # Add newline
        file1.write("\n")

    file1.close()
    print()


if __name__ == '__main__':
    #JespersNN()

    bias = load_dat_files('bias.csv')
    weights = load_dat_files('weights.csv')

    createNNConfigFile("testFile.txt", bias, weights)

    print(bias)

