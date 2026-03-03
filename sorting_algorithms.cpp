
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void printArray(int arr[], int n) {
    if (n <= 50) {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    } else {
        for (int i = 0; i < 25; i++)
            cout << arr[i] << " ";
        cout << "... ";
        for (int i = n - 25; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortRecursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortRecursive(arr, low, pi - 1);
        quickSortRecursive(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    quickSortRecursive(arr, 0, n - 1);
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSortRecursive(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRecursive(arr, l, m);
        mergeSortRecursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(int arr[], int n) {
    mergeSortRecursive(arr, 0, n - 1);
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

void generateArray(int arr[], int n, int type) {
    if (type == 1) {
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (n * 10);
    } else if (type == 2) {
        for (int i = 0; i < n; i++)
            arr[i] = i;
    } else {
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
    }
}

double benchmark(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();
    return (double)(end - start) * 1000 / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));

    int option;
    cout << "1-Bubble\n2-Selection\n3-Insertion\n4-Quick\n5-Merge\n6-Shell\n7-Todos\nEscolha: ";
    cin >> option;

    int n;
    cout << "Tamanho do vetor: ";
    cin >> n;

    int type;
    cout << "1-Aleatorio 2-Crescente 3-Decrescente: ";
    cin >> type;

    int* baseArr = new int[n];
    generateArray(baseArr, n, type);

    if (option == 7) {
        int* temp = new int[n];

        copyArray(baseArr, temp, n);
        cout << "Bubble: " << benchmark(bubbleSort, temp, n) << " ms\n";
        copyArray(baseArr, temp, n);
        cout << "Selection: " << benchmark(selectionSort, temp, n) << " ms\n";
        copyArray(baseArr, temp, n);
        cout << "Insertion: " << benchmark(insertionSort, temp, n) << " ms\n";
        copyArray(baseArr, temp, n);
        cout << "Quick: " << benchmark(quickSort, temp, n) << " ms\n";
        copyArray(baseArr, temp, n);
        cout << "Merge: " << benchmark(mergeSort, temp, n) << " ms\n";
        copyArray(baseArr, temp, n);
        cout << "Shell: " << benchmark(shellSort, temp, n) << " ms\n";

        delete[] temp;
    } else {
        double tempo = 0;
        switch(option) {
            case 1: tempo = benchmark(bubbleSort, baseArr, n); break;
            case 2: tempo = benchmark(selectionSort, baseArr, n); break;
            case 3: tempo = benchmark(insertionSort, baseArr, n); break;
            case 4: tempo = benchmark(quickSort, baseArr, n); break;
            case 5: tempo = benchmark(mergeSort, baseArr, n); break;
            case 6: tempo = benchmark(shellSort, baseArr, n); break;
        }
        cout << "Tempo: " << tempo << " ms\n";
    }

    delete[] baseArr;
    return 0;
}
