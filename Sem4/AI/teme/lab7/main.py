import os
import numpy as np
from PIL import Image
from keras.src.models import Sequential
from keras.src.layers import Dense, Flatten, Conv2D, MaxPooling2D
from keras.src.optimizers import Adam
from keras.src.legacy.preprocessing.image import ImageDataGenerator
import matplotlib.pyplot as plt
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import train_test_split


def create_image_dataset(input_folder, output_folder):
    sepia_folder = os.path.join(output_folder, 'sepia')
    original_folder = os.path.join(output_folder, 'original')

    os.makedirs(sepia_folder, exist_ok=True)
    os.makedirs(original_folder, exist_ok=True)

    for filename in os.listdir(input_folder):
        if filename.endswith('.jpg') or filename.endswith('.png'):
            image_path = os.path.join(input_folder, filename)
            image = Image.open(image_path)
            sepia_image = apply_sepia_filter(image)
            image.save(os.path.join(original_folder, filename))
            sepia_image.save(os.path.join(sepia_folder, filename))

def apply_sepia_filter(image):
    image = image.convert("RGB")
    width, height = image.size
    pixels = image.load()

    for py in range(height):
        for px in range(width):
            r, g, b = image.getpixel((px, py))

            tr = int(0.393 * r + 0.769 * g + 0.189 * b)
            tg = int(0.349 * r + 0.686 * g + 0.168 * b)
            tb = int(0.272 * r + 0.534 * g + 0.131 * b)

            if tr > 255:
                tr = 255
            if tg > 255:
                tg = 255
            if tb > 255:
                tb = 255

            pixels[px, py] = (tr, tg, tb)

    return image

def train_ann_model(train_dir, val_dir):
    train_data_gen = ImageDataGenerator(rescale=1./255)
    test_data_gen = ImageDataGenerator(rescale=1./255)

    train_generator = train_data_gen.flow_from_directory(
        train_dir,
        target_size=(64, 64),
        batch_size=10,
        class_mode='binary'
    )

    validation_generator = test_data_gen.flow_from_directory(
        val_dir,
        target_size=(64,64),
        batch_size=10,
        class_mode='binary'
    )

    model = Sequential()
    model.add(Flatten(input_shape=(64,64,3)))
    model.add(Dense(128, activation='relu'))
    model.add(Dense(1, activation='sigmoid'))

    optimezer = Adam(learning_rate=0.001)
    model.compile(loss='binary_crossentropy', optimizer=optimezer, metrics=['accuracy'])

    history = model.fit(
        train_generator,
        steps_per_epoch = train_generator.n // 10,
        epochs = 20,
        validation_data = validation_generator,
        validation_steps = validation_generator.n // 10
    )

    return model, history

def evaluate_hyperparameters(train_dir, val_dir):
    learning_rates = [0.001, 0.01, 0.1]
    batch_sizes = [2, 5, 10]
    epochs = [5, 10, 20]
    hidden_neurons = [64, 128, 256]

    results = {}

    for lr in learning_rates:
        for bs in batch_sizes:
            for e in epochs:
                for hn in hidden_neurons:
                    train_datagen = ImageDataGenerator(rescale=1. / 255)
                    val_datagen = ImageDataGenerator(rescale=1. / 255)

                    train_generator = train_datagen.flow_from_directory(
                        train_dir,
                        target_size=(64, 64),
                        batch_size=bs,
                        class_mode='binary'
                    )

                    validation_generator = val_datagen.flow_from_directory(
                        val_dir,
                        target_size=(64, 64),
                        batch_size=bs,
                        class_mode='binary'
                    )

                    model = Sequential()
                    model.add(Flatten(input_shape=(64, 64, 3)))
                    model.add(Dense(hn, activation='relu'))
                    model.add(Dense(1, activation='sigmoid'))

                    optimizer = Adam(learning_rate=lr)
                    model.compile(loss='binary_crossentropy', optimizer=optimizer, metrics=['accuracy'])

                    model.fit(
                        train_generator,
                        steps_per_epoch=train_generator.samples,
                        epochs=e,
                        validation_data=validation_generator,
                        validation_steps=validation_generator.samples,
                        verbose=0
                    )

                    test_loss, test_acc = model.evaluate(validation_generator, steps=validation_generator.samples)
                    results[(lr,bs,e,hn)] = test_acc
                    print(f"Evaluare: learning_rate={lr}, batch_size={bs}, epochs={e}, hidden_neurons={hn}, accuracy={test_acc:.4f}")

    return results

class ANN:
    def __init__(self, input_size, hidden_size, output_size):
        self.input_size = input_size
        self.hidden_size = hidden_size
        self.output_size = output_size

        self.weights_input_hidden = np.random.randn(self.input_size, self.hidden_size)
        self.weights_hidden_output = np.random.randn(self.hidden_size, self.output_size)

        self.bias_hidden = np.random.randn(self.hidden_size)
        self.bias_output = np.random.randn(self.output_size)

        self.history = {'accuracy': [], 'loss': [], 'val_accuracy': [], 'val_loss': []}

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def forward(self, X):
        self.hidden_input = np.dot(X, self.weights_input_hidden) + self.bias_hidden
        self.hidden_output = self.sigmoid(self.hidden_input)

        self.final_input = np.dot(self.hidden_output, self.weights_hidden_output) + self.bias_output
        self.final_output = self.sigmoid(self.final_input)

        return self.final_output

    def backward(self, X, y, learning_rate=0.01):
        output_error = y - self.final_output
        output_delta = output_error * self.sigmoid_derivative(self.final_output)

        hidden_error = output_delta.dot(self.weights_hidden_output.T)
        hidden_delta = hidden_error * self.sigmoid_derivative(self.hidden_output)

        self.weights_input_hidden += X.T.dot(hidden_delta) * learning_rate
        self.weights_hidden_output += self.hidden_output.T.dot(output_delta) * learning_rate
        self.bias_hidden += np.sum(hidden_delta, axis=0) * learning_rate
        self.bias_output += np.sum(output_delta, axis=0) * learning_rate

    '''
    def train(self, X, y, epochs=20, learning_rate=0.01):
        for epoch in range(epochs):
            output = self.forward(X)
            self.backward(X, y, learning_rate)

            predictions = (output > 0.5).astype(int)
            acc = np.mean(predictions == y)
            loss = np.mean((y - output) ** 2)

            self.history['accuracy'].append(acc)
            self.history['loss'].append(loss)
            self.history['val_accuracy'].append(acc)
            self.history['val_loss'].append(loss)
    '''

    def train(self, X_train, y_train, X_val, y_val, epochs=20, learning_rate=0.01):
        for epoch in range(epochs):
            output_train = self.forward(X_train)
            self.backward(X_train, y_train, learning_rate)

            # Train metrics
            predictions_train = (output_train > 0.5).astype(int)
            acc_train = np.mean(predictions_train == y_train)
            loss_train = np.mean((y_train - output_train) ** 2)

            # Validation metrics
            output_val = self.forward(X_val)
            predictions_val = (output_val > 0.5).astype(int)
            acc_val = np.mean(predictions_val == y_val)
            loss_val = np.mean((y_val - output_val) ** 2)

            # Save metrics
            self.history['accuracy'].append(acc_train)
            self.history['loss'].append(loss_train)
            self.history['val_accuracy'].append(acc_val)
            self.history['val_loss'].append(loss_val)

    def predict(self, X):
        return self.forward(X)

class SimpleCNN:
    def __init__(self, input_shape, hidden_size, output_size):
        self.input_shape = input_shape
        self.hidden_size = hidden_size
        self.output_size = output_size

        flat_size = np.prod(input_shape)

        self.weights_input_hidden = np.random.randn(flat_size, hidden_size) * 0.01
        self.weights_hidden_output = np.random.randn(hidden_size, output_size) * 0.01
        self.bias_hidden = np.zeros(hidden_size)
        self.bias_output = np.zeros(output_size)

        self.history = {'accuracy': [], 'loss': [], 'val_accuracy': [], 'val_loss': []}

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)

    def forward(self, X):
        self.X_flat = X.reshape(X.shape[0], -1)

        self.hidden_input = np.dot(self.X_flat, self.weights_input_hidden) + self.bias_hidden
        self.hidden_output = self.sigmoid(self.hidden_input)

        self.final_input = np.dot(self.hidden_output, self.weights_hidden_output) + self.bias_output
        self.final_output = self.sigmoid(self.final_input)

        return self.final_output

    def backward(self, y, learning_rate):
        output_error = y - self.final_output
        output_delta = output_error * self.sigmoid_derivative(self.final_output)

        hidden_error = np.dot(output_delta, self.weights_hidden_output.T)
        hidden_delta = hidden_error * self.sigmoid_derivative(self.hidden_output)

        self.weights_hidden_output += np.dot(self.hidden_output.T, output_delta) * learning_rate
        self.weights_input_hidden += np.dot(self.X_flat.T, hidden_delta) * learning_rate

        self.bias_output += np.sum(output_delta, axis=0) * learning_rate
        self.bias_hidden += np.sum(hidden_delta, axis=0) * learning_rate

    def train(self, X_train, y_train, X_val, y_val, epochs=20, learning_rate=0.01):
        for epoch in range(epochs):
            output_train = self.forward(X_train)
            self.backward(y_train, learning_rate)

            predictions_train = (output_train > 0.5).astype(int)
            acc_train = np.mean(predictions_train == y_train)
            loss_train = np.mean((y_train - output_train) ** 2)

            output_val = self.forward(X_val)
            predictions_val = (output_val > 0.5).astype(int)
            acc_val = np.mean(predictions_val == y_val)
            loss_val = np.mean((y_val - output_val) ** 2)

            self.history['accuracy'].append(acc_train)
            self.history['loss'].append(loss_train)
            self.history['val_accuracy'].append(acc_val)
            self.history['val_loss'].append(loss_val)

            print(f"Epoch {epoch+1}/{epochs} - acc: {acc_train:.4f} - val_acc: {acc_val:.4f}")

    def predict(self, X):
        output = self.forward(X)
        return (output > 0.5).astype(int)


def plot_metrics(ann_model):
    history = ann_model.history

    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(history['accuracy'], label='Train Accuracy')
    plt.plot(history['val_accuracy'], label='Validation Accuracy')
    plt.title('Accuracy over epochs')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(history['loss'], label='Train Loss')
    plt.plot(history['val_loss'], label='Validation Loss')
    plt.title('Loss over epochs')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()

    plt.show()

def plot_cnn_metrics(model):
    history = model.history

    plt.figure(figsize=(12, 4))

    plt.subplot(1, 2, 1)
    plt.plot(history['accuracy'], label='Train Accuracy')
    plt.plot(history['val_accuracy'], label='Validation Accuracy')
    plt.title('CNN Accuracy over epochs')
    plt.xlabel('Epochs')
    plt.ylabel('Accuracy')
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(history['loss'], label='Train Loss')
    plt.plot(history['val_loss'], label='Validation Loss')
    plt.title('CNN Loss over epochs')
    plt.xlabel('Epochs')
    plt.ylabel('Loss')
    plt.legend()

    plt.show()


def load_images_from_directory(directory, image_size=(64, 64), split = True):
    X = []
    y = []

    for label, class_name in enumerate(os.listdir(directory)):
        class_path = os.path.join(directory, class_name)
        if not os.path.isdir(class_path):
            continue

        for filename in os.listdir(class_path):
            if filename.endswith('.jpg') or filename.endswith('.png'):
                image_path = os.path.join(class_path, filename)
                image = Image.open(image_path).convert('RGB').resize(image_size)
                image = np.array(image) / 255.0
                X.append(image)
                y.append(label)

    X = np.array(X)
    y = np.array(y).reshape(-1, 1)

    if split:
        return train_test_split(X, y, test_size=0.2, random_state=42)
    else:
        return X, y


if __name__ == "__main__":
    #cerinta 1 - baza de date
    input_folder = 'imagini_originale'
    output_folder = 'imagini'
    #create_image_dataset(input_folder, output_folder)

    #cerinta 2 - ann tool
    train_dir = 'imagini'
    val_dir = 'imagini'
    ann_model, ann_history = train_ann_model(train_dir, val_dir)

    #cerinta 3 - influenta hyperparametrilor
    #concluzii - cele mai bune pentru:
    #learning rate: 0.001
    #batch size mai mic (2/5)
    #epochs mai multe, dar nu mereu
    #hidden neurons: mai putini
    #multi hidden_neurons + small batch size => bad performance

    #results = evaluate_hyperparameters(train_dir, val_dir)

    #cerinta 4 - ann
    X_train, X_val, y_train, y_val = load_images_from_directory('imagini')
    X_train = X_train.reshape(X_train.shape[0], -1)
    X_val = X_val.reshape(X_val.shape[0], -1)

    ann_custom = ANN(input_size=64 * 64 * 3, hidden_size=128, output_size=1)
    ann_custom.train(X_train, y_train, X_val, y_val, epochs=20, learning_rate=0.01)

    plot_metrics(ann_custom)

    # cerinta 5 - CNN custom
    X_train_cnn, X_val_cnn, y_train_cnn, y_val_cnn = load_images_from_directory('imagini', image_size=(32, 32))

    cnn_model = SimpleCNN(input_shape=(32, 32, 3), hidden_size=64, output_size=1)
    cnn_model.train(X_train_cnn, y_train_cnn, X_val_cnn, y_val_cnn, epochs=20, learning_rate=0.01)

    plot_cnn_metrics(cnn_model)



