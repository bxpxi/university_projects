import numpy as np
import pandas as pd
from ucimlrepo import fetch_ucirepo
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

iris = fetch_ucirepo(id=53)

X = iris.data.features.values
y = iris.data.targets.values

unique_classes = np.unique(y)
class_mapping = {cls: idx for idx, cls in enumerate(unique_classes)}
y = np.array([class_mapping[label[0]] for label in y])  # FIXED

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

mean_X = np.mean(X_train, axis=0)
std_X = np.std(X_train, axis=0)
X_train = (X_train - mean_X) / std_X
X_test = (X_test - mean_X) / std_X

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def compute_loss(y, y_pred):
    return -np.mean(y * np.log(y_pred) + (1 - y) * np.log(1 - y_pred))

def logistic_regression(X, y, lr=0.1, epochs=5000):
    m, n = X.shape
    w = np.zeros(n)
    b = 0

    for _ in range(epochs):
        z = np.dot(X, w) + b
        y_pred = sigmoid(z)

        dw = (1 / m) * np.dot(X.T, (y_pred - y))
        db = (1 / m) * np.sum(y_pred - y)

        w -= lr * dw
        b -= lr * db

    return w, b

w, b = logistic_regression(X_train, y_train)

print(f"Learned model: f(x) = {b} + {w[0]} * x1 + {w[1]} * x2 + {w[2]} * x3 + {w[3]} * x4")

def predict(X, w, b):
    probs = sigmoid(np.dot(X, w) + b)
    return np.round(probs).astype(int)

y_pred = predict(X_test, w, b)

accuracy = accuracy_score(y_test, y_pred)
print("Accuracy:", accuracy)

new_sample = np.array([[5.35, 3.85, 1.25, 0.4]])
x_new = (new_sample - mean_X) / std_X
prediction = predict(x_new, w, b)
predicted_species = unique_classes[prediction[0]]
print("The predicted species for the flower is: ", predicted_species)
