unsorted_list = [65, 10, 85, 28, 33, 74, 67, 56, 31, 62, 45, 24]
def bubble_sort(input_list: list) -> list:
    if input_list == []:
        return []
    for i in range(0, len(input_list)):
        for j in range(0, len(input_list)-i-1):
            if input_list[j] > input_list[j+1]:
                input_list[j], input_list[j+1] = input_list[j+1], input_list[j]
    return input_list
def selection_sort(input_list: list) -> list:
    if input_list == []:
        return []
    for i in range(0, len(input_list) - 1):
        minIndex = i
        for j in range(i + 1, len(input_list)):
            if input_list[j] < input_list[minIndex]:
                minIndex = j
        if i != minIndex:
            input_list[i], input_list[minIndex] = input_list[minIndex], input_list[i]
    return input_list
def insertion_sort(input_list: list) -> list:
    for i in range(len(input_list)):
        pre = i-1
        current = input_list[i]
        while pre >= 0 and input_list[pre] > current:
            input_list[pre+1] = input_list[pre]
            pre -= 1
        input_list[pre+1] = current
    return input_list
print(unsorted_list)
print(bubble_sort(unsorted_list))
print(selection_sort(unsorted_list))
print(insertion_sort(unsorted_list))
