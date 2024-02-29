#include "lib/FiguresClasses.cpp"
#include <QApplication>

#pragma once

class Scheme {
public:

    struct SchemeParams {
        int width{0};
        int height{0};
        int version{0};
        int scale{1};
        int scale_in_ARM{1};
        int fonts_amount{0};
        int objects_amount{0};
        int groups_amount{0};

        std::string name_scheme = std::string();    // Конструктор пустой строки ("")
        std::string file_path = std::string();
        std::string name_bd = std::string();
        std::string server = std::string();

        std::vector<FiguresClasses::Primitive*> objects_vector;
        FiguresClasses::Set set_object = Set(1, 20, 20, 1, {200, 200, 200});
    };

private:

    SchemeParams actual_params;

public:
    // Конструктор пустой схемы
    Scheme() = default;

    // Конструктор схемы с заданными параметрами
    Scheme(const SchemeParams& input_params) {
        actual_params = input_params;
    }

    void set_width(int width);

    void set_height(int height);

    void set_version(int version);

    void set_scale(int scale);

    void set_scale_in_ARM(int scale_in_ARM);

    void set_fonts_number(int fonts_numbers);

    void set_objects_number(int objects_number);

    void set_groups_number(int groups_number);

    void set_name_scheme(const std::string& name);

    void set_file_path(const std::string& file_path);

    void set_bd_name(const std::string& bd);

    void set_server(const std::string& server);

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

    void draw_scheme(QPainter& painter);

    void add_object(FiguresClasses::Primitive* add_object);

};
