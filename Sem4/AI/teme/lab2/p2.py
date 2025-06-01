# Se dau mai multe imagini (salvate in folder-ul "data/images"). Se cere:
#
# sa se vizualizeze una din imagini
# daca imaginile nu aceeasi dimensiune, sa se redimensioneze toate la 128 x 128 pixeli si sa se vizualizeze imaginile intr-un cadru tabelar.
# sa se transforme imaginile in format gray-levels si sa se vizualizeze
# sa se blureze o imagine si sa se afiseze in format "before-after"
# sa se identifice muchiile intr-o imagine si sa se afiseze in format "before-after"
import random

import numpy as np
import pandas as pd
from PIL import Image, ImageFilter
import os
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

def view(name):
    img = mpimg.imread(name)
    plt.imshow(img)
    plt.show()

def tabel(files):
    img_redim = [Image.open(os.path.join('images', file)).resize((128, 128)) for file in files]

    for nr, img in enumerate(img_redim):
        plt.subplot(len(img_redim) // 4 + 1, 4, nr + 1)
        plt.imshow(img)

    plt.show()

def gray_levels(files):
    img_gray = [Image.open(os.path.join('images', file)).resize((128,128)).convert("L") for file in files]

    for nr, img in enumerate(img_gray):
        plt.subplot(len(img_gray) // 4 + 1, 4, nr + 1)
        plt.imshow(img)

    plt.show()

def blurare(file):
    img = Image.open(os.path.join('images', file))
    img_blurata = img.filter(ImageFilter.BLUR)

    plt.subplot(1,2,1)
    plt.imshow(img)
    plt.title("Before")

    plt.subplot(1, 2, 2)
    plt.imshow(img_blurata)
    plt.title("After")

    plt.show()

def muchii(file):
    img = Image.open(os.path.join('images', file))
    muchii = img.filter(ImageFilter.FIND_EDGES)

    plt.subplot(1,2,1)
    plt.imshow(img)
    plt.title("Before")

    plt.subplot(1,2,2)
    plt.imshow(muchii)
    plt.title("Afer")

    plt.show()

def normalizare(files):
    for file in files:
        image = Image.open(os.path.join('images', file)).convert("L")
        image_array = np.array(image, dtype=np.float32)

        image_log = np.log1p(image_array)
        image_norm = 255 * (image_log - np.min(image_log)) / (np.max(image_log) - np.min(image_log))
        image_norm = image_norm.astype(np.uint8)

        plt.axis('off')
        plt.imshow(image_norm, cmap="gray")
        plt.show()


def p2():
    files = os.listdir('images')
    file = random.choice(files)
    view(os.path.join('images', file))
    tabel(files)
    gray_levels(files)
    blurare(file)
    muchii(file)
    normalizare(os.listdir('images'))

p2()

