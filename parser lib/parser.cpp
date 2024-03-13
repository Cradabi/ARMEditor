#ifdef WIN32

#include <windows.h>

#endif

#include "../parser lib/lib/SchemeFileParser.cpp"

int main() {

#ifdef WIN32

    SetConsoleOutputCP(CP_UTF8);

#endif
    SchemeFileParser NewParser();

    NewParser.parse("..\\schemes_exp\\.схема", "..\\logs\\SchemeLogs.txt");

    return 0;
}
