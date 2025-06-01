import random

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn import linear_model
import csv
import numpy as np
import matplotlib.pyplot as plt

def plotData(x1, y1, x2=None, y2=None, x3=None, y3=None, title=None):
    plt.plot(x1, y1, 'ro', label='train data')
    if x2 is not None:
        plt.plot(x2, y2, 'b-', label='learned model')
    if x3 is not None:
        plt.plot(x3, y3, 'g^', label='test data')
    plt.title(title)
    plt.legend()
    plt.show()

def plotDataHistogram(x, variableName):
    n, bins, patches = plt.hist(x, 10)
    plt.title('Histogram of ' + variableName)
    plt.show()

def loadData(fileName, inputVariableName, outputVariableName):
    data = []
    dataNames = []

    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0

        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1

    selectedVariable = dataNames.index(inputVariableName)
    inputs = [float(data[i][selectedVariable]) for i in range(len(data))]
    selectedOutput = dataNames.index(outputVariableName)
    outputs = [float(data[i][selectedOutput]) for i in range(len(data))]

    return inputs, outputs

def family_problem(filename):
    # load data
    inputs, outputs = loadData(filename, 'Family', 'Happiness.Score')

    # histograms for input/output data
    plotDataHistogram(inputs, 'family')
    plotDataHistogram(outputs, 'Happiness score')

    # check liniarity (y = happiness vs x = happiness)
    plotData(inputs, outputs, [], [], [], [], 'family vs hapiness')

    # test data - allocated randomly
    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    # create data set
    trainInputs = [inputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testOutputs = [outputs[i] for i in testSample]

    plotData(trainInputs, trainOutputs, [], [], testInputs, testOutputs, "train and test data")

    # train the model
    xx = [[el] for el in trainInputs]
    regressor = linear_model.LinearRegression()

    # minimise loss function
    regressor.fit(xx, trainOutputs)
    w0, w1 = regressor.intercept_, regressor.coef_

    # plot the model
    noOfPoints = 1000
    xref = []
    val = min(trainInputs)
    step = (max(trainInputs) - min(trainInputs)) / noOfPoints

    # x-axis values
    for i in range(1, noOfPoints):
        xref.append(val)
        val += step

    # y-axis linear model equation
    yref = [w0 + w1 * el for el in xref]

    plotData(trainInputs, trainOutputs, xref, yref, [], [], title="train data and model")

    # predictions for test data
    computedTestOutputs = regressor.predict([[x] for x in testInputs])
    plotData([], [], testInputs, computedTestOutputs, testInputs, testOutputs, "predictions vs real test data")

    # calculate error
    error = mean_squared_error(testOutputs, computedTestOutputs)
    print('Error (with tool): ', error)

def loadDataGDP(fileName, inputVariableName, outputVariableName):
    data = pd.read_csv(fileName).dropna()
    inputs = data[inputVariableName].values
    outputs = data[outputVariableName].values

    return inputs, outputs

def economy_freedom_problem(fileName):
    inputs, outputs = loadDataGDP(fileName, ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')

    plotDataHistogram(inputs[:,0], 'Economy GDP per Capita')
    plotDataHistogram(inputs[:,1], 'Freedom')

    plotData(inputs[:,0], outputs, [], [], [], [], 'Economy GDP per Capita vs Happiness')
    plotData(inputs[:,1], outputs, [], [], [], [], 'Freedom vs Happiness')

    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]

    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    regressor = linear_model.LinearRegression()
    regressor.fit(trainInputs, trainOutputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]

    noOfPoints = 1000
    x1_ref = []
    x2_ref = []
    val1 = min([x[0] for x in trainInputs])
    step1 = (max([x[0] for x in trainInputs]) - min([x[0] for x in trainInputs])) / noOfPoints
    val2 = min([x[1] for x in trainInputs])
    step2 = (max([x[1] for x in trainInputs]) - min([x[1] for x in trainInputs])) / noOfPoints

    for i in range(1, noOfPoints):
        x1_ref.append(val1)
        val1 += step1
        x2_ref.append(val2)
        val2 += step2

    y_ref = [w0 + w1 * x1 +w2 * x2 for x1, x2 in zip(x1_ref, x2_ref)]

    plotData([x[0] for x in trainInputs], trainOutputs, x1_ref, y_ref, [], [], "Train Data and Model: Economy..GDP.per.Capita.")

    computedTestOutputs = regressor.predict(testInputs)

    plotData([], [], [x[0] for x in testInputs], computedTestOutputs, [x[0] for x in testInputs], testOutputs, "Predictions vs Real Test Data (Economy GDP per Capita)")
    plotData([], [], [x[1] for x in testInputs], computedTestOutputs, [x[1] for x in testInputs], testOutputs,"Predictions vs Real Test Data (Freedom)")

    error = mean_squared_error(testOutputs, computedTestOutputs)
    print("Error: ", error)


class MyLinearUnivariateRegression:

    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = 0.0

    def fit(self, x, y):
        n = len(x)
        sum_x = sum(x)
        sum_y = sum(y)
        sum_xy = sum(i * j for i, j in zip(x, y))
        sum_xx = sum(i ** 2 for i in x)

        w1 = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x ** 2)
        w0 = (sum_y - w1 * sum_x) / n

        self.intercept_, self.coef_ = w0, w1

    def predict(self, validationInputs):
        return [self.intercept_ + self.coef_ * x for x in validationInputs]

def computeError(testOutputs, computedTestOutputs):
    return sum((t1 - t2) ** 2 for t1, t2 in zip(computedTestOutputs, testOutputs)) / len(testOutputs)

def splitData(inputs, outputs, test_size=0.2, random_state=None):
    if random_state is not None:
        np.random.seed(random_state)

    num_samples = len(inputs)
    num_test_samples = int(test_size * num_samples)

    indexes = np.arange(num_samples)
    np.random.shuffle(indexes)

    train_indexes = indexes[num_test_samples:]
    test_indexes = indexes[:num_test_samples]

    train_inputs = [inputs[i] for i in train_indexes]
    test_inputs = [inputs[i] for i in test_indexes]

    train_outputs = [outputs[i] for i in train_indexes]
    test_outputs = [outputs[i] for i in test_indexes]

    return train_inputs, test_inputs, train_outputs, test_outputs

def family_problem_manual(filename):
    inputs, outputs = loadData(filename, 'Family', 'Happiness.Score')

    plotDataHistogram(inputs, 'family')
    plotDataHistogram(outputs, 'Happiness score')

    # liniarity check
    plotData(inputs, outputs, [], [], [], [], 'family vs happiness')

    trainInputs, testInputs, trainOutputs, testOutputs = splitData(inputs, outputs)

    plotData(trainInputs, trainOutputs, [], [], testInputs, testOutputs, "train and test data")

    # train the model
    regressor = MyLinearUnivariateRegression()
    regressor.fit(trainInputs, trainOutputs)
    w0, w1 = regressor.intercept_, regressor.coef_

    # plot the model
    noOfPoints = 1000
    xref = []
    val = min(trainInputs)
    step = (max(trainInputs) - min(trainInputs)) / noOfPoints

    for i in range(1, noOfPoints):
        xref.append(val)
        val += step

    yref = [w0 + w1 * el for el in xref]

    plotData(trainInputs, trainOutputs, xref, yref, [], [], "train data and model")

    # predictions for test data
    computedTestOutputs = regressor.predict(testInputs)
    plotData([], [], testInputs, computedTestOutputs, testInputs, testOutputs, "predictions vs real test data")

    # error
    error = computeError(testOutputs, computedTestOutputs)
    print("Error: ", error)

class MyLinearBivariateRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = [0.0, 0.0]

    def fit(self, x, y):
        n = len(x)
        sum_x1 = sum(i[0] for i in x)
        sum_x2 = sum(i[1] for i in x)
        sum_y = sum(y)
        sum_x1x1 = sum(i[0] ** 2 for i in x)
        sum_x2x2 = sum(i[1] ** 2 for i in x)
        sum_x1x2 = sum(i[0] * i[1] for i in x)
        sum_x1y = sum(i[0] * j for i, j in zip(x, y))
        sum_x2y = sum(i[1] * j for i, j in zip(x, y))

        det = n * (sum_x1x1 * sum_x2x2 - sum_x1x2 ** 2) - sum_x1 * (sum_x1 * sum_x2x2 - sum_x1x2 * sum_x2) + sum_x2 * (sum_x1 * sum_x1x2 - sum_x1x1 * sum_x2)
        w0 = (sum_y * (sum_x1x1 * sum_x2x2 - sum_x1x2 ** 2) - sum_x1 * (sum_x1y * sum_x2x2 - sum_x1x2 * sum_x2y) + sum_x2 * (sum_x1y * sum_x1x2 - sum_x1x1 * sum_x2y)) / det
        w1 = (n * (sum_x1y * sum_x2x2 - sum_x1x2 * sum_x2y) - sum_y * (sum_x1 * sum_x2x2 - sum_x1x2 * sum_x2) + sum_x2 * (sum_x1 * sum_x2y - sum_x1y * sum_x2)) / det
        w2 = (n * (sum_x1x1 * sum_x2y - sum_x1x2 * sum_x1y) - sum_x1 * (sum_x1 * sum_x2y - sum_x1y * sum_x2) + sum_y * (sum_x1 * sum_x1x2 - sum_x1x1 * sum_x2)) / det

        self.intercept_ = w0
        self.coef_ = [w1, w2]

    def predict(self, validationInputs):
        return [self.intercept_ + self.coef_[0] * x[0] + self.coef_[1] * x[1] for x in validationInputs]

def economy_freedom_problem_manual(fileName):
    inputs, outputs = loadDataGDP(fileName, ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')

    plotDataHistogram(inputs[:, 0], 'Economy GDP per Capita')
    plotDataHistogram(inputs[:, 1], 'Freedom')

    plotData(inputs[:, 0], outputs, [], [], [], [], 'Economy GDP per Capita vs Happiness')
    plotData(inputs[:, 1], outputs, [], [], [], [], 'Freedom vs Happiness')

    trainInputs, testInputs, trainOutputs, testOutputs = splitData(inputs, outputs)

    regressor = MyLinearBivariateRegression()
    regressor.fit(trainInputs, trainOutputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]

    computedTestOutputs = regressor.predict(testInputs)

    plotData([], [], [x[0] for x in testInputs], computedTestOutputs, [x[0] for x in testInputs], testOutputs, "Predictions vs Real Test Data (Economy GDP per Capita)")
    plotData([], [], [x[1] for x in testInputs], computedTestOutputs, [x[1] for x in testInputs], testOutputs, "Predictions vs Real Test Data (Freedom)")

    error = computeError(testOutputs, computedTestOutputs)
    print("Error: ", error)

def main():
    print(" -- Problema 1 --")
    family_problem('data/v1_world-happiness-report-2017.csv')
    economy_freedom_problem('data/v1_world-happiness-report-2017.csv')

    print(" -- Problema 2 --")
    family_problem('data/v2_world-happiness-report-2017.csv')
    economy_freedom_problem('data/v2_world-happiness-report-2017.csv')

    print(" -- Problema 3 --")
    family_problem('data/v3_world-happiness-report-2017.csv')
    economy_freedom_problem('data/v3_world-happiness-report-2017.csv')

    print(" -- Problema 1 (manual) --")
    family_problem_manual('data/v1_world-happiness-report-2017.csv')
    economy_freedom_problem_manual('data/v1_world-happiness-report-2017.csv')

main()

