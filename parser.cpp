#include <iostream>
#include <fstream>
#include <cinttypes>
#include <locale>
#include <windows.h>
#include <bitset>

#include "parser/SchemeFileParser.cpp"

int main() {

    SetConsoleOutputCP(CP_UTF8);

    SchemeFileParser NewParser;

    NewParser.parse(L"..\\schemes_exp\\ЛинияВерт.схема", "..\\logs\\SchemeLogs.txt");

    return 0;
}