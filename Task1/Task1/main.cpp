#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

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

    int max_val = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max_val) max_val = arr[i];

    int* counts = new int[max_val + 1]();

    for (int i = 0; i < n; i++)
        counts[arr[i]]++;

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
    srand(time(0));

    int test_sizes[] = { 18, 160, 1024, 4096, 32600, 128000 };

    ofstream file("results.txt");

    cout << "n\tShell\tSelection\tCounting\n";
    file << "n Shell Selection Counting\n";

    for (int s = 0; s < 6; s++) {
        int n = test_sizes[s];

        long long sum_shell = 0;
        long long sum_selection = 0;
        long long sum_counting = 0;

        for (int run = 0; run < 5; run++) {

            int* a = new int[n];
            int* b = new int[n];
            int* c = new int[n];

            for (int i = 0; i < n; i++) {
                int val = rand() % 10000;
                a[i] = val;
                b[i] = val;
                c[i] = val;
            }

            sum_shell += sort_shell(a, n);

            if (n <= 20000)
                sum_selection += sort_selection(b, n);

            sum_counting += sort_counting(c, n);

            delete[] a;
            delete[] b;
            delete[] c;
        }

        long long avg_shell = sum_shell / 5;
        long long avg_selection = (n <= 20000) ? sum_selection / 5 : 0;
        long long avg_counting = sum_counting / 5;

        if (n <= 20000)
            cout << n << "\t" << avg_shell << "\t" << avg_selection << "\t\t" << avg_counting << endl;
        else
            cout << n << "\t" << avg_shell << "\t" << "-" << "\t\t" << avg_counting << endl;

        if (n <= 20000)
            file << n << " " << avg_shell << " " << avg_selection << " " << avg_counting << endl;
        else
            file << n << " " << avg_shell << " - " << avg_counting << endl;
    }

    file.close();

    cout << "\nРезультати записані у файл results.txt\n";

    return 0;
}