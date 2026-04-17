#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

struct Gurtogitok {
    string name;
    string address;
    int rooms;
    int students;
    string commandant;
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n;
    cout << "Введіть кількість гуртожитків: ";
    cin >> n;

    Gurtogitok g[100];

    for (int i = 0; i < n; i++) {
        cout << "\nГуртожиток #" << i + 1 << endl;

        cout << "Назва: ";
        cin >> g[i].name;

        cout << "Адреса: ";
        cin >> g[i].address;

        cout << "К-сть кімнат: ";
        cin >> g[i].rooms;

        cout << "К-сть жильців: ";
        cin >> g[i].students;

        cout << "Комендант: ";
        cin >> g[i].commandant;
    }

    int maxRooms = 0;
    int maxStudents = 0;
    int indexRooms = 0;
    int indexStudents = 0;

    for (int i = 0; i < n; i++) {
        if (g[i].rooms > maxRooms) {
            maxRooms = g[i].rooms;
            indexRooms = i;
        }

        if (g[i].students > maxStudents) {
            maxStudents = g[i].students;
            indexStudents = i;
        }
    }

    cout << "\nГуртожиток з найбільшою кількістю кімнат:\n";
    cout << g[indexRooms].name << ", " << g[indexRooms].address << endl;

    cout << "\nГуртожиток з найбільшою кількістю студентів:\n";
    cout << g[indexStudents].name << ", " << g[indexStudents].address << endl;

    return 0;
}