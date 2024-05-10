def generic_sort(data, key=lambda x: x, reverse=False, algorithm="merge_sort"):
    if algorithm == "merge_sort":
        return merge_sort(list(data), key=key, reverse=reverse)
    elif algorithm == "bingo_sort":
        return bingo_sort(list(data), key=key, reverse=reverse)
    else:
        raise ValueError("Algoritmul specificat nu se poate realiza.")


def merge_sort(data, key=lambda x: x, reverse=False):
    if len(data) <= 1:
        return data

    middle = len(data) // 2
    left_half = merge_sort(data[:middle], key=key, reverse=reverse)
    right_half = merge_sort(data[middle:], key=key, reverse=reverse)

    return merge(left_half, right_half, key=key, reverse=reverse)


def merge(left, right, key=lambda x: x, reverse=False):
    result = []
    i = j = 0

    while i < len(left) and j < len(right):
        if key(left[i]) < key(right[j]):
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1

    result.extend(left[i:])
    result.extend(right[j:])

    return result


def bingo_sort(data, key=lambda x: x, reverse=False):
    n = len(data)

    while n > 1:
        swapped = False

        for i in range(n - 1):
            if key(data[i]) > key(data[i + 1]):
                data[i], data[i + 1] = data[i + 1], data[i]
                swapped = True

        if not swapped:
            break

    return data if not reverse else list(reversed(data))
