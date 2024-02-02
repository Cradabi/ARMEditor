#include <iostream>
#include <vector>
#include <cmath>

namespace FiguresClasses {

    class Line { // класс линии
    private:
        bool bool_show_help = false;             //флаг показывания подсказки
        bool bool_show = true;                   //флаг показывания линии
        bool bold_font = false;                  //флаг жирности шрифта
        bool italic_font = false;                //флаг наклонности шрифта
        bool underlined_font = false;            //флаг подчеркнутости шрифта
        bool crossed_font = false;               //флаг зачеркнутости шрифта

        std::vector<std::string> style_arrow_list =
                {"esNone", "esRoundArrow", "esSharpArrow", "esDot",
                 "esRightArrow"};         //список названий типов стрелок
        std::vector<std::string> style_line_list =
                {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6", "psDash1",
                 "psDash2"};                                                                  //список названий стилей линий

        std::string type_object = "Линия";
        std::string text = "";              //текст на линии
        std::string help_text = "";         //подсказка к линии
        std::string font_name = "";         //имя шрифта

        int start_x = 0;
        int start_y = 0;
        int end_x = 0;
        int end_y = 0;
        int center_x = 0;
        int center_y = 0;

        int font_size = 14;     //размер шрифта
        int number_of_text = 0; //количество текстовых вставок
        int style_line = 1;     //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"

        int line_width = 2;

        int start_style_arrow = 0; //тип начала линии 0-"esNone", 1-"esRoundArrow", 2-"esSharpArrow", 3-"esDot", 4-"esRightArrow"
        int end_style_arrow = 0;   //тип начала линии 0-"esNone", 1-"esRoundArrow", 2-"esSharpArrow", 3-"esDot", 4-"esRightArrow"

        std::vector<int> line_color = {0, 0, 0};
        std::vector<int> font_color = {0, 0, 0};

    public:
        Line(int st_x, int st_y, int end_x, int end_y);

        //меняет координаты начала, конца, центра линии
        void change_center_cords(int st_x, int st_y, int end_x,
                                 int end_y);

        //меняет вектор цвета линии
        void set_line_color(std::vector<int>& lin_col);

        void set_text(std::string& text);

        void set_help_text(std::string& help);

        void set_font_name(std::string& fn_name);

        void set_font_size(int fn_size);

        void set_font_color(std::vector<int>& fn_col);

        void set_italic_font(bool italic);

        void set_bold_font(bool bold);

        void set_underlined_font(bool underlined);

        void set_crossed_font(bool crossed);

        void set_font(std::string& font_name, int font_size);

        void set_font(std::string& font_name, int font_size, std::vector<int>& font_color);

        void
        set_font(std::string& font_name, int font_size, std::vector<int>& font_color, bool bold_font, bool italic_font,
                 bool underlined_font, bool crossed_font);

        //выводит вектор цветов линии rgb
        std::vector<int> get_line_color();

        std::string get_type_object();

        std::string get_text();

        std::string get_help_text();

        //выводит координату x начала линии
        int get_st_x();

        //выводит координату y начала линии
        int get_st_y();

        //выводит координату x конца линии
        int get_end_x();

        //выводит координату y конца линии
        int get_end_y();

        //возвращает x-координату центра
        int get_center_cord_x();

        //возвращает y-координату центра
        int get_center_cord_y();

        int get_font_size();

        std::string get_font_name();

        bool get_bold_font();

        bool get_italic_font();

        bool get_crossed_font();

        bool get_underlined_font();

        std::vector<int> get_font_color();

        void show_help();

        void show();

        void hide_help();

        void hide();

    };


    class Rectangle {   //класс прямоугольника
    private:
        bool bool_show_help = false;                        //показывать подсказку
        bool bool_show = true;                              //показывать прямоугольник
        bool bool_show_filling = false;                     //показывать заливку
        std::vector<int> line_color = {0, 0, 0};            //цвет линии
        std::vector<int> filling_color = {255, 255, 255};   //цвет заливки

        std::vector<std::string> style_frame_list =    //список названий стилей линий
                {"fsNull", "fsButtonDown", "fsButtonUp", "fsBagetDown", "fsBagetUp", "fsDoubleDown",
                 "fsDoubleUp"};
        std::vector<std::string> style_gradient_list = //список названий стилей градиентных заливок
                {"stNone", "stHorzPlane", "stVertPlane", "stHorzPipe", "stVertPipe",
                 "stSphere", "stCone", "stBTTrapezoid", "stLRTrapezoid",
                 "stTBTrapezoid"};
        std::vector<std::string> style_line_list =     //список названий стилей линий
                {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6",
                 "psDash1", "psDash2"};

        std::string type_object = "Прямоугольник";
        std::string help_text = "";     //текст подсказки

        int style_frame = 0;            // стиль рамки 0-"fsNull", 1-"fsButtonDown", 2-"fsButtonUp", 3-"fsBagetDown", 4-"fsBagetUp", 5-"fsDoubleDown", 6-"fsDoubleUp"
        int style_gradient_filling = 0; //0-stNone", 1-"stHorzPlane", 2-"stVertPlane", 3-"stHorzPipe", 4-"stVertPipe", 5-"stSphere", 6-"stCone", 7-"stBTTrapezoid", 8-"stLRTrapezoid", 9-"stTBTrapezoid"
        int style_line = 1;             //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"

        int line_width = 2;
        int angle = 0;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        int center_x = 0;
        int center_y = 0;

    public:
        Rectangle(int x, int y, int width, int height) {
            change_center_cords(x, y, width, height);
        }

        //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
        void change_center_cords(int x, int y, int width, int height) {
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

        void set_line_width(int width) {
            this->line_width = width;
        }

        void set_line_color(std::vector<int> ln_col) {
            this->line_color = ln_col;
        }

        void set_filling_color(std::vector<int> fil_col) {
            this->filling_color = fil_col;
        }

        void set_help_text(std::string help) {
            this->help_text = help;
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

        std::string get_type_object() {
            return this->type_object;
        }

        int get_style_frame() {
            return this->style_frame;
        }

        int get_line_width() {
            return this->line_width;
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

        std::vector<int> get_line_color() {
            return this->line_color;
        }

        std::vector<int> get_filling_color() {
            return this->filling_color;
        }

        void show() {
            this->bool_show = true;
        }

        void show_help() {
            this->bool_show_help = true;
        }

        void show_filling() {
            this->bool_show_filling = true;
        }

        void hide() {
            this->bool_show = false;
        }

        void hide_help() {
            this->bool_show_help = false;
        }

        void hide_filling() {
            this->bool_show_filling = false;
        }

    };


    class Ellipse { //класс эллипса
    protected:
        bool bool_show_help = false; // показывать подсказку
        bool bool_show = true; //показывать эллипс
        bool bool_show_filling = false; //показывать заливку
        std::vector<int> line_color = {0, 0, 0}; //цвет линии
        std::vector<int> filling_color = {255, 255, 255}; //цвет заливки
        std::vector<std::string> style_line_list = {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4",
                                                    "psDot5",
                                                    "psDot6",
                                                    "psDash1", "psDash2"}; //список названий стилей линий
        std::string type_object = "Эллипс";
        std::string help_text = ""; //текст подсказки
        int style_line = 1;  //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"
        int line_width = 2;
        int angle = 0;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        int center_x = 0;
        int center_y = 0;


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

        void set_line_width(int line_width) {
            this->line_width = line_width;
        }

        void set_help_text(std::string text) {
            this->help_text = text;
        }

        void set_line_color(std::vector<int> ln_col) {
            this->line_color = ln_col;
        }

        void set_filling_color(std::vector<int> fil_col) {
            this->filling_color = fil_col;
        }


        void set_style_line(int st_line) {
            if (st_line >= 0 && st_line < this->style_line_list.size()) {
                this->style_line = st_line;
            }
        }

        std::string get_type_object() {
            return this->type_object;
        }

        std::string get_help_text() {
            return this->help_text;
        }

        int get_style_line() {
            return this->style_line;
        }

        int get_line_width() {
            return this->line_width;
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

        std::vector<int> get_line_color() {
            return this->line_color;
        }

        std::vector<int> get_filling_color() {
            return this->filling_color;
        }

        void show() {
            this->bool_show = true;
        }

        void show_help() {
            this->bool_show_help = true;
        }

        void show_filling() {
            this->bool_show_filling = true;
        }

        void hide() {
            this->bool_show = false;
        }

        void hide_help() {
            this->bool_show_help = false;
        }

        void hide_filling() {
            this->bool_show_filling = false;
        }


    };

    class Arc : public Ellipse { //класс дуги, которая наслдуется от эллипса
    private:
        int start_angle = 0;
        int end_angle = 0;

    public:
        Arc(int x, int y, int width, int height, int st_angle, int end_angle) : Ellipse() {
            this->type_object = "Дуга";
            this->start_angle = st_angle;
            this->end_angle = end_angle;
            change_center_cords(x, y, width, height);
        }

        void set_arc_angles(int start_angle, int end_angle) {
            this->start_angle = start_angle;
            this->end_angle = end_angle;
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

        std::vector<int> get_arc_angles() {
            return {this->start_angle, this->end_angle};
        }

    };


    class TransitionPoint { //класс точки перехода
    private:
        int number_of_transition_point = 0; // номер точки перехода

    protected:
        bool bool_show_help = false;        // показывать подсказку
        bool bool_show = true;              //показывать прямоугольник
        bool bool_show_filling = false;     //показывать заливку

        std::vector<int> filling_color = {255, 255, 255}; //цвет заливки
        std::string type_object = "Точка перехода";
        std::string help_text = "";                       //текст подсказки

        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        int center_x = 0;
        int center_y = 0;

    public:
        TransitionPoint() {}

        TransitionPoint(int number, int x, int y, int width,
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


        void set_filling_color(std::vector<int> fil_col) {
            this->filling_color = fil_col;
        }

        void set_help_text(std::string help_text) {
            this->help_text = help_text;
        }

        void set_number(int num) {
            this->number_of_transition_point = num;
        }

        std::string get_type_object() {
            return this->type_object;
        }

        std::string get_help_text() {
            return this->help_text;
        }

        int get_number() {
            return this->number_of_transition_point;
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


        std::vector<int> get_filling_color() {
            return this->filling_color;
        }

        void show() {
            this->bool_show = true;
        }

        void show_help() {
            this->bool_show_help = true;
        }

        void show_filling() {
            this->bool_show_filling = true;
        }

        void hide() {
            this->bool_show = false;
        }

        void hide_help() {
            this->bool_show_help = false;
        }

        void hide_filling() {
            this->bool_show_filling = false;
        }

    };


    class TransitionButton : TransitionPoint {      //класс кнопка перехода
    private:
        bool bold_font = false;                     //флаг жирности шрифта
        bool italic_font = false;                   //флаг наклонности шрифта
        bool underlined_font = false;               //флаг подчеркнутости шрифта
        bool crossed_font = false;                  //флаг зачеркнутости шрифта
        bool auto_size_text = false;                //авторазмер текста
        std::vector<int> font_color = {0, 0, 0};    //цвет шрифта

        std::vector<std::string> hAlignment_list = {"ahLeft", "ahRight", "ahCenter"};
        std::vector<std::string> vAlignment_list = {"avTop", "avBottom", "avCenter"};

        std::string text = "";                      //текст кнопки
        std::string font_name = "Arial";

        int hAlignment = 2;
        int vAlignment = 2;
        int font_size = 14;
        int number_of_transition_button = 0;
        int angle = 0;


    public:
        TransitionButton(int number, int x, int y, int width, int height) : TransitionPoint() {
            this->number_of_transition_button = number;
            this->type_object = "Точка перехода";
            int number_transition_point = 0; //служебная переменная
            change_center_cords(x, y, width, height);
        }


        void set_angle(int angl) {
            this->angle = angl;
        }

        void set_italic_font(bool italic) {
            this->italic_font = italic;
        }

        void set_bold_font(bool bold) {
            this->bold_font = bold;
        }

        void set_underlined_font(bool underlined) {
            this->underlined_font = underlined;
        }

        void set_crossed_font(bool crossed) {
            this->crossed_font = crossed;
        }

        void set_font(std::string font_name, int font_size) {
            this->font_name = font_name;
            this->font_size = font_size;
        }

        void set_font(std::string font_name, int font_size, std::vector<int> font_color) {
            this->font_name = font_name;
            this->font_size = font_size;
            this->font_color = font_color;
        }

        void
        set_font(std::string font_name, int font_size, std::vector<int> font_color, bool bold_font, bool italic_font,
                 bool underlined_font, bool crossed_font) {
            this->font_name = font_name;
            this->font_size = font_size;
            this->font_color = font_color;
            this->bold_font = bold_font;
            this->italic_font = italic_font;
            this->underlined_font = underlined_font;
            this->crossed_font = crossed_font;
        }


        void set_auto_size_text(bool auto_size) {
            this->auto_size_text = auto_size;
        }

        void set_text(std::string text) {
            this->text = text;
        }

        void set_font_name(std::string font_name) {
            this->font_name = font_name;
        }

        void set_font_size(int font_size) {
            this->font_size = font_size;
        }

        void set_hAlignment(int hAlignment) {
            if (hAlignment >= 0 && hAlignment <= 3) {
                this->hAlignment = hAlignment;
            }
        }

        void set_vAlignment(int vAlignment) {
            if (vAlignment >= 0 && vAlignment <= 3) {
                this->vAlignment = vAlignment;
            }
        }

        void set_Alignment(std::vector<int> al) {
            if (al[0] >= 0 && al[0] <= 3 && al[1] >= 0 && al[1] <= 3) {
                this->hAlignment = al[0];
                this->vAlignment = al[1];
            }
        }

        void set_nuber(int num) {
            this->number_of_transition_button = num;
        }

        void set_font_color(std::vector<int> fn_col) {
            this->font_color = fn_col;
        }


        int get_angle() {
            return this->angle;
        }


        int get_font_size() {
            return this->font_size;
        }

        int get_number() {
            return this->number_of_transition_button;
        }

        bool get_bold_font() {
            return this->bold_font;
        }

        bool get_italic_font() {
            return this->italic_font;
        }

        bool get_crossed_font() {
            return this->crossed_font;
        }

        bool get_underlined_font() {
            return this->underlined_font;
        }

        bool get_auto_size_text() {
            return this->auto_size_text;
        }


        std::string get_text() {
            return this->text;
        }

        std::string get_font_name() {
            return this->font_name;
        }

        std::vector<int> get_font_color() {
            return this->font_color;
        }


        std::string get_hAlignment() {
            return this->hAlignment_list[this->hAlignment];
        }

        std::string get_vAlignment() {
            return this->vAlignment_list[this->vAlignment];
        }

        std::vector<int> get_alignment() {
            return {this->hAlignment, this->vAlignment};
        }

    };

    class CrookedLine {                             //класс кривой линии
    protected:

        bool bool_show_help = false;                // показывать подсказку
        bool bool_show = true;                      //показывать прямоугольник

        bool bool_show_filling = false;                         //показывать заливку
        std::vector<int> line_color = {0, 0, 0};                //цвет линии
        std::vector<int> filling_color = {255, 255, 255};       //цвет заливки

        std::vector<std::string> style_line_list =
                {"psNull", "psSolid", "psDot1", "psDot2", "psDot3", "psDot4", "psDot5", "psDot6",
                 "psDash1", "psDash2"};         //список названий стилей линий

        std::string type_object = "Кривая линия";
        std::string help_text = "";             //текст подсказки
        int style_line = 1;                     //стиль линии 0-"psNull", 1-"psSolid", 2-"psDot1", 3-"psDot2", 4-"psDot3", 5-"psDot4", 6-"psDot5", 7-"psDot6", 8-"psDash1", 9-"psDash2"

        int line_width = 2;
        int angle = 0;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        int center_x = 0;
        int center_y = 0;

    public:
        CrookedLine() {}

        CrookedLine(std::vector<std::vector<int>> points_vector) {
            change_center_cords(points_vector);
        }

        void
        change_center_cords(
                std::vector<std::vector<int>> points_vector) { //меняет координаты начала, конца, центра многоугольника. Эта функция нужня для изменения размеров.
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

        void set_line_color(std::vector<int> ln_col) {
            this->line_color = ln_col;
        }

        void set_filling_color(std::vector<int> fil_col) {
            this->filling_color = fil_col;
        }

        void set_help_text(std::string text) {
            this->help_text = text;
        }


        void set_style_line(int st_line) {
            if (st_line >= 0 && st_line < this->style_line_list.size()) {
                this->style_line = st_line;
            }
        }

        std::string get_type_object() {
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

        std::string get_help_text() {
            return this->help_text;
        }

        int get_line_width() {
            return this->line_width;
        }

        std::vector<int> get_line_color() {
            return this->line_color;
        }

        std::vector<int> get_filling_color() {
            return this->filling_color;
        }

        void show() {
            this->bool_show = true;
        }

        void show_help() {
            this->bool_show_help = true;
        }

        void show_filling() {
            this->bool_show_filling = true;
        }

        void hide() {
            this->bool_show = false;
        }

        void hide_help() {
            this->bool_show_help = false;
        }

        void hide_filling() {
            this->bool_show_filling = false;
        }

    };

    class Polygon : public CrookedLine { //класс многоугольника
    private:
        bool end_polygone;

    public:
        Polygon(std::vector<std::vector<int>> points_vector, bool end_polygon = false) : CrookedLine() {
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


    };

}


