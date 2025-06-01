from ucimlrepo import fetch_ucirepo
import warnings; warnings.simplefilter('ignore')
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression

# fetch dataset
iris = fetch_ucirepo(id=53)

# data (as pandas dataframes)
X = iris.data.features
y = iris.data.targets

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

scaler = StandardScaler()
scaler.fit(X_train)
X_train_scaled = scaler.transform(X_train)
X_test_scaled = scaler.transform(X_test)

model = LogisticRegression()
model.fit(X_train_scaled, y_train)
w0, w1 = model.intercept_, model.coef_[0]
computedTestPredictions = model.predict(X_test_scaled)

normalized_inputs = scaler.transform([[5.35, 3.85, 1.25, 0.4]])
prediction = model.predict(np.array(normalized_inputs))

predicted_species = prediction
print("The predicted species for the flower is: ", predicted_species)