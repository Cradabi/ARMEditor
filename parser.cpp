#ifdef WIN32

#include <windows.h>

#endif

#include "parser/SchemeFileParser.cpp"

int main() {

#ifdef WIN32

    SetConsoleOutputCP(CP_UTF8);

#endif

    SchemeFileParser NewParser;

    NewParser.parse(L"..\\schemes_exp\\Мультищитовая3.схема", "..\\logs\\SchemeLogs.txt");

    return 0;
}