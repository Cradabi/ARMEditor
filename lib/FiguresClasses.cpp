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
void Line::set_line_color(std::vector<int>& lin_col) {
    this->line_color = lin_col;
}

void Line::set_text(std::string& text) {
    this->text = text;
}

void Line::set_help_text(std::string& help) {
    this->help_text = help;
}

void Line::set_font_name(std::string& fn_name) {
    this->font_name = fn_name;
}

void Line::set_font_size(int fn_size) {
    this->font_size = fn_size;
}

void Line::set_font_color(std::vector<int>& fn_col) {
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

void Line::set_font(std::string& font_name, int font_size) {
    this->font_name = font_name;
    this->font_size = font_size;
}

void Line::set_font(std::string& font_name, int font_size, std::vector<int>& font_color) {
    this->font_name = font_name;
    this->font_size = font_size;
    this->font_color = font_color;
}

void
Line::set_font(std::string& font_name, int font_size, std::vector<int>& font_color, bool bold_font, bool italic_font,
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