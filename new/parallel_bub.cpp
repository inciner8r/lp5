#include <omp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void buble_p(int n, int array[]) {
    int var = 0;
    for (int i = 0; i < n; i++) {
        #pragma omp parallel for
        for (int j = var; j < n - 1; j += 2) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
        var = 1 - var; // Toggle var for next pass
    }
}

void buble_s(int n, int array[]) {
    int var = 0;
    for (int i = 0; i < n; i++) {
        for (int j = var; j < n - 1; j += 2) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
        var = 1 - var; // Toggle var for next pass
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int array[n];

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 32;
    }

    cout << "Original Array: ";
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    int array_p[n], array_s[n];
    copy(array, array + n, array_p); // Copy for parallel version
    copy(array, array + n, array_s); // Copy for serial version

    clock_t start_p = clock();
    buble_p(n, array_p);
    clock_t stop_p = clock();

    cout << "Final Array (Parallel): ";
    for (int i = 0; i < n; i++) {
        cout << array_p[i] << " ";
    }
    cout << endl;

    clock_t start_s = clock();
    buble_s(n, array_s);
    clock_t stop_s = clock();

    cout << "Final Array (Serial): ";
    for (int i = 0; i < n; i++) {
        cout << array_s[i] << " ";
    }
    cout << endl;

    double duration_p = double(stop_p) / CLOCKS_PER_SEC;
    double duration_s = double(stop_s) / CLOCKS_PER_SEC;

    cout << "Time required for parallel: " << duration_p << " seconds" << endl;
    cout << "Time required for serial: " << duration_s << " seconds" << endl;

    return 0;
}
