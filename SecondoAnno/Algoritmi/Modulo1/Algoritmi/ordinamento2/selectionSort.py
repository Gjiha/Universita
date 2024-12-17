def selectionSort(L):

    for k in range(len(L)-1):
        m = k
        j = k + 1
        while j <= (len(L)-1):
            if L[j] < L[m]:
                L[m] , L[j] = L[j], L[m]
            j += 1

    return L

L = [10,6,5,8,9,5,4,5,6,9]
print(selectionSort(L))
