#include <iostream>
#include <iomanip>

using namespace std;

void vvedennya(double** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

int obchisliti_sektor1(double** a, int n) {
    int suma = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j && (i + j) < (n - 1)) {
                int temp = (int)a[i][j];
                if (temp % 2 != 0) {
                    suma += temp;
                }
            }
        }
    }
    return suma;
}

double znayti_ser_arifm(double** a, int n) {
    double suma_v = 0;
    int k_v = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < 0) {
                suma_v += a[i][j];
                k_v++;
            }
        }
    }
    if (k_v > 0) return suma_v / k_v;
    return 0;
}

int obrobka_sektor10(double** a, int n, double znachennya) {
    int k_s10 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > (n - 1) / 2.0) {
                k_s10++;
                a[i][j] = znachennya;
            }
        }
    }
    return k_s10;
}

void vivod(double** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;

    double** a = new double* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
    }

    vvedennya(a, n);

    int res1 = obchisliti_sektor1(a, n);
    double res_ser = znayti_ser_arifm(a, n);
    int res10 = obrobka_sektor10(a, n, res_ser);

    cout << res1 << endl;
    cout << res10 << endl;
    cout << res_ser << endl;

    vivod(a, n);

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;

    return 0;
}