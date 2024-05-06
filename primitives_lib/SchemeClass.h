#pragma once

#include "FiguresClasses.h"

class Scheme {
public:

    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    struct SchemeParams {
        int width{0};
        int height{0};
        int version{0};
        int scale{1};
        int scale_in_ARM{1};
        int fonts_amount{0};
        int objects_amount{0};
        int groups_amount{0};

        Color bgColor;
        Color setColor;

        std::string name_scheme = std::string();    // Конструктор пустой строки ("")
        std::string file_path = std::string();
        std::string name_bd = std::string();
        std::string server = std::string();

        std::vector<FiguresClasses::Primitive *> objects_vector;
        FiguresClasses::Set set_object;
    };

private:

    SchemeParams actual_params;

public:
    // Конструктор пустой схемы
    Scheme() = default;

    // Конструктор схемы с заданными параметрами
    Scheme(const SchemeParams &input_params) {
        actual_params = input_params;
        actual_params.set_object = FiguresClasses::Set(1, 1, 1, 128, 128, 64, 64, 16, 16, 1,
                                                       {actual_params.setColor.red, actual_params.setColor.green,
                                                        actual_params.setColor.blue});
    }

    ~Scheme();

    void set_width(int width);

    void set_height(int height);

    void set_version(int version);

    void set_scale(int scale);

    void set_scale_in_ARM(int scale_in_ARM);

    void set_fonts_number(int fonts_numbers);

    void set_objects_number(int objects_number);

    void set_groups_number(int groups_number);

    void set_name_scheme(const std::string &name);

    void set_file_path(const std::string &file_path);

    void set_bd_name(const std::string &bd);

    void set_server(const std::string &server);

    int get_width();

    int get_height();

    int get_version();

    int get_scale();

    int get_scale_in_ARM();

    int get_fonts_number();

    int get_objects_number();

    int get_groups_number();

    std::string get_name_scheme();

    std::string get_file_path();

    std::string get_bd_name();

    std::string get_server();

    void draw_scheme(QPainter &painter);

    void add_object(FiguresClasses::Primitive *add_object);

};

Scheme::~Scheme() {
    for (auto object: actual_params.objects_vector) {
        if (object->get_type_object() == "Библиотечный объект") {
            for (auto pattern : object->get_patterns()){
                for (auto obj_in_pattern : pattern){
                    delete obj_in_pattern;
                }
            }
        }
        delete object;
    }
    actual_params = {};
}

void Scheme::set_width(int input_width) {
    actual_params.width = input_width;
}

void Scheme::set_height(int input_height) {
    actual_params.height = input_height;
}

void Scheme::set_version(int input_version) {
    actual_params.version = input_version;
}

void Scheme::set_scale(int input_scale) {
    actual_params.scale = input_scale;
}

void Scheme::set_scale_in_ARM(int input_scale_in_ARM) {
    actual_params.scale_in_ARM = input_scale_in_ARM;
}

void Scheme::set_fonts_number(int input_fonts_amount) {
    actual_params.fonts_amount = input_fonts_amount;
}

void Scheme::set_objects_number(int input_objects_number) {
    actual_params.objects_amount = input_objects_number;
}

void Scheme::set_groups_number(int input_groups_number) {
    actual_params.groups_amount = input_groups_number;
}

void Scheme::set_name_scheme(const std::string &input_name) {
    actual_params.name_scheme = input_name;
}

void Scheme::set_file_path(const std::string &input_file_path) {
    actual_params.file_path = input_file_path;
}

void Scheme::set_bd_name(const std::string &input_bd) {
    actual_params.name_bd = input_bd;
}

void Scheme::set_server(const std::string &input_server) {
    actual_params.server = input_server;
}

int Scheme::get_width() {
    return actual_params.width;
}

int Scheme::get_height() {
    return actual_params.height;
}

int Scheme::get_version() {
    return actual_params.version;
}

int Scheme::get_scale() {
    return actual_params.scale;
}

int Scheme::get_scale_in_ARM() {
    return actual_params.scale_in_ARM;
}

int Scheme::get_fonts_number() {
    return actual_params.fonts_amount;
}

int Scheme::get_objects_number() {
    return actual_params.objects_amount;
}

int Scheme::get_groups_number() {
    return actual_params.groups_amount;
}

std::string Scheme::get_name_scheme() {
    return actual_params.name_scheme;
}

std::string Scheme::get_file_path() {
    return actual_params.file_path;
}

std::string Scheme::get_bd_name() {
    return actual_params.name_bd;
}

std::string Scheme::get_server() {
    return actual_params.server;
}

void Scheme::draw_scheme(QPainter &painter) {
    actual_params.set_object.draw(painter, actual_params.width, actual_params.height);
    for (auto primitive: actual_params.objects_vector) {
        primitive->draw(painter);
    }
}

void Scheme::add_object(FiguresClasses::Primitive *add_line) {
    actual_params.objects_vector.push_back(add_line);
}
