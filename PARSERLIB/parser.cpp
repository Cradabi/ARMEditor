#ifdef WIN32

#include <windows.h>

#endif

#include "lib/SchemeFileParser.cpp"

int main() {

#ifdef WIN32

    SetConsoleOutputCP(CP_UTF8);

#endif

    /*Scheme::SchemeParams tmp_sch_params;    // Экземплр структуры параметров схемы

    // Заполняем текущие параметры схемы
    tmp_sch_params.width = 15360;
    tmp_sch_params.height = 1200;
    tmp_sch_params.objects_amount = 10;
    tmp_sch_params.name_scheme = "Мультищитовая";
    tmp_sch_params.objects_vector = {};
    tmp_sch_params.objects_vector.push_back(new Ellipse(central_x - half_width, central_y - half_height, half_width * 2, half_height * 2, (360 - angle) % 360, int line_width, int style_line,
                const std::vector<int> &line_color(rgb), const std::string &help_text, bool bool_show,
                const std::vector<int> &filling_color(rgb), bool bool_show_filling));
    std::vector <int> col = {200, 200, 200};
    FiguresClasses::Set set(1, 20, 20, 1, col);
    tmp_sch_params.set_object = set;

    Scheme sch(tmp_sch_params);     // Экземпляр схемы

    QPainter painter;
    painter.begin(this);
    sch.draw_scheme(painter);
    painter.end();

    */
    SchemeFileParser NewParser;

    NewParser.parse(L"..\\schemes_exp\\Мультищитовая3.схема", "..\\logs\\SchemeLogs.txt");

    return 0;
}
