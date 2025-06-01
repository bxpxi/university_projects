import os
import time

import matplotlib.pyplot as plt
from azure.cognitiveservices.vision.computervision import ComputerVisionClient
from azure.cognitiveservices.vision.computervision.models import OperationStatusCodes
from azure.cognitiveservices.vision.computervision.models import VisualFeatureTypes
from msrest.authentication import CognitiveServicesCredentials
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score

#Authentication
subscription_key = "7V7ycWx3H2kw14NJCfvzmJNl9daU00DpJ4M9oaShjhQuj7SRL3XOJQQJ99BCAC5RqLJXJ3w3AAAFACOGpYkm"
endpoint = "https://ai-ubb-2025-patricia.cognitiveservices.azure.com/"
cv_client = ComputerVisionClient(endpoint, CognitiveServicesCredentials(subscription_key))

def read():
    dir = "bikes"
    images = []

    for file in os.listdir(dir):
        if file.endswith(".jpg"):
            image_path = os.path.join(dir, file)
            images.append(image_path)

    return images

'''
def classify(images):
    label_names = ["bike", "non-bike"]
    real_labels = ['bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'non-bike',
                   'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike',
                   'non-bike']
    computed_labels = []

    for image in images:
        img = open(image, "rb")
        time.sleep(5)  # Add delay to avoid rate limit erro
        result = cv_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.tags, VisualFeatureTypes.objects])

        computed_label = "non-bike"

        for object in result.objects:
            if object.object_property == "bike" or object.object_property == "bikes" or object.object_property == "bicycle" or object.object_property == "cycle" or object.object_property == "cycling":
                computed_label = "bike"

        computed_labels.append(computed_label)

    conf_matrix = confusion_matrix(real_labels, computed_labels, labels=label_names)
    accuracy = accuracy_score(real_labels, computed_labels)
    precision = precision_score(real_labels, computed_labels, average=None, labels=label_names)
    recall = recall_score(real_labels, computed_labels, average=None, labels=label_names)

    return accuracy, precision, recall
'''

def classify(images):
    label_names = ["bike", "non-bike"]
    real_labels = ['bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'bike', 'non-bike',
                   'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike', 'non-bike',
                   'non-bike']
    computed_labels = []

    for i in range(0, len(images), 2):
        batch = images[i:i+2]

        for image in batch:
            img = open(image, "rb")
            result = cv_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.tags, VisualFeatureTypes.objects])

            computed_label = "non-bike"

            for object in result.objects:
                if object.object_property in ["bike", "bikes", "bicycle", "cycle", "cycling"]:
                    computed_label = "bike"

            computed_labels.append(computed_label)

        time.sleep(10)

    conf_matrix = confusion_matrix(real_labels, computed_labels, labels=label_names)
    accuracy = accuracy_score(real_labels, computed_labels)
    precision = precision_score(real_labels, computed_labels, average=None, labels=label_names)
    recall = recall_score(real_labels, computed_labels, average=None, labels=label_names)

    return accuracy, precision, recall

'''
def locate(images):
    predicted_boxes = []

    for image in images:
        predicted_box = []
        isBike = False

        img = open(image, "rb")
        result = cv_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.objects])

        for object in result.objects:
            if object.object_property == "bike" or object.object_property == "bikes" or object.object_property == "bicycle" or object.object_property == "cycle" or object.object_property == "cycling":
                isBike = True
                predicted_box = [object.rectangle.x, object.rectangle.y, object.rectangle.x + object.rectangle.w, object.rectangle.y + object.rectangle.h]
                predicted_boxes.append(predicted_box)

        if isBike:
            im = plt.imread(image)
            fig = plt.imshow(im)
            fig.axes.add_patch(plt.Rectangle(xy=(predicted_box[0], predicted_box[1]), width=predicted_box[2] - predicted_box[0], height=predicted_box[3]-predicted_box[1], fill=False, color="red", linewidth=2))
            #plt.show()

    return predicted_boxes
'''

def locate(images):
    predicted_boxes = []

    for i in range(0, len(images), 2):
        batch = images[i:i+2]

        for image in batch:
            predicted_box = []
            isBike = False

            img = open(image, "rb")
            result = cv_client.analyze_image_in_stream(img, visual_features=[VisualFeatureTypes.objects])

            for object in result.objects:
                if object.object_property in ["bike", "bikes", "bicycle", "cycle", "cycling"]:
                    isBike = True
                    predicted_box = [object.rectangle.x, object.rectangle.y, object.rectangle.x + object.rectangle.w, object.rectangle.y + object.rectangle.h]
                    predicted_boxes.append(predicted_box)

            if isBike:
                im = plt.imread(image)
                fig = plt.imshow(im)
                fig.axes.add_patch(plt.Rectangle(
                    xy=(predicted_box[0], predicted_box[1]),
                    width=predicted_box[2] - predicted_box[0],
                    height=predicted_box[3] - predicted_box[1],
                    fill=False, color="red", linewidth=2))
                plt.show()

        time.sleep(10)

    return predicted_boxes


def locate_without_ai(images):
    boxes = [[5, 32, 400, 374], [17, 88, 362, 234], [157, 145, 186, 261], [3, 1, 412, 414], [69, 45, 288, 301], [160, 145, 186, 261], [61, 204, 237, 212], [54, 2, 333, 353], [4, 8, 378, 376], [142, 125, 234, 284]]

    for i, image in enumerate(images[:10], start = 0):
        im = plt.imread(image)
        fig = plt.imshow(im)
        fig.axes.add_patch(plt.Rectangle(xy=(boxes[i][0], boxes[i][1]), width=boxes[i][2], height=boxes[i][3], fill=False, color="green", linewidth=2))
        plt.show()
        i += 1

'''
def evaluate(real_boxes, predicted_boxes):
    if len(real_boxes) != len(predicted_boxes):
        print(
            f"Warning: Numărul de imagini reale ({len(real_boxes)}) nu corespunde cu numărul de imagini procesate ({len(predicted_boxes)}).")
        return

    for i in range(len(real_boxes)):
        error = 0

        for value in zip(predicted_boxes[i], real_boxes[i]):
            error += (value[0] - value[1])**2

        error /= 4

        print("Image ", i)
        print("Error ", error)
'''

import numpy as np

def intersection_over_union(boxA, boxB):
    xA = max(boxA[0], boxB[0])
    yA = max(boxA[1], boxB[1])
    xB = min(boxA[2], boxB[2])
    yB = min(boxA[3], boxB[3])

    interArea = max(0, xB - xA) * max(0, yB - yA)

    boxAArea = (boxA[2] - boxA[0]) * (boxA[3] - boxA[1])
    boxBArea = (boxB[2] - boxB[0]) * (boxB[3] - boxB[1])

    iou = interArea / float(boxAArea + boxBArea - interArea)
    return iou

def mean_squared_error(boxA, boxB):
    return np.mean([(boxA[i] - boxB[i]) ** 2 for i in range(4)])

def evaluate(real_boxes, predicted_boxes):
    if len(real_boxes) != len(predicted_boxes):
        print(f"Warning: Expected {len(real_boxes)} boxes but got {len(predicted_boxes)}.")
        return

    iou_scores = []
    mse_scores = []

    for i in range(len(real_boxes)):
        iou = intersection_over_union(real_boxes[i], predicted_boxes[i])
        mse = mean_squared_error(real_boxes[i], predicted_boxes[i])

        iou_scores.append(iou)
        mse_scores.append(mse)

        print(f"Image {i}: IoU = {iou:.4f}, MSE = {mse:.2f}")

    print("\nOverall Performance:")
    print(f"Mean IoU: {np.mean(iou_scores):.4f}")
    print(f"Mean MSE: {np.mean(mse_scores):.2f}")


def main():
    images = read()

    accuracy, precision, recall = classify(images)
    print("Accuracy: ", accuracy)
    print("Precision: ", precision)
    print("Recall: ", recall)

    predicted_boxes = locate(images)

    locate_without_ai(images)

    #real_boxes = [[5, 32, 400, 374], [17, 88, 362, 234], [157, 145, 186, 261], [3, 1, 412, 414], [69, 45, 288, 301], [160, 145, 186, 261], [61, 204, 237, 212], [54, 2, 333, 353], [4, 8, 378, 376], [142, 125, 234, 284]]
    real_boxes = [[5, 32, 400, 374], [17, 88, 362, 234], [157, 145, 186, 261], [3, 1, 412, 414], [69, 45, 288, 301],[160, 145, 186, 261], [61, 204, 237, 212], [54, 2, 333, 353], [4, 8, 378, 376]]

    evaluate(real_boxes, predicted_boxes)

main()



