import numpy as np
import pandas as pd
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

data = load_breast_cancer()
df = pd.DataFrame(data.data, columns=data.feature_names)
df['target'] = data.target

X = df[['mean radius', 'mean texture']].values
y = df['target'].values

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# normalizare
mean_X = np.mean(X_train, axis=0)
std_X = np.std(X_train, axis=0)

X_train = (X_train - mean_X) / std_X
X_test = (X_test - mean_X) / std_X

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

#loss function
def compute_loss(y, y_pred):
    return -np.mean(y * np.log(y_pred) + (1 - y) * np.log(1 - y_pred))

#gradient descent - regresie logistica
def logistic_regression(X, y, lr=0.1, epochs=5000):
    m, n = X.shape
    w = np.zeros(n)  # coeficineti
    b = 0  # bias

    for _ in range(epochs):
        z = np.dot(X, w) + b
        y_pred = sigmoid(z)

        dw = (1 / m) * np.dot(X.T, (y_pred - y))
        db = (1 / m) * np.sum(y_pred - y)

        w -= lr * dw
        b -= lr * db

    return w, b


# train the model
w, b = logistic_regression(X_train, y_train)

print(f"Learned model: f(x) = {b} + {w[0]} * x1 + {w[1]} * x2")


# predict
def predict(X, w, b):
    return [1 if sigmoid(np.dot(x, w) + b) >= 0.5 else 0 for x in X]


# predict for test data
y_pred = predict(X_test, w, b)

# calculate accuracy
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy:", accuracy)

# example
new_sample = np.array([[18, 10]])
x_new = (new_sample - mean_X) / std_X
prediction = predict(x_new, w, b)

if prediction[0] == 0:
    print("leziune benigna")
else:
    print("leziune maligna")
