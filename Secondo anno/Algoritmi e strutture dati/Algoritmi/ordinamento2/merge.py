def merge (L, i, m , f):
    app = []

    inf = i
    mid = m

    while inf < m and mid < f:
        if L[inf] < L[mid]:
            app.append(L[inf])
            inf += 1
        else :
            app.append(L[mid])
            mid += 1
    
    if inf == m:
        temp = mid
        end = f
    else:
        temp = inf
        end = m

    while temp <= end:
        app.append(L[temp])
        temp += 1

    copia = i
    while copia < f:
        L[copia] = app[copia]
        copia += 1
    return


def mergeSort(L, i , f):
    if f == i or f == i+1:
        return
    m = (f + i)// 2
    mergeSort(L, i, m)
    mergeSort(L, m + 1, f)
    merge(L, i, m, f)
    return


L = [9,6,5,8,7,4,1,2,3,0]
mergeSort(L, 0, len(L)-1)
print(L)










