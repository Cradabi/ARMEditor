#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>

#include "SchemeFileParser.h"

int main() {
    
    SetConsoleOutputCP(CP_UTF8);

    SchemeFileParser NewParser;

    NewParser.OpenWorkFiles(L"Линия.схема", "logs\\SchemeLogs.txt");

    NewParser.Parsing();

    return 0;
}