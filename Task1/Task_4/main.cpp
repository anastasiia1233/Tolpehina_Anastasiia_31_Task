#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int counts[256] = { 0 };
    char max_sym = ' ';
    int max_count = 0;
    string line;

    ifstream input("text.txt");

    if (!input.is_open()) {
        cerr << "Pomylka: fail 'text.txt' ne znaydeno!" << endl;
        system("pause");
        return 1;
    }

    while (getline(input, line)) {
        for (unsigned char current : line) {
            if (current <= 32) continue;
            counts[current]++;
        }
    }
    input.close();

    for (int i = 0; i < 256; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_sym = (char)i;
        }
    }

    if (max_count > 0) {
        cout << "Naichastishyi symvol: '" << max_sym << "'" << endl;
        cout << "Kilkist povtoren: " << max_count << endl;

        ofstream output("result.txt");
        if (output.is_open()) {
            output << "Simvol: " << max_sym << endl;
            output << "Kilkist: " << max_count << endl;
            output.close();
        }
    }
    else {
        cout << "Fail 'text.txt' porozhnyi." << endl;
    }
    return 0;
}