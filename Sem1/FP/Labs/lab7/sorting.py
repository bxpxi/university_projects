def merge_sort(data, key=None, reverse=False):
    if len(data) <= 1:
        return data

    mid = len(data) // 2
    left = merge_sort(data[:mid], key=key, reverse=reverse)
    right = merge_sort(data[mid:], key=key, reverse=reverse)

    return merge(left, right, key=key, reverse=reverse)


def merge(left, right, key=None, reverse=False):
    result = []
    left_index = 0
    right_index = 0

    while left_index < len(left) and right_index < len(right):
        if (key(left[left_index]) if key else left[left_index]) <= (key(right[right_index]) if key else right[right_index]):
            result.append(left[left_index])
            left_index += 1
        else:
            result.append(right[right_index])
            right_index += 1

    result.extend(left[left_index:])
    result.extend(right[right_index:])

    if reverse:
        result.reverse()

    return result


def bingo_sort(data, key=None, reverse=False):
    if len(data) <= 1:
        return data

    bins = [0] * (max(data) + 1)

    for item in data:
        bins[item] += 1

    result = []
    for i in range(len(bins)):
        result.extend([i] * bins[i])

    if reverse:
        result.reverse()

    return result


def generic_sort(data, sort_type, key=None, reverse=False):
    if sort_type == "merge_sort":
        return merge_sort(data, key=key, reverse=reverse)
    elif sort_type == "bingo_sort":
        return bingo_sort(data, key=key, reverse=reverse)
    else:
        raise ValueError("Invalid sorting algorithm specified")
