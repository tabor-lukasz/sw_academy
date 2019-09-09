#ifndef SORTMERGE_H
#define SORTMERGE_H

template <typename T>
void merge(T arr[], int l, int m, int r, bool oper(T a, T b))
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    T L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if ( oper(L[i],R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(T arr[], int l, int r, bool oper(T a, T b) = [](T a, T b){return a < b;})
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m, oper);
        mergeSort(arr, m+1, r, oper);

        merge(arr, l, m, r,oper);
    }
}

#endif // SORTMERGE_H
