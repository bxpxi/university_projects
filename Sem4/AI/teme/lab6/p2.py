import pandas as pd
from sklearn.datasets import load_breast_cancer
import numpy as np
import warnings

warnings.simplefilter('ignore')
from ucimlrepo import fetch_ucirepo
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

data = load_breast_cancer()

#access the features and target
allData = data.data # Features
y = data.target # target (0 malign, 1 benign)

scaler = StandardScaler()

labels_to_analyze = ['mean radius', 'mean texture', 'target']
df = pd.DataFrame(data=allData, columns=data.feature_names)
df['target'] = y

#select feature
XRad = df['mean radius'].values
XText = df['mean texture'].values
XRad = XRad.reshape(-1, 1) #resize for scaler
XRad = scaler.fit_transform(XRad)
XText = XText.reshape(-1, 1) #resize for scaler
XText = scaler.fit_transform(XText)
X = np.concatenate((XRad, XText), axis=1) #matrix
y = df['target'].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.8, random_state=42)

#normalizare prin scalare
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# train the model
model = LogisticRegression()
model.fit(X_train, y_train)
w0, w1 = model.intercept_, model.coef_[0]
print('Learned model: f(x) = ', w0[0], ' + ', w1[0], ' * x1 + ', w1[1], ' * x2')

# prediction
computedTestPredictions = model.predict(X_test)
accuracy = accuracy_score(y_test, computedTestPredictions)
print("Accuracy:", accuracy)

# normalise and predicti
normalized_inputs = scaler.transform([[18, 10]]).reshape(1, -1)
prediction = model.predict(np.array(normalized_inputs))

if prediction[0] == 0:
    print("leziune benigna")
else:
    print("leziune maligna")




