#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

void zapovnennya(double** a, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 21 - 10;
        }
    }
}

int sektor1(double** a, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j && i + j < n - 1) {
                if ((int)a[i][j] % 2 != 0) {
                    suma += (int)a[i][j];
                }
            }
        }
    }
    return suma;
}

double serednye_neg(double** a, int n) {
    double suma = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < 0) {
                suma += a[i][j];
                k++;
            }
        }
    }
    return (k == 0) ? 0 : suma / k;
}

int sektor10(double** a, int n, double ser) {
    int k = 0;
    int mid = n / 2;

    for (int i = 0; i < n; i++) {
        for (int j = mid + 1; j < n; j++) {
            a[i][j] = ser;
            k++;
        }
    }
    return k;
}

void vivod(double** a, int n) {
    cout << "\nМатриця:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(6) << a[i][j];
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ukr");

    int n;
    cout << "Введіть розмір матриці: ";
    cin >> n;

    double** a = new double* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
    }

    zapovnennya(a, n);
    vivod(a, n);

    int s1 = sektor1(a, n);
    double avg = serednye_neg(a, n);
    int k10 = sektor10(a, n, avg);

    cout << "\nСума непарних у секторі 1: " << s1 << endl;
    cout << "Кількість елементів у секторі 10: " << k10 << endl;
    cout << "Середнє від'ємних: " << avg << endl;

    vivod(a, n);

    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;

    return 0;
}