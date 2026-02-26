#include <iostream>

using namespace std;

double calculateParallel(double arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
    }
    return sum;
}

double calculateSerial(double arr[], int n) {
    double sum_inv = 0;
    for (int i = 0; i < n; i++) {
        sum_inv = sum_inv + (1.0 / arr[i]);
    }
    return 1.0 / sum_inv;
}

int main() {
    double C[6] = { 1.5, 1.1, 3.6, 5.4, 4.4, 2.1 };
    int n = 6;

    double res_par = calculateParallel(C, n);
    double res_ser = calculateSerial(C, n);

    cout << "Parallel: " << res_par << " pF" << endl;
    cout << "Serial: " << res_ser << " pF" << endl;

    return 0;
}