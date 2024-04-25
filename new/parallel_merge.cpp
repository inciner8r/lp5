#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void merge(vector<int>& array, int low1, int high1, int low2, int high2) {
    int i = low1, j = low2, k = 0;
    vector<int> temp(high2 - low1 + 1);

    while (i <= high1 && j <= high2) {
        if (array[i] < array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while (i <= high1)
        temp[k++] = array[i++];

    while (j <= high2)
        temp[k++] = array[j++];

    for (i = low1, j = 0; i <= high2; i++, j++)
        array[i] = temp[j];
}

void mergesortp(vector<int>& array, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            {
                mergesortp(array, low, mid);
            }

#pragma omp section
            {
                mergesortp(array, mid + 1, high);
            }
        }

        merge(array, low, mid, mid + 1, high);
    }
}

void mergesorts(vector<int>& array, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergesorts(array, low, mid);
        mergesorts(array, mid + 1, high);
        merge(array, low, mid, mid + 1, high);
    }
}

void display(const vector<int>& array) {
    for (int i = 0; i < array.size(); i++)
        cout << array[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> array(n);

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 32;
    }

    cout << "Original Array: ";
    display(array);

    vector<int> array_p = array; // Copy for parallel version
    vector<int> array_s = array; // Copy for serial version

    clock_t start_p = clock();
    mergesortp(array_p, 0, n - 1);
     cout << "Final Array (Parallel): ";
    display(array_p);

    clock_t stop_p = clock();

   
    clock_t start_s = clock();
    mergesorts(array_s, 0, n - 1);
     cout << "Final Array (Serial): ";
    display(array_s);

    clock_t stop_s = clock();

   
    double duration_p = double(stop_p) / CLOCKS_PER_SEC;
    double duration_s = double(stop_s) / CLOCKS_PER_SEC;

    cout << "Time required for parallel: " << duration_p << " seconds" << endl;
    cout << "Time required for serial: " << duration_s << " seconds" << endl;

    return 0;
}
