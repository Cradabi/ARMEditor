#include <iostream>
#include <fstream>
#include <cinttypes>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <windows.h>
#include <bitset>

int main() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::ifstream file;

    file.open(L"Новая схема.схема", std::ios_base::binary);

    if (!file) {
        std::cout << "File wasn't open\n";
    }

    std::string section_names[9] = {"ARM", "schm",
                                    "cach", "link", "sect",
                                    "objs", "extd", "sch2",
                                    "font"};

    int names_positions[11];

    for (int i = 0; i < 11; ++i) {
        names_positions[i] = -1;
    }

    names_positions[0] = 0;

    char byte;

    std::string check_name{""};

    int position = 0;
    uint8_t counter = 0;

    std::bitset<8> print_binary;

    while (file.get(byte) and !file.eof()) {
        if (isalnum(byte)) {
            check_name += byte;

            SetConsoleTextAttribute(hConsole, 12);
            std::cout << byte;

        } else if (check_name != "") {
            for (int i = 0; i < 9; ++i) {
                if (check_name == section_names[i] and names_positions[i + 1] == -1) {
                    if (check_name == "ARM") {
                        names_positions[i + 1] = position - 2;
                        std::cout << ' ';
                    } else {
                        names_positions[i + 1] = position - 3;
                        std::cout << ' ';
                    }
                    break;
                }
            }

            check_name = "";

        } else {
            SetConsoleTextAttribute(hConsole, 15);

            print_binary = byte;
            std::cout << print_binary;

        }

        ++counter;
        if (counter == 32) {
            std::cout << '\n';
            counter = 0;
        } else
            std::cout << ' ';

        ++position;
    }

    // file.clear();
    // file.seekg(0, std::ios_base::beg);

    std::cout << '\n' << '\n';

    file.close();

    names_positions[10] = position;

    for (int i = 1; i < 10; ++i) {
        std::cout << names_positions[i] - names_positions[i - 1] << ' '
                  << section_names[i - 1] << ' '
                  << names_positions[i + 1] - names_positions[i] << "       /   "
                  << names_positions[i] << '\n';
    }

    std::cout << '\n' << position << '\n';

    return 0;
}
