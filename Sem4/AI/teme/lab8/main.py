import re
import pandas as pd
import numpy as np
import nltk
import string

from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
from sklearn.feature_extraction.text import CountVectorizer, TfidfVectorizer
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from keras.src.models import Sequential
from keras.src.layers import Dense, Dropout
from keras.src.utils import to_categorical
from gensim.models import Word2Vec
from azure.ai.textanalytics import TextAnalyticsClient
from azure.core.credentials import AzureKeyCredential
from sklearn.preprocessing import StandardScaler

# Azure Authentication + Analysis
key = "2mJzu9KhUoj0yyOogkvtEmC16jyALbrD841aevm5AHIcoyhKMnKMJQQJ99BDACPV0roXJ3w3AAAaACOGGF7i"
endpoint = "https://ai-patricia-2025.cognitiveservices.azure.com/"

def authenticate():
    credential = AzureKeyCredential(key)
    return TextAnalyticsClient(endpoint=endpoint, credential=credential)

def azure_sentiment_analysis(text):
    client = authenticate()
    document = [text]
    response = client.analyze_sentiment(documents=document)[0]
    print(f"\n Azure Sentiment: {response.sentiment}")
    for key, val in response.confidence_scores.__dict__.items():
        print(f" {key.capitalize()}: {val:.2f}")

# Text preprocessing + features extraction
'''
nltk.download('punkt')
nltk.download('stopwords')
nltk.download('wordnet')
'''

stop_words = set(stopwords.words('english'))
lemmatizer = WordNetLemmatizer()

def clean_text(text):
    text = text.lower()
    text = re.sub(r"http\S+|www\S+|https\S+", '', text)
    text = re.sub(r'\d+', '', text)
    text = text.translate(str.maketrans('', '', string.punctuation))
    tokens = nltk.word_tokenize(text)
    tokens = [lemmatizer.lemmatize(word) for word in tokens if word not in stop_words]
    return ' '.join(tokens)

df = pd.read_csv("data/review_mixed.csv")
df.dropna(inplace=True)
df['cleaned'] = df['Text'].apply(clean_text)

label_encoder = LabelEncoder()
y_labels = label_encoder.fit_transform(df["Sentiment"])
y = to_categorical(y_labels)

# BoW
vectorizer_bow = CountVectorizer(max_features=1000)
X_bow = vectorizer_bow.fit_transform(df['cleaned']).toarray()

# TF-IDF
vectorizer_tfidf = TfidfVectorizer(max_features=1000)
X_tfidf = vectorizer_tfidf.fit_transform(df['cleaned']).toarray()

# Word2Vec
sentences = [text.split() for text in df['cleaned']]
w2v_model = Word2Vec(sentences, vector_size=100, window=5, min_count=1, workers=4)
X_w2v = np.array([np.mean([w2v_model.wv[word] for word in words if word in w2v_model.wv] or [np.zeros(100)], axis=0) for words in sentences])

# Extra features
positive_words = {'happy', 'joy', 'love', 'great', 'good', 'excellent', 'amazing'}
negative_words = {'sad', 'bad', 'terrible', 'awful', 'hate', 'worst'}

def extra_features(text):
    tokens = text.split()
    word_count = len(tokens)
    char_count = len(text)
    pos_count = sum(1 for word in tokens if word in positive_words)
    neg_count = sum(1 for word in tokens if word in negative_words)
    return [char_count, word_count, pos_count, neg_count]

X_extra = np.array([extra_features(text) for text in df['cleaned']])
scaler = StandardScaler()
X_extra_scaled = scaler.fit_transform(X_extra)
X_combined = np.hstack((X_tfidf, X_extra_scaled))

# ANN (tool)
X_train, X_test, y_train, y_test = train_test_split(X_combined, y, test_size=0.2, random_state=42)

model = Sequential([
    Dense(64, activation='relu', input_shape=(X_combined.shape[1],)),
    Dropout(0.3),
    Dense(32, activation='relu'),
    Dense(y_train.shape[1], activation='softmax')
])

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
model.fit(X_train, y_train, epochs=20, batch_size=20, validation_split=0.1)
loss, acc = model.evaluate(X_test, y_test)
print(f"\n Accuracy ANN(tool) : {acc:.2f}")

# ANN without tool
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return sigmoid(x) * (1 - sigmoid(x))

class ANN:
    def __init__(self, input_size, hidden_size, output_size, lr=0.001):
        self.lr = lr
        self.W1 = np.random.randn(input_size, hidden_size)
        self.b1 = np.zeros((1, hidden_size))
        self.W2 = np.random.randn(hidden_size, output_size)
        self.b2 = np.zeros((1, output_size))

    def forward(self, X):
        self.z1 = X @ self.W1 + self.b1
        self.a1 = sigmoid(self.z1)
        self.z2 = self.a1 @ self.W2 + self.b2
        self.a2 = sigmoid(self.z2)
        return self.a2

    def backward(self, X, y, output):
        m = y.shape[0]
        d_z2 = output - y
        d_W2 = self.a1.T @ d_z2 / m
        d_b2 = np.sum(d_z2, axis=0, keepdims=True) / m
        d_z1 = (d_z2 @ self.W2.T) * sigmoid_derivative(self.z1)
        d_W1 = X.T @ d_z1 / m
        d_b1 = np.sum(d_z1, axis=0, keepdims=True) / m

        self.W1 -= self.lr * d_W1
        self.b1 -= self.lr * d_b1
        self.W2 -= self.lr * d_W2
        self.b2 -= self.lr * d_b2

    def train(self, X, y, epochs=100):
        for i in range(epochs):
            out = self.forward(X)
            self.backward(X, y, out)
            if i % 10 == 0:
                loss = np.mean((y - out) ** 2)
                print(f"Epoch {i} - Loss: {loss:.4f}")

X_small = X_combined[:209]
y_small = y[:209]
ann = ANN(input_size=X_small.shape[1], hidden_size=32, output_size=2)
ann.train(X_small, y_small, epochs=20)

msg = "By choosing a bike over a car, I’m reducing my environmental footprint. Cycling promotes eco-friendly transportation, and I’m proud to be part of that movement."
azure_sentiment_analysis(msg)

msg_cleaned = clean_text(msg)
msg_vec = vectorizer_tfidf.transform([msg_cleaned]).toarray()
msg_extra = scaler.transform([extra_features(msg_cleaned)])
msg_input = np.hstack((msg_vec, msg_extra))

pred = model.predict(msg_input)
pred_label = label_encoder.inverse_transform([np.argmax(pred)])
print(f"\n ANN (Keras) Predicted Sentiment: {pred_label[0]}")

manual_pred = ann.forward(msg_input)
manual_label = np.argmax(manual_pred)
if y.shape[1] == 2:
    label_name = label_encoder.inverse_transform([manual_label])[0]
else:
    label_name = f"Clasa {manual_label}"

print(f"\nANN (Manual) Predicted Sentiment: {label_name}")
