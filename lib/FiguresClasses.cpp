#include "FiguresClasses.h"

using namespace FiguresClasses;

Line::Line(int st_x, int st_y, int end_x, int end_y) {
    change_center_cords(st_x, st_y, end_x, end_y);
}

//меняет координаты начала, конца, центра линии
void Line::change_center_cords(int st_x, int st_y, int end_x,
                               int end_y) {
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

//меняет вектор цвета линии
void Line::set_line_color(const std::vector<int> &lin_col) {
    this->line_color = lin_col;
}

void Line::set_text(const std::string &text) {
    this->text = text;
}

void Line::set_help_text(const std::string &help) {
    this->help_text = help;
}

void Line::set_font_name(const std::string &fn_name) {
    this->font_name = fn_name;
}

void Line::set_font_size(int fn_size) {
    this->font_size = fn_size;
}

void Line::set_font_color(const std::vector<int> &fn_col) {
    this->font_color = fn_col;
}

void Line::set_italic_font(bool italic) {
    this->italic_font = italic;
}

void Line::set_bold_font(bool bold) {
    this->bold_font = bold;
}

void Line::set_underlined_font(bool underlined) {
    this->underlined_font = underlined;
}

void Line::set_crossed_font(bool crossed) {
    this->crossed_font = crossed;
}

void Line::set_font(const std::string &font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void Line::set_font(const std::string &font_name, int font_size, const std::vector<int> &font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
Line::set_font(const std::string &font_name, int font_size, const std::vector<int> &font_color, bool bold_font,
               bool italic_font,
               bool underlined_font, bool crossed_font) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
}

std::vector<int> Line::get_line_color() { //выводит вектор цветов линии rgb
    return this->line_color;
}


std::string Line::get_type_object() {
    return this->type_object;
}

std::string Line::get_text() {
    return this->text;
}

std::string Line::get_help_text() {
    return this->help_text;
}

int Line::get_st_x() { //выводит координату x начала линии
    return this->start_x;
}

int Line::get_st_y() {  //выводит координату y начала линии
    return this->start_y;
}

int Line::get_end_x() {  //выводит координату x конца линии
    return this->end_x;
}

int Line::get_end_y() {  //выводит координату y конца линии
    return this->end_y;
}

int Line::get_center_cord_x() {  //возвращает x-координату центра
    return this->center_x;
}

int Line::get_center_cord_y() {  //возвращает y-координату центра
    return this->center_y;
}

int Line::get_font_size() {
    return this->font_size;
}

std::string Line::get_font_name() {
    return this->font_name;
}

bool Line::get_bold_font() {
    return this->bold_font;
}

bool Line::get_italic_font() {
    return this->italic_font;
}

bool Line::get_crossed_font() {
    return this->crossed_font;
}

bool Line::get_underlined_font() {
    return this->underlined_font;
}


std::vector<int> Line::get_font_color() {
    return this->font_color;
}

void Line::show_help() {
    this->bool_show_help = true;
}

void Line::show() {
    this->bool_show = true;
}

void Line::hide_help() {
    this->bool_show_help = false;
}

void Line::hide() {
    this->bool_show = false;
}

Rectangle::Rectangle(int x, int y, int width, int height) {
    change_center_cords(x, y, width, height);
}

//меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
void Rectangle::change_center_cords(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

void Rectangle::set_angle(int angl) {
    this->angle = angl;
}

void Rectangle::set_line_width(int width) {
    this->line_width = width;
}

void Rectangle::set_line_color(const std::vector<int> &ln_col) {
    this->line_color = ln_col;
}

void Rectangle::set_filling_color(const std::vector<int> &fil_col) {
    this->filling_color = fil_col;
}

void Rectangle::set_help_text(const std::string &help) {
    this->help_text = help;
}

void Rectangle::set_style_frame(int st_frame) {
    if (st_frame >= 0 && st_frame < this->style_frame_list.size()) {
        this->style_frame = st_frame;
    }
}

void Rectangle::set_style_gradient_filling(int st_gradient) {
    if (st_gradient >= 0 && st_gradient < this->style_gradient_list.size()) {
        this->style_gradient_filling = st_gradient;
    }
}

void Rectangle::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

std::string Rectangle::get_type_object() {
    return this->type_object;
}

int Rectangle::get_style_frame() {
    return this->style_frame;
}

int Rectangle::get_line_width() {
    return this->line_width;
}

int Rectangle::get_style_line() {
    return this->style_line;
}

int Rectangle::get_style_gradient_filling() {
    return this->style_gradient_filling;
}

int Rectangle::get_angle() {
    return this->angle;
}

int Rectangle::get_x() {
    return this->x;
}

int Rectangle::get_y() {
    return this->y;
}

int Rectangle::get_width() {
    return this->width;
}

int Rectangle::get_height() {
    return this->height;
}

int Rectangle::get_center_x() {
    return this->center_x;
}

int Rectangle::get_center_y() {
    return this->center_y;
}

std::vector<int> Rectangle::get_line_color() {
    return this->line_color;
}

std::vector<int> Rectangle::get_filling_color() {
    return this->filling_color;
}

void Rectangle::show() {
    this->bool_show = true;
}

void Rectangle::show_help() {
    this->bool_show_help = true;
}

void Rectangle::show_filling() {
    this->bool_show_filling = true;
}

void Rectangle::hide() {
    this->bool_show = false;
}

void Rectangle::hide_help() {
    this->bool_show_help = false;
}

void Rectangle::hide_filling() {
    this->bool_show_filling = false;
}

Ellipse::Ellipse() {}

Ellipse::Ellipse(int x, int y, int width, int height) {
    change_center_cords(x, y, width, height);
}

void
Ellipse::change_center_cords(int x, int y, int width,
                             int height) { //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}

void Ellipse::set_angle(int angl) {
    this->angle = angl;
}

void Ellipse::set_line_width(int line_width) {
    this->line_width = line_width;
}

void Ellipse::set_help_text(const std::string &text) {
    this->help_text = text;
}

void Ellipse::set_line_color(const std::vector<int> &ln_col) {
    this->line_color = ln_col;
}

void Ellipse::set_filling_color(const std::vector<int> &fil_col) {
    this->filling_color = fil_col;
}


void Ellipse::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

std::string Ellipse::get_type_object() {
    return this->type_object;
}

std::string Ellipse::get_help_text() {
    return this->help_text;
}

int Ellipse::get_style_line() {
    return this->style_line;
}

int Ellipse::get_line_width() {
    return this->line_width;
}


int Ellipse::get_angle() {
    return this->angle;
}

int Ellipse::get_x() {
    return this->x;
}

int Ellipse::get_y() {
    return this->y;
}

int Ellipse::get_width() {
    return this->width;
}

int Ellipse::get_height() {
    return this->height;
}

int Ellipse::get_center_x() {
    return this->center_x;
}

int Ellipse::get_center_y() {
    return this->center_y;
}

std::vector<int> Ellipse::get_line_color() {
    return this->line_color;
}

std::vector<int> Ellipse::get_filling_color() {
    return this->filling_color;
}

void Ellipse::show() {
    this->bool_show = true;
}

void Ellipse::show_help() {
    this->bool_show_help = true;
}

void Ellipse::show_filling() {
    this->bool_show_filling = true;
}

void Ellipse::hide() {
    this->bool_show = false;
}

void Ellipse::hide_help() {
    this->bool_show_help = false;
}

void Ellipse::hide_filling() {
    this->bool_show_filling = false;
}

Arc::Arc(int x, int y, int width, int height, int st_angle, int end_angle) : Ellipse::Ellipse() {
    this->type_object = "Дуга";
    this->start_angle = st_angle;
    this->end_angle = end_angle;
    change_center_cords(x, y, width, height);
}

void Arc::set_arc_angles(int start_angle, int end_angle) {
    this->start_angle = start_angle;
    this->end_angle = end_angle;
}

void Arc::set_start_angle(int st_angle) {
    this->start_angle = st_angle;
}

void Arc::set_end_angle(int end_angle) {
    this->end_angle = end_angle;
}

int Arc::get_start_angle() {
    return this->start_angle;
}

int Arc::get_end_angle() {
    return this->end_angle;
}

std::vector<int> Arc::get_arc_angles() {
    return {this->start_angle, this->end_angle};
}

CrookedLine::CrookedLine() {}

CrookedLine::CrookedLine(const std::vector<std::vector<int>> &points_vector) {
    change_center_cords(points_vector);
}

void
CrookedLine::change_center_cords(
        const std::vector<std::vector<int>> &points_vector) { //меняет координаты начала, конца, центра многоугольника. Эта функция нужня для изменения размеров.
    this->points = points_vector;
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

void CrookedLine::set_angle(int angl) {
    this->angle = angl;
}

void CrookedLine::set_line_color(const std::vector<int> &ln_col) {
    this->line_color = ln_col;
}

void CrookedLine::set_filling_color(const std::vector<int> &fil_col) {
    this->filling_color = fil_col;
}

void CrookedLine::set_help_text(const std::string &text) {
    this->help_text = text;
}


void CrookedLine::set_style_line(int st_line) {
    if (st_line >= 0 && st_line < this->style_line_list.size()) {
        this->style_line = st_line;
    }
}

std::string CrookedLine::get_type_object() {
    return this->type_object;
}

int CrookedLine::get_style_line() {
    return this->style_line;
}

int CrookedLine::get_angle() {
    return this->angle;
}

int CrookedLine::get_x() {
    return this->x;
}

int CrookedLine::get_y() {
    return this->y;
}

int CrookedLine::get_width() {
    return this->width;
}

int CrookedLine::get_height() {
    return this->height;
}

int CrookedLine::get_center_x() {
    return this->center_x;
}

int CrookedLine::get_center_y() {
    return this->center_y;
}

std::string CrookedLine::get_help_text() {
    return this->help_text;
}

int CrookedLine::get_line_width() {
    return this->line_width;
}

std::vector<int> CrookedLine::get_line_color() {
    return this->line_color;
}

std::vector<int> CrookedLine::get_filling_color() {
    return this->filling_color;
}

void CrookedLine::show() {
    this->bool_show = true;
}

void CrookedLine::show_help() {
    this->bool_show_help = true;
}

void CrookedLine::show_filling() {
    this->bool_show_filling = true;
}

void CrookedLine::hide() {
    this->bool_show = false;
}

void CrookedLine::hide_help() {
    this->bool_show_help = false;
}

void CrookedLine::hide_filling() {
    this->bool_show_filling = false;
}

Polygon::Polygon(const std::vector<std::vector<int>> &points_vector, bool end_polygon) : CrookedLine::CrookedLine() {
    this->type_object = "Полигон";
    this->end_polygone = end_polygon;
    change_center_cords(points_vector);
}

bool Polygon::get_end_polygon() {
    return this->end_polygone;
}

void Polygon::set_end_polygon(bool end_pol) {
    this->end_polygone = end_pol;
}

TransitionPoint::TransitionPoint() {}

TransitionPoint::TransitionPoint(int number, int x, int y, int width,
                                 int height) { // получает номер точки перехода, координаты, ширина, высота
    this->number_of_transition_point = number;
    change_center_cords(x, y, width, height);
}

void
TransitionPoint::change_center_cords(int x, int y, int width,
                                     int height) { //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}


void TransitionPoint::set_filling_color(const std::vector<int> &fil_col) {
    this->filling_color = fil_col;
}

void TransitionPoint::set_help_text(const std::string &help_text) {
    this->help_text = help_text;
}

void TransitionPoint::set_number(int num) {
    this->number_of_transition_point = num;
}

std::string TransitionPoint::get_type_object() {
    return this->type_object;
}

std::string TransitionPoint::get_help_text() {
    return this->help_text;
}

int TransitionPoint::get_number() {
    return this->number_of_transition_point;
}

int TransitionPoint::get_x() {
    return this->x;
}

int TransitionPoint::get_y() {
    return this->y;
}

int TransitionPoint::get_width() {
    return this->width;
}

int TransitionPoint::get_height() {
    return this->height;
}

int TransitionPoint::get_center_x() {
    return this->center_x;
}

int TransitionPoint::get_center_y() {
    return this->center_y;
}


std::vector<int> TransitionPoint::get_filling_color() {
    return this->filling_color;
}

void TransitionPoint::show() {
    this->bool_show = true;
}

void TransitionPoint::show_help() {
    this->bool_show_help = true;
}

void TransitionPoint::show_filling() {
    this->bool_show_filling = true;
}

void TransitionPoint::hide() {
    this->bool_show = false;
}

void TransitionPoint::hide_help() {
    this->bool_show_help = false;
}

void TransitionPoint::hide_filling() {
    this->bool_show_filling = false;
}

TransitionButton::TransitionButton(int number, int x, int y, int width, int height)
        : TransitionPoint::TransitionPoint() {
    this->number_of_transition_button = number;
    this->type_object = "Точка перехода";
    int number_transition_point = 0; //служебная переменная
    change_center_cords(x, y, width, height);
}


void TransitionButton::set_angle(int angl) {
    this->angle = angl;
}

void TransitionButton::set_italic_font(bool italic) {
    this->italic_font = italic;
}

void TransitionButton::set_bold_font(bool bold) {
    this->bold_font = bold;
}

void TransitionButton::set_underlined_font(bool underlined) {
    this->underlined_font = underlined;
}

void TransitionButton::set_crossed_font(bool crossed) {
    this->crossed_font = crossed;
}

void TransitionButton::set_font(const std::string &font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void TransitionButton::set_font(const std::string &font_name, int font_size, const std::vector<int> &font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
TransitionButton::set_font(const std::string &font_name, int font_size, const std::vector<int> &font_color,
                           bool bold_font, bool italic_font,
                           bool underlined_font, bool crossed_font) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
}


void TransitionButton::set_auto_size_text(bool auto_size) {
    this->auto_size_text = auto_size;
}

void TransitionButton::set_text(const std::string &text) {
    this->text = text;
}

void TransitionButton::set_font_name(const std::string &font_name) {
    this->font_name = font_name;
}

void TransitionButton::set_font_size(int font_size) {
    this->font_size = font_size;
}

void TransitionButton::set_hAlignment(int hAlignment) {
    if (hAlignment >= 0 && hAlignment <= 3) {
        this->hAlignment = hAlignment;
    }
}

void TransitionButton::set_vAlignment(int vAlignment) {
    if (vAlignment >= 0 && vAlignment <= 3) {
        this->vAlignment = vAlignment;
    }
}

void TransitionButton::set_Alignment(const std::vector<int> &al) {
    if (al[0] >= 0 && al[0] <= 3 && al[1] >= 0 && al[1] <= 3) {
        this->hAlignment = al[0];
        this->vAlignment = al[1];
    }
}

void TransitionButton::set_number(int num) {
    this->number_of_transition_button = num;
}

void TransitionButton::set_font_color(const std::vector<int> &fn_col) {
    this->font_color = fn_col;
}


int TransitionButton::get_angle() {
    return this->angle;
}


int TransitionButton::get_font_size() {
    return this->font_size;
}

int TransitionButton::get_number() {
    return this->number_of_transition_button;
}

bool TransitionButton::get_bold_font() {
    return this->bold_font;
}

bool TransitionButton::get_italic_font() {
    return this->italic_font;
}

bool TransitionButton::get_crossed_font() {
    return this->crossed_font;
}

bool TransitionButton::get_underlined_font() {
    return this->underlined_font;
}

bool TransitionButton::get_auto_size_text() {
    return this->auto_size_text;
}


std::string TransitionButton::get_text() {
    return this->text;
}

std::string TransitionButton::get_font_name() {
    return this->font_name;
}

std::vector<int> TransitionButton::get_font_color() {
    return this->font_color;
}


std::string TransitionButton::get_hAlignment() {
    return this->hAlignment_list[this->hAlignment];
}

std::string TransitionButton::get_vAlignment() {
    return this->vAlignment_list[this->vAlignment];
}

std::vector<std::string> TransitionButton::get_alignment() {
    return {this->hAlignment_list[this->hAlignment], this->vAlignment_list[this->vAlignment]};
}


Text::Text(int x, int y, int width, int height) {
    Text::change_center_cords(x, y, width, height);
}

void
Text::change_center_cords(int x, int y, int width,
                          int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->center_x = this->x + floor(this->width / 2);
    this->center_y = this->y + floor(this->height / 2);
}


void Text::set_filling_color(const std::vector<int> &fil_col) {
    this->filling_color = fil_col;
}

void Text::set_help_text(const std::string &help_text) {
    this->help_text = help_text;
}

void Text::set_angle(int angl) {
    this->angle = angl;
}

void Text::set_italic_font(bool italic) {
    this->italic_font = italic;
}

void Text::set_bold_font(bool bold) {
    this->bold_font = bold;
}

void Text::set_underlined_font(bool underlined) {
    this->underlined_font = underlined;
}

void Text::set_crossed_font(bool crossed) {
    this->crossed_font = crossed;
}

void Text::set_font(const std::string &font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void Text::set_font(const std::string &font_name, int font_size, const std::vector<int> &font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
Text::set_font(const std::string &font_name, int font_size, const std::vector<int> &font_color, bool bold_font,
               bool italic_font,
               bool underlined_font, bool crossed_font) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
    this->bold_font = bold_font;
    this->italic_font = italic_font;
    this->underlined_font = underlined_font;
    this->crossed_font = crossed_font;
}


void Text::set_auto_size_text(bool auto_size) {
    this->auto_size_text = auto_size;
}

void Text::set_text(const std::string &text) {
    this->text = text;
}

void Text::set_font_name(const std::string &font_name) {
    this->font_name = font_name;
}

void Text::set_font_size(int font_size) {
    this->font_size = font_size;
}

void Text::set_hAlignment(int hAlignment) {
    if (hAlignment >= 0 && hAlignment <= 3) {
        this->hAlignment = hAlignment;
    }
}

void Text::set_vAlignment(int vAlignment) {
    if (vAlignment >= 0 && vAlignment <= 3) {
        this->vAlignment = vAlignment;
    }
}

void Text::set_Alignment(const std::vector<int> &al) {
    if (al[0] >= 0 && al[0] <= 3 && al[1] >= 0 && al[1] <= 3) {
        this->hAlignment = al[0];
        this->vAlignment = al[1];
    }
}

void Text::set_font_color(const std::vector<int> &fn_col) {
    this->font_color = fn_col;
}

std::string Text::get_type_object() {
    return this->type_object;
}

std::string Text::get_help_text() {
    return this->help_text;
}

int Text::get_x() {
    return this->x;
}

int Text::get_y() {
    return this->y;
}

int Text::get_width() {
    return this->width;
}

int Text::get_height() {
    return this->height;
}

int Text::get_center_x() {
    return this->center_x;
}

int Text::get_center_y() {
    return this->center_y;
}


std::vector<int> Text::get_filling_color() {
    return this->filling_color;
}

int Text::get_angle() {
    return this->angle;
}


int Text::get_font_size() {
    return this->font_size;
}


bool Text::get_bold_font() {
    return this->bold_font;
}

bool Text::get_italic_font() {
    return this->italic_font;
}

bool Text::get_crossed_font() {
    return this->crossed_font;
}

bool Text::get_underlined_font() {
    return this->underlined_font;
}

bool Text::get_auto_size_text() {
    return this->auto_size_text;
}


std::string Text::get_text() {
    return this->text;
}

std::string Text::get_font_name() {
    return this->font_name;
}

std::vector<int> Text::get_font_color() {
    return this->font_color;
}


std::string Text::get_hAlignment() {
    return this->hAlignment_list[this->hAlignment];
}

std::string Text::get_vAlignment() {
    return this->vAlignment_list[this->vAlignment];
}

std::vector<std::string> Text::get_alignment() {
    return {this->hAlignment_list[this->hAlignment], this->vAlignment_list[this->vAlignment]};
}

void Text::show() {
    this->bool_show = true;
}

void Text::show_help() {
    this->bool_show_help = true;
}

void Text::show_filling() {
    this->bool_show_filling = true;
}

void Text::hide() {
    this->bool_show = false;
}

void Text::hide_help() {
    this->bool_show_help = false;
}

void Text::hide_filling() {
    this->bool_show_filling = false;
}
