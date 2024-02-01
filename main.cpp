#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Line { // класс линии
public:
    Line(int st_x, int st_y, int end_x, int end_y) {
        change_center_cords(st_x, st_y, end_x, end_y);
    }

    void change_center_cords(int st_x, int st_y, int end_x,
                             int end_y) { //меняет координаты начала, конца, центра линии
        this->start_x = st_x;
        this->start_y = st_y;
        this->end_x = end_x;
        this->end_y = end_y;
        int x_cord = 0;
        int y_cord = 0;
        //начало изменений координат центра
        if (st_x >= end_x) {
            x_cord = end_x + floor(abs(st_x - end_x) / 2);
        } else {
            x_cord = st_x + floor(abs(st_x - end_x) / 2);
        }
        if (st_y >= end_y) {
            y_cord = end_y + floor(abs(st_y - end_y) / 2);
        } else {
            y_cord = st_y + floor(abs(st_y - end_y) / 2);
        }
        this->center_x = x_cord;
        this->center_y = y_cord;
    }

    void set_line_color(vector<int> lin_col) { //меняет вектор цвета линии
        this->line_color = lin_col;
    }

    vector<int> get_line_color() { //выводит вектор цветов линии rgb
        return this->line_color;
    }


    string get_type_object() {
        return this->type_object;
    }

    int get_st_x() { //выводит координату x начала линии
        return this->start_x;
    }

    int get_st_y() {  //выводит координату y начала линии
        return this->start_y;
    }

    int get_end_x() {  //выводит координату x конца линии
        return this->end_x;
    }

    int get_end_y() {  //выводит координату y конца линии
        return this->end_y;
    }

    int get_center_cord_x() {  //возвращает x-координату центра
        return this->center_x;
    }

    int get_center_cord_y() {  //возвращает y-координату центра
        return this->center_y;
    }

    void show_help() {
        this->bool_show_help = true;
    }

    void show_line() {
        this->bool_show = true;
    }

    void hide_help() {
        this->bool_show_help = false;
    }

    void hide_line() {
        this->bool_show = false;
    }

    string text = ""; //текст на линии
    string help_line = ""; //подсказка к линии
    string font_name = ""; //имя шрифта
    bool bool_show_help = false; //флаг показывания подсказки
    bool bool_show = true; //флаг показывания линии
    bool bold_font = false; //флаг жирности шрифта
    bool italic_font = false; //флаг наклонности шрифта
    bool underlined_font = false; //флаг подчеркнутости шрифта
    bool crossed_font = false; //флаг зачеркнутости шрифта
    int font_size = 14; //размер шрифта
    int number_of_text = 0; //количество текстовых вставок
    int style_line = 1; //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"
    int line_width = 2;
    int start_style_arrow = 0; //тип начала линии 0-"esNone", 1-"esRoundArrow", 2-"esSharpArrow", 3-"esDot", 4-"esRightArrow"
    int end_style_arrow = 0; //тип начала линии 0-"esNone", 1-"esRoundArrow", 2-"esSharpArrow", 3-"esDot", 4-"esRightArrow"
    vector<string> style_arrow_list = {"esNone", "esRoundArrow", "esSharpArrow", "esDot",
                                       "esRightArrow"}; //список названий типов стрелок
    vector<string> style_line_list = {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6",
                                      "psDash1", "psDash2"}; //список названий стилей линий
private:
    string type_object = "Линия";
    int start_x = 0;
    int start_y = 0;
    int end_x = 0;
    int end_y = 0;
    int center_x = 0;
    int center_y = 0;
    vector<int> line_color = {0, 0, 0};
};


class Rectangle { //класс прямоугольника
public:
    Rectangle(int x, int y, int width, int height) {
        change_center_cords(x, y, width, height);
    }

    void
    change_center_cords(int x, int y, int width,
                        int height) { //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->center_x = this->x + floor(this->width / 2);
        this->center_y = this->y + floor(this->height / 2);
    }

    void set_angle(int angl) {
        this->angle = angl;
    }

    void set_line_color(vector<int> ln_col) {
        this->line_color = ln_col;
    }

    void set_filling_color(vector<int> fil_col) {
        this->filling_color = fil_col;
    }

    void set_style_frame(int st_frame) {
        if (st_frame >= 0 && st_frame < this->style_frame_list.size()) {
            this->style_frame = st_frame;
        }
    }

    void set_style_gradient_filling(int st_gradient) {
        if (st_gradient >= 0 && st_gradient < this->style_gradient_list.size()) {
            this->style_gradient_filling = st_gradient;
        }
    }

    void set_style_line(int st_line) {
        if (st_line >= 0 && st_line < this->style_line_list.size()) {
            this->style_line = st_line;
        }
    }

    string get_type_object() {
        return this->type_object;
    }

    int get_style_frame() {
        return this->style_frame;
    }

    int get_style_line() {
        return this->style_line;
    }

    int get_style_gradient_filling() {
        return this->style_gradient_filling;
    }

    int get_angle() {
        return this->angle;
    }

    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

    int get_width() {
        return this->width;
    }

    int get_height() {
        return this->height;
    }

    int get_center_x() {
        return this->center_x;
    }

    int get_center_y() {
        return this->center_y;
    }

    vector<int> get_line_color() {
        return this->line_color;
    }

    vector<int> get_filling_color() {
        return this->filling_color;
    }

    void show_rect() {
        this->bool_show = true;
    }

    void show_help() {
        this->bool_show_help = true;
    }

    void show_filling() {
        this->bool_show_filling = true;
    }

    void hide_rect() {
        this->bool_show = false;
    }

    void hide_help() {
        this->bool_show_help = false;
    }

    void hide_filling() {
        this->bool_show_filling = false;
    }


    string help_line = ""; //текст подсказки
    bool bool_show_help = false; // показывать подсказку
    bool bool_show = true; //показывать прямоугольник
    bool bool_show_filling = false; //показывать заливку
    int style_frame = 0; // стиль рамки 0-"fsNull", 1-"fsButtonDown", 2-"fsButtonUp", 3-"fsBagetDown", 4-"fsBagetUp", 5-"fsDoubleDown", 6-"fsDoubleUp"
    int style_gradient_filling = 0; //0-stNone", 1-"stHorzPlane", 2-"stVertPlane", 3-"stHorzPipe", 4-"stVertPipe", 5-"stSphere", 6-"stCone", 7-"stBTTrapezoid", 8-"stLRTrapezoid", 9-"stTBTrapezoid"
    int style_line = 1;  //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"
    int line_width = 2;
    vector<int> line_color = {0, 0, 0}; //цвет линии
    vector<int> filling_color = {255, 255, 255}; //цвет заливки
    vector<string> style_frame_list = {"fsNull", "fsButtonDown", "fsButtonUp", "fsBagetDown", "fsBagetUp",
                                       "fsDoubleDown", "fsDoubleUp"}; //список названий стилей линий
    vector<string> style_gradient_list = {"stNone", "stHorzPlane", "stVertPlane", "stHorzPipe", "stVertPipe",
                                          "stSphere", "stCone", "stBTTrapezoid",
                                          "stLRTrapezoid",
                                          "stTBTrapezoid"}; //список названий стилей градиентных заливок
    vector<string> style_line_list = {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6",
                                      "psDash1", "psDash2"}; //список названий стилей линий

private:
    string type_object = "Прямоугольник";
    int angle = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int center_x = 0;
    int center_y = 0;

};


class Ellipse { //класс эллипса
public:
    Ellipse() {}

    Ellipse(int x, int y, int width, int height) {
        change_center_cords(x, y, width, height);
    }

    void
    change_center_cords(int x, int y, int width,
                        int height) { //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->center_x = this->x + floor(this->width / 2);
        this->center_y = this->y + floor(this->height / 2);
    }

    void set_angle(int angl) {
        this->angle = angl;
    }

    void set_line_color(vector<int> ln_col) {
        this->line_color = ln_col;
    }

    void set_filling_color(vector<int> fil_col) {
        this->filling_color = fil_col;
    }


    void set_style_line(int st_line) {
        if (st_line >= 0 && st_line < this->style_line_list.size()) {
            this->style_line = st_line;
        }
    }

    string get_type_object() {
        return this->type_object;
    }

    int get_style_line() {
        return this->style_line;
    }


    int get_angle() {
        return this->angle;
    }

    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

    int get_width() {
        return this->width;
    }

    int get_height() {
        return this->height;
    }

    int get_center_x() {
        return this->center_x;
    }

    int get_center_y() {
        return this->center_y;
    }

    vector<int> get_line_color() {
        return this->line_color;
    }

    vector<int> get_filling_color() {
        return this->filling_color;
    }

    void show_ellipse() {
        this->bool_show = true;
    }

    void show_help() {
        this->bool_show_help = true;
    }

    void show_filling() {
        this->bool_show_filling = true;
    }

    void hide_ellipse() {
        this->bool_show = false;
    }

    void hide_help() {
        this->bool_show_help = false;
    }

    void hide_filling() {
        this->bool_show_filling = false;
    }


    string help_line = ""; //текст подсказки
    bool bool_show_help = false; // показывать подсказку
    bool bool_show = true; //показывать эллипс
    bool bool_show_filling = false; //показывать заливку
    int style_line = 1;  //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"
    int line_width = 2;
    vector<int> line_color = {0, 0, 0}; //цвет линии
    vector<int> filling_color = {255, 255, 255}; //цвет заливки
    vector<string> style_line_list = {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6",
                                      "psDash1", "psDash2"}; //список названий стилей линий

protected:
    string type_object = "Эллипс";
    int angle = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int center_x = 0;
    int center_y = 0;

};

class Arc : public Ellipse { //класс дуги, которая наслдуется от эллипса

public:
    Arc(int x, int y, int width, int height, int st_angle, int end_angle) : Ellipse() {
        this->type_object = "Дуга";
        this->start_angle = st_angle;
        this->end_angle = end_angle;
        change_center_cords(x, y, width, height);
    }

    void set_start_angle(int st_angle) {
        this->start_angle = st_angle;
    }

    void set_end_angle(int end_angle) {
        this->end_angle = end_angle;
    }

    int get_start_angle() {
        return this->start_angle;
    }

    int get_end_angle() {
        return this->end_angle;
    }

private:
    int start_angle = 0;
    int end_angle = 0;

};


class Transition_point { //класс точки перехода
public:
    Transition_point(int number, int x, int y, int width,
                     int height) { // получает номер точки перехода, координаты, ширина, высота
        this->number_of_transition_point = number;
        change_center_cords(x, y, width, height);
    }

    void
    change_center_cords(int x, int y, int width,
                        int height) { //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->center_x = this->x + floor(this->width / 2);
        this->center_y = this->y + floor(this->height / 2);
    }


    void set_filling_color(vector<int> fil_col) {
        this->filling_color = fil_col;
    }

    string get_type_object() {
        return this->type_object;
    }


    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

    int get_width() {
        return this->width;
    }

    int get_height() {
        return this->height;
    }

    int get_center_x() {
        return this->center_x;
    }

    int get_center_y() {
        return this->center_y;
    }


    vector<int> get_filling_color() {
        return this->filling_color;
    }

    void show_rect() {
        this->bool_show = true;
    }

    void show_help() {
        this->bool_show_help = true;
    }

    void show_filling() {
        this->bool_show_filling = true;
    }

    void hide_rect() {
        this->bool_show = false;
    }

    void gide_help() {
        this->bool_show_help = false;
    }

    void hide_filling() {
        this->bool_show_filling = false;
    }


    string help_line = ""; //текст подсказки
    bool bool_show_help = false; // показывать подсказку
    bool bool_show = true; //показывать прямоугольник
    bool bool_show_filling = false; //показывать заливку
    vector<int> filling_color = {255, 255, 255}; //цвет заливки

private:
    string type_object = "Кнопка перехода";
    int number_of_transition_point = 0; // номер точки перехода
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int center_x = 0;
    int center_y = 0;

};


class Transition_button { //класс кнопка перехода
public:
    Transition_button(int number, int x, int y, int width, int height) {
        this->number_of_transition_button = number;
        change_center_cords(x, y, width, height);
    }

    void
    change_center_cords(int x, int y, int width,
                        int height) { //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->center_x = this->x + floor(this->width / 2);
        this->center_y = this->y + floor(this->height / 2);
    }

    void set_angle(int angl) {
        this->angle = angl;
    }

    void set_line_color(vector<int> fn_col) {
        this->font_color = fn_col;
    }

    void set_filling_color(vector<int> fil_col) {
        this->filling_color = fil_col;
    }


    string get_type_object() {
        return this->type_object;
    }


    int get_angle() {
        return this->angle;
    }

    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

    int get_width() {
        return this->width;
    }

    int get_height() {
        return this->height;
    }

    int get_center_x() {
        return this->center_x;
    }

    int get_center_y() {
        return this->center_y;
    }

    vector<int> get_font_color() {
        return this->font_color;
    }

    vector<int> get_filling_color() {
        return this->filling_color;
    }

    void show_button() {
        this->bool_show = true;
    }

    void show_help() {
        this->bool_show_help = true;
    }

    void show_filling() {
        this->bool_show_filling = true;
    }

    void hide_button() {
        this->bool_show = false;
    }

    void hide_help() {
        this->bool_show_help = false;
    }

    void hide_filling() {
        this->bool_show_filling = false;
    }


    string help_line = ""; //текст подсказки
    string text = ""; //текст кнопки
    string font_name = "Arial";
    bool bool_show_help = false; // показывать подсказку
    bool bool_show = true; //показывать кнопку
    bool bool_show_filling = false; //показывать заливку
    bool bold_font = false; //флаг жирности шрифта
    bool italic_font = false; //флаг наклонности шрифта
    bool underlined_font = false; //флаг подчеркнутости шрифта
    bool crossed_font = false; //флаг зачеркнутости шрифта
    bool auto_size_text = false; //авторазмер текста
    int hAlignment = 2;
    int vAlignment = 2;
    int font_size = 14;
    vector<int> font_color = {0, 0, 0}; //цвет шрифта
    vector<int> filling_color = {255, 255, 255}; //цвет заливки
    vector<string> hAlignment_list = {"ahLeft", "ahRight", "ahCenter"};
    vector<string> vAlignment_list = {"avTop", "avBottom", "avCenter"};

private:
    string type_object = "Кнопка перехода";
    int number_of_transition_button = 0;
    int angle = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int center_x = 0;
    int center_y = 0;

};

class CrookedLine { //класс кривой
public:
    CrookedLine() {}

    CrookedLine(vector<vector<int>> points_vector) {
        change_center_cords(points_vector);
    }

    void
    change_center_cords(
            vector<vector<int>> points_vector) { //меняет координаты начала, конца, центра многоугольника. Эта функция нужня для изменения размеров.
        int max_x = 0;
        int max_y = 0;
        int min_x = points_vector[0][0];
        int min_y = points_vector[0][1];
        for (auto i: points_vector) {
            if (i[0] < min_x) {
                min_x = i[0];
            }
            if (i[0] > max_x) {
                max_x = i[0];
            }
            if (i[1] < min_y) {
                min_y = i[1];
            }
            if (i[1] > max_x) {
                max_y = i[1];
            }
        }
        this->x = min_x;
        this->y = min_y;
        this->width = max_x - min_x;
        this->height = max_y - min_y;
        this->center_x = this->x + floor(this->width / 2);
        this->center_y = this->y + floor(this->height / 2);
    }

    void set_angle(int angl) {
        this->angle = angl;
    }

    void set_line_color(vector<int> ln_col) {
        this->line_color = ln_col;
    }

    void set_filling_color(vector<int> fil_col) {
        this->filling_color = fil_col;
    }


    void set_style_line(int st_line) {
        if (st_line >= 0 && st_line < this->style_line_list.size()) {
            this->style_line = st_line;
        }
    }

    string get_type_object() {
        return this->type_object;
    }

    int get_style_line() {
        return this->style_line;
    }

    int get_angle() {
        return this->angle;
    }

    int get_x() {
        return this->x;
    }

    int get_y() {
        return this->y;
    }

    int get_width() {
        return this->width;
    }

    int get_height() {
        return this->height;
    }

    int get_center_x() {
        return this->center_x;
    }

    int get_center_y() {
        return this->center_y;
    }

    vector<int> get_line_color() {
        return this->line_color;
    }

    vector<int> get_filling_color() {
        return this->filling_color;
    }

    void show_polygon() {
        this->bool_show = true;
    }

    void show_help() {
        this->bool_show_help = true;
    }

    void show_filling() {
        this->bool_show_filling = true;
    }

    void hide_polygon() {
        this->bool_show = false;
    }

    void hide_help() {
        this->bool_show_help = false;
    }

    void hide_filling() {
        this->bool_show_filling = false;
    }


    string help_line = ""; //текст подсказки
    bool bool_show_help = false; // показывать подсказку
    bool bool_show = true; //показывать прямоугольник
    bool bool_show_filling = false; //показывать заливку
    int style_line = 1;  //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"
    int line_width = 2;
    vector<int> line_color = {0, 0, 0}; //цвет линии
    vector<int> filling_color = {255, 255, 255}; //цвет заливки
    vector<string> style_line_list = {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6",
                                      "psDash1", "psDash2"}; //список названий стилей линий

protected:
    string type_object = "Кривая линия";
    int angle = 0;
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int center_x = 0;
    int center_y = 0;

};

class Polygon : public CrookedLine { //класс многоугольника
public:
    Polygon(vector<vector<int>> points_vector, bool end_polygon = false) : CrookedLine() {
        this->type_object = "Полигон";
        this->end_polygone = end_polygon;
        change_center_cords(points_vector);
    }

    bool get_end_polygon() {
        return this->end_polygone;
    }

    void set_end_polygon(bool end_pol) {
        this->end_polygone = end_pol;
    }

private:
    bool end_polygone;
};


int main() {
    Polygon pol({{1, 2}, {2, 3}, {5, 0}}, true);
    cout << pol.get_x() << " " << pol.get_y() << endl << pol.get_width() << " " << pol.get_height() << endl << pol.get_end_polygon() << endl << pol.get_type_object();
    return 0;
}

