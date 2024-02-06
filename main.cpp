#include <fstream>
#include <iostream>
#include <cinttypes>
#include <vector>
#include <locale>
#include <codecvt>
#include <algorithm>

int main() {

    std::ifstream file;

    file.open(L"Мультищитовая3.схема", std::ios_base::binary);

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

    while (file.get(byte)) {
        if (isalnum(byte)) {
            check_name += byte;
        } else if (check_name != "") {
            for (int i = 0; i < 9; ++i) {
                if (check_name == section_names[i] and names_positions[i + 1] == -1) {
                    if (check_name == "ARM")
                        names_positions[i + 1] = position - 2;
                    else
                        names_positions[i + 1] = position - 3;
                    break;
                }
            }
            check_name = "";
        }

        ++position;
    }

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
