import numpy as np


class MyBatchGradientDescentRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = []

    def fit(self, x, y, learningRate = 0.001, noOfEpochs=1000, batches=20):
        self.coef_ = [0.0 for _ in range(len(x[0]) + 1)]

        for epoch in range(noOfEpochs):
            for i in range(0, len(x), batches):
                yComputed = [self.eval(xi) for xi in x[i:i+batches]]
                crtErrors = [yc - yi for yc, yi in zip(yComputed, y[i:i+batches])]

                for j in range(0, len(x[0])):
                    self.coef_[j] = self.coef_[j] - learningRate * sum([crtError * xi[j] for crtError, xi in zip(crtErrors, x[i:i+batches])])

                self.coef_[len(x[0])] = self.coef_[len(x[0])] - learningRate * sum(crtErrors)

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    # compute estimated value per feature
    def eval(self, xi):
        yi = self.coef_[-1]
        for j in range(len(xi)):
            yi += self.coef_[j] * xi[j]
        return yi

    def predict(self, x):
        return [self.eval(xi) for xi in x]

from sklearn.metrics import mean_squared_error
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import KFold
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import csv
import matplotlib.pyplot as plt

def loadData(fileName, inputVariableName, outputVariableName):
    data = []
    dataNames =[]

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

def plotDataHistogram(x, variableName):
    n, bins, patches = plt.hist(x, 10)
    plt.title('Histogram of ' + variableName)
    plt.show()

def plotData(x1, y1, x2=None, y2=None, x3=None, y3=None, title=None):
    plt.plot(x1, y1, 'ro', label='train data')
    if x2:
        plt.plot(x2, y2, 'b-', label='learned model')
    if x3:
        plt.plot(x3, y3, 'g^', label='test data')
    plt.title(title)
    plt.legend()
    plt.show()

def funcGBPOnly():
    inputs, outputs = loadData('data/fericire-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score')

    plotDataHistogram(inputs, 'capita GDP')
    plotDataHistogram(outputs, 'Happiness score')

    #check liniarity
    plotData(inputs, outputs, [], [], [], [], 'capita vs happiness')

    #split data
    trainInputs, testInputs, trainOutputs, testOutputs = train_test_split(inputs, outputs, test_size=0.2, random_state=42)

    plotData(trainInputs, trainOutputs, [], [], testInputs, testOutputs, 'train and test data')

    #train the model
    xx = [[el] for el in trainInputs]
    regressor = MyBatchGradientDescentRegression()
    regressor.fit(xx, trainOutputs)
    w0, w1 = regressor.intercept_, regressor.coef_[0]

    #plot the model
    noOfPoints = 1000
    xref = []
    val = min(trainInputs)
    step = (max(trainInputs) - min(trainInputs)) / noOfPoints
    for i in range(1, noOfPoints):
        xref.append(val)
        val += step
    yref = [w0 + w1 * el for el in xref]
    plotData(trainInputs, trainOutputs, xref, yref, [], [], title="train data and model")

    #predict test data
    computedTestOutputs = regressor.predict([[x] for x in testInputs])
    plotData([], [], testInputs, computedTestOutputs, testInputs, testOutputs, title='predictions vs real test data')

    #compute the error
    error = 0.0
    for t1, t2 in zip(computedTestOutputs, testOutputs):
        error += (t1-t2) ** 2
    error = error / len(testOutputs)
    print("Error (manual): ", error)

def plot3Ddata(x1Train, x2Train, yTrain, x1Model=None, x2Model=None, yModel=None, x1Test=None, x2Test=None, yTest=None, title=None):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    if x1Train is not None:
        ax.scatter(x1Train, x2Train, yTrain, c='red', marker='o', label='Train Data')
    if x1Model is not None:
        ax.scatter(x1Model, x2Model, yModel, c='blue', marker='_', label='Learned Model')
    if x1Test is not None:
        ax.scatter(x1Test, x2Test, yTest, c='green', marker='^', label='Test Data')

    ax.set_xlabel('X Label')
    ax.set_ylabel('Y Label')
    ax.set_zlabel('Z Label')
    plt.title(title)
    ax.legend()
    plt.show()

def loadDataMoreInputs(filename, inputVariableNames, outputVariableName):
    data = []
    dataNames = []

    with open(filename) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count=0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count+=1

    selectedVariable1 = dataNames.index(inputVariableNames[0])
    selectedVariable2 = dataNames.index(inputVariableNames[1])
    inputs = [[float(data[i][selectedVariable1]), float(data[i][selectedVariable2])] for i in range(len(data))]
    selectedOutput = dataNames.index(outputVariableName)
    outputs = [float(data[i][selectedOutput]) for i in range(len(data))]

    return inputs, outputs

def normalisation(trainData, testData):
    #standard scaling
    scaler = StandardScaler()
    if not isinstance(trainData[0], list):
        #encode samples in a list
        trainData = [[d] for d in trainData]
        testData = [[d] for d in testData]

        scaler.fit(trainData)
        normalisedTrainData = scaler.transform(trainData)
        normalisedTestData = scaler.transform(testData)

        #decode from list to raw values
        normalisedTrainData = [el[0] for el in normalisedTrainData]
        normalisedTestData = [el[0] for el in normalisedTestData]
    else:
        scaler.fit(trainData)
        normalisedTrainData = scaler.transform(trainData)
        normalisedTestData = scaler.transform(testData)

    return normalisedTrainData, normalisedTestData

def funcGBPFreedom():
    inputs, outputs = loadDataMoreInputs('data/fericire-2017.csv', ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')

    feature1 = [ex[0] for ex in inputs]
    feature2 = [ex[1] for ex in inputs]

    plotDataHistogram(feature1, 'capita GDP')
    plotDataHistogram(feature2, 'freedom')
    plotDataHistogram(outputs, 'Happiness score')

    plot3Ddata(feature1, feature2, outputs, [], [], [], [], [], [], 'capita vs freedom vs happiness')

    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    trainInputs, testInputs = normalisation(trainInputs, testInputs)
    trainOutputs, testOutputs = normalisation(trainOutputs, testOutputs)

    feature1Train = [ex[0] for ex in trainInputs]
    feature2Train = [ex[1] for ex in trainInputs]

    feature1Test = [ex[0] for ex in testInputs]
    feature2Test = [ex[1] for ex in testInputs]

    plot3Ddata(feature1Train, feature2Train, trainOutputs, [], [], [], feature1Test, feature2Test, testOutputs, 'train and test data(after normalisation)')

    regressor = MyBatchGradientDescentRegression()
    regressor.fit(trainInputs, trainOutputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
    print('Learned model: f(x) = ', w0, '+', w1, ' * x1 + ', w2, ' * x2')

    noOfPoints = 50
    xref1 = []
    val = min(feature1)
    step1 = (max(feature1) - min(feature1)) / noOfPoints
    for _ in range(1, noOfPoints):
        for _ in range(1, noOfPoints):
            xref1.append(val)
        val += step1

    xref2 = []
    val = min(feature2)
    step2 = (max(feature2) - min(feature2)) / noOfPoints
    for _ in range(1, noOfPoints):
        aux = val
        for _ in range(1, noOfPoints):
            xref2.append(aux)
            aux += step2

    yref = [w0 + w1 * el1 + w2 * el2 for el1, el2 in zip(xref1, xref2)]

    plot3Ddata(feature1Train, feature2Train, trainOutputs, xref1, xref2, yref, [], [], [], 'train data and learned model')

    computedTestOutputs = regressor.predict(testInputs)
    plot3Ddata([], [], [], feature1Test, feature2Test, computedTestOutputs, feature1Test, feature2Test, testOutputs, 'predicted vs real test data')

    error = mean_squared_error(testOutputs, computedTestOutputs)
    print('Error: ', error)

from sklearn.linear_model import SGDRegressor

def funcGBPOnlyTool():
    inputs, outputs = loadData('data/fericire-2017.csv', 'Economy..GDP.per.Capita.', 'Happiness.Score')

    plotDataHistogram(inputs, 'capita GDP')
    plotDataHistogram(outputs, 'Happiness score')

    plotData(inputs, outputs, [], [], [], [], 'capita vs happiness')

    trainInputs, testInputs, trainOutputs, testOutputs = train_test_split(inputs, outputs, test_size=0.2, random_state=42)

    plotData(trainInputs, trainOutputs, [], [], testInputs, testOutputs, 'train and test data')

    #train the model
    xx = [[el] for el in trainInputs]
    regressor = SGDRegressor(learning_rate='constant', eta0=0.01, max_iter=1000, tol=1e-3, penalty=None)
    regressor.fit(xx, trainOutputs)
    w0, w1 = regressor.intercept_, regressor.coef_[0]

    #plot the model
    noOfPoints = 1000
    xref = []
    val = min(trainInputs)
    step = (max(trainInputs) - min(trainInputs)) / noOfPoints
    for i in range(1, noOfPoints):
        xref.append(val)
        val += step
    yref = [w0 + w1 * el for el in xref]
    plotData(trainInputs, trainOutputs, xref, yref, [], [], title='train data and model')

    computedTestOutputs = regressor.predict([[x] for x in testInputs])
    plotData([], [], testInputs, computedTestOutputs, testInputs, testOutputs, 'predicted vs real test data')

    error = 0.0
    for t1, t2 in zip(computedTestOutputs, testOutputs):
        error += (t1-t2)**2
    error = error / len(testOutputs)
    print('Error (tool): ', error)

    mse_scores = cross_validation(regressor, inputs, outputs)
    avg_mse = mse_scores.mean()
    print('Average MSE: ', avg_mse)


def cross_validation(model, inputs, outputs, num_folds=5):
    inputs = np.array(inputs)
    inputs = inputs.reshape(-1, 1)

    kf = KFold(n_splits=num_folds, shuffle=True, random_state=42)

    mse_scores = cross_val_score(model, inputs, outputs, cv=kf, scoring='neg_mean_squared_error')

    return -mse_scores

def cross_validate(model, inputs, outputs, num_folds=5):
    kf = KFold(n_splits=num_folds, shuffle=True, random_state=42)
    mse_scores = cross_val_score(model, inputs, outputs, cv=kf, scoring='neg_mean_squared_error')
    return -mse_scores

def funcGBPFreedomTool():
    inputs, outputs = loadDataMoreInputs('data/fericire-2017.csv', ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')

    feature1 = [ex[0] for ex in inputs]
    feature2 = [ex[1] for ex in inputs]

    plotDataHistogram(feature1, 'capita GDP')
    plotDataHistogram(feature2, 'freedom')
    plotDataHistogram(outputs, 'Happiness score')

    # check liniarity
    plot3Ddata(feature1, feature2, outputs, [], [], [], [], [], [], 'capita vs freedom vs happiness')

    np.random.seed(5)
    indexes = [i for i in range(len(inputs))]
    trainSample = np.random.choice(indexes, int(0.8*len(inputs)), replace=False)
    testSample = [i for i in indexes if not i in trainSample]

    trainInputs = [inputs[i] for i in trainSample]
    trainOutputs = [outputs[i] for i in trainSample]
    testInputs = [inputs[i] for i in testSample]
    testOutputs = [outputs[i] for i in testSample]

    trainInputs, testInputs = normalisation(trainInputs, testInputs)
    trainOutputs, testOutputs = normalisation(trainOutputs, testOutputs)

    feature1train = [ex[0] for ex in trainInputs]
    feature2train = [ex[1] for ex in trainInputs]

    feature1test = [ex[0] for ex in testInputs]
    feature2test = [ex[1] for ex in testInputs]

    plot3Ddata(feature1train, feature2train, trainOutputs, [], [], [], feature1test, feature2test, testOutputs,"train and test data (after normalisation)")

    regressor = SGDRegressor(learning_rate='constant', eta0=0.01, max_iter=1000, tol=1e-3, penalty=None)
    regressor.fit(trainInputs, trainOutputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
    print('Learned model: f(x) = ', w0, ' + ', w1, ' * x1 + ', w2, ' * x2')

    noOfPoints = 50
    xref1 = []
    val = min(feature1)
    step1 = (max(feature1) - min(feature1)) / noOfPoints
    for _ in range(1, noOfPoints):
        for _ in range(1, noOfPoints):
            xref1.append(val)
        val += step1

    xref2 = []
    val = min(feature2)
    step2 = (max(feature2) - min(feature2)) / noOfPoints
    for _ in range(1, noOfPoints):
        aux = val
        for _ in range(1, noOfPoints):
            xref2.append(aux)
            aux += step2
    yref = [w0 + w1 * el1 + w2 * el2 for el1, el2 in zip(xref1, xref2)]
    #plot3Ddata(feature1train, feature2train, trainOutputs, xref1, xref2, yref, [], [], [],'train data and learned model')

    computedTestOutputs = regressor.predict(testInputs)
    plot3Ddata([], [], [], feature1test, feature2test, computedTestOutputs, feature1test, feature2test, testOutputs,'predicted vs real test data')

    error = mean_squared_error(testOutputs, computedTestOutputs)
    print('Error (tool):   ', error)

    mse_scores = cross_validate(regressor, inputs, outputs)
    avg_mse = mse_scores.mean()
    print('Average MSE: ', avg_mse)

def main():
    funcGBPOnly()
    funcGBPFreedom()
    funcGBPOnlyTool()
    funcGBPFreedomTool()

main()
