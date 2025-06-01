import numpy as np
import matplotlib.pyplot as plt
import time
import Levenshtein
from PIL import Image, ImageDraw

from azure.cognitiveservices.vision.computervision import ComputerVisionClient
from azure.cognitiveservices.vision.computervision.models import OperationStatusCodes
from azure.ai.vision.imageanalysis import ImageAnalysisClient
from azure.ai.vision.imageanalysis.models import VisualFeatures
from azure.core.credentials import AzureKeyCredential
from msrest.authentication import CognitiveServicesCredentials

# Azure authentication
subscription_key = "7V7ycWx3H2kw14NJCfvzmJNl9daU00DpJ4M9oaShjhQuj7SRL3XOJQQJ99BCAC5RqLJXJ3w3AAAFACOGpYkm"
endpoint = "https://ai-ubb-2025-patricia.cognitiveservices.azure.com/"
computervision_client = ComputerVisionClient(endpoint, CognitiveServicesCredentials(subscription_key))
cv_client = ImageAnalysisClient(endpoint=endpoint, credential=AzureKeyCredential(subscription_key))


def proccess_image(img):
    read_response = computervision_client.read_in_stream(
        image=img,
        mode="Handwritten",
        raw=True
    )

    operation_id = read_response.headers['Operation-Location'].split('/')[-1]
    while True:
        read_result = computervision_client.get_read_result(operation_id)
        if read_result.status not in ['notStarted', 'running']:
            break
        time.sleep(1)

    result = []
    if read_result.status == OperationStatusCodes.succeeded:
        for text_result in read_result.analyze_result.read_results:
            for line in text_result.lines:
                result.append(line.text)

    return result


# 1a - Levenshtein Distance - masoara numarul minim de operatii (inserare, stergere, substituire) pentru a transforma
# un sir de caractere in altul
def verify_levenshtein(result, text):
    char_dist = Levenshtein.distance(text, result)
    words = text.split()
    result_words = result.split()
    word_dist = Levenshtein.distance(words, result_words)
    return char_dist, word_dist


# 1b - varianta 1: jaccard - masoara similaritatea
# compara seturile de cuvinte, se compara la nivel de cuvant
def verify_jaccard(text, result):
    char_dist, word_dist = verify_levenshtein(result, text)
    similarity = 1 - (word_dist / max(len(text), len(result)))
    return similarity


# 1b - varianta 2: hamming
def verify_hamming(text, result):
    if len(text) != len(result):
        print("Nu se poate calcula, deoarece nu au aceeasi lungime.")
        return None
    else:
        count = 0
        for i in range(len(text)):
            if text[i] != result[i]:
                count += 1
        return count


# 1b - varianta 3: Distanta euclediana
def verify_euclidean(text, result):
    text_ascii = np.array([ord(c) for c in text])
    result_ascii = np.array([ord(c) for c in result])

    if len(text_ascii) != len(result_ascii):
        print("Nu se poate calcula, deoarece nu au aceeasi lungime.")
        return None
    else:
        diff = np.sum((text_ascii - result_ascii) ** 2)
        dist = np.sqrt(diff)
        return dist


# 2 - calitatea localizarii corecte a textului in imagine
def quality_check(image_file):
    with open(image_file, 'rb') as image:
        image_data = image.read()

    image = open(image_file, 'rb')

    result = cv_client.analyze(
        image_data=image_data,
        visual_features=[VisualFeatures.READ]
    )

    if result.read is not None:
        image = Image.open(image_file)
        plt.axis('off')
        draw = ImageDraw.Draw(image)
        color = 'red'

        for line in result.read.blocks[0].lines:
            draw_line_polygon = True
            r = line.bounding_polygon
            bounding_polygon = ((r[0].x, r[0].y), (r[1].x, r[1].y), (r[2].x, r[2].y), (r[3].x, r[3].y))
            if draw_line_polygon:
                draw.polygon(bounding_polygon, outline=color, width=3)

    plt.imshow(image)
    plt.show()


# 3 - imbunatatirea procesului
def proccess_image_better(image_file):
    with open(image_file, 'rb') as image:
        image_data = image.read()

    result = cv_client.analyze(
        image_data=image_data,
        visual_features=[VisualFeatures.READ]
    )

    if result.read is not None:
        text = ""
        for line in result.read.blocks[0].lines:
            text += line.text + "\n"

        return text

    else:
        return None


def __main__():
    text = "Succes in rezolvarea tEMELOR la LABORAtoarele de Inteligenta Artificiala"
    result = proccess_image(open("test2 (1).jpeg", "rb"))
    result_words = ' '.join(result)
    print("Procesare initiala:")
    print(result_words)

    char_dist, word_dist = verify_levenshtein(result_words, text)
    print("Distanta Levensthein la nivel de caracter:", char_dist)
    print("Distanta Levensthein la nivel de cuvant:", word_dist)

    jaccard = verify_jaccard(text, result_words)
    print("Similitudinea Jaccard: ", jaccard)

    hamming = verify_hamming(text, result_words)
    print("Similitudinea Hamming: ", hamming)

    euclidean = verify_euclidean(text, result_words)
    # euclidean = verify_euclidean("ana", "ane")
    print("Similitudinea Euclidean: ", euclidean)

    quality_check("test2 (1).jpeg")

    result2 = proccess_image_better("test2 (1).jpeg")
    print("Procesare imbunatatita:")
    print(result2)


__main__()
