#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <future>

using namespace std;
using namespace std::chrono;

void print_array(int* arr, int n) {
    int limit = (n > 20) ? 20 : n;
    for (int i = 0; i < limit; i++) {
        cout << arr[i] << " ";
    }
    if (n > 20) cout << "...";
    cout << endl;
}

long long sort_shell(int* arr, int n) {
    auto t1 = high_resolution_clock::now();
    for (int d = n / 2; d > 0; d /= 2) {
        for (int i = d; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= d && arr[j - d] > temp; j -= d)
                arr[j] = arr[j - d];
            arr[j] = temp;
        }
    }
    auto t2 = high_resolution_clock::now();
    return duration_cast<microseconds>(t2 - t1).count();
}

long long sort_selection(int* arr, int n) {
    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        swap(arr[i], arr[min_idx]);
    }
    auto t2 = high_resolution_clock::now();
    return duration_cast<microseconds>(t2 - t1).count();
}

long long sort_counting(int* arr, int n) {
    auto t1 = high_resolution_clock::now();
    if (n <= 0) return 0;
    int max_val = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max_val) max_val = arr[i];

    int* counts = new int[max_val + 1]();
    for (int i = 0; i < n; i++) counts[arr[i]]++;
    int k = 0;
    for (int i = 0; i <= max_val; i++) {
        while (counts[i] > 0) {
            arr[k++] = i;
            counts[i]--;
        }
    }
    delete[] counts;
    auto t2 = high_resolution_clock::now();
    return duration_cast<microseconds>(t2 - t1).count();
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    srand(time(0));

    int test_sizes[] = { 18, 160, 1024, 4096, 32600, 128000 };

    for (int n : test_sizes) {
        cout << "\n--- n = " << n << " ---" << endl;

        int* data = new int[n];
        int* copy1 = new int[n];
        int* copy2 = new int[n];
        int* copy3 = new int[n];

        for (int i = 0; i < n; i++) {
            data[i] = rand() % 10000;
            copy1[i] = data[i];
            copy2[i] = data[i];
            copy3[i] = data[i];
        }

        auto fut1 = async(launch::async, sort_shell, copy1, n);
        auto fut2 = async(launch::async, sort_selection, copy2, n);
        auto fut3 = async(launch::async, sort_counting, copy3, n);

        cout << "Shell: " << fut1.get() << " mks" << endl;
        cout << "Selection: " << fut2.get() << " mks" << endl;
        cout << "Counting: " << fut3.get() << " mks" << endl;

        if (n == 18) {
            cout << "Array: ";
            print_array(copy1, n);
        }

        cout << "Search: ";
        int key;
        cin >> key;

        int low = 0, high = n - 1, res = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (copy1[mid] == key) { res = mid; break; }
            if (copy1[mid] < key) low = mid + 1;
            else high = mid - 1;
        }

        if (res != -1) cout << "Index: " << res << endl;
        else cout << "Not found" << endl;

        delete[] data;
        delete[] copy1;
        delete[] copy2;
        delete[] copy3;
    }

    return 0;
}