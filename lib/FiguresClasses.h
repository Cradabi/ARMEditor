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
        Rectangle(int x, int y, int width, int height);

        //меняет координаты начала, конца, центра прямоугольника. Эта функция нужня для изменения размеров.
        void change_center_cords(int x, int y, int width, int height);

        void set_angle(int angl);

        void set_line_width(int width);

        void set_line_color(std::vector<int>& ln_col);

        void set_filling_color(std::vector<int>& fil_col);

        void set_help_text(std::string& help);

        void set_style_frame(int st_frame);

        void set_style_gradient_filling(int st_gradient);

        void set_style_line(int st_line);

        std::string get_type_object();

        int get_style_frame();

        int get_line_width();

        int get_style_line();

        int get_style_gradient_filling();

        int get_angle();

        int get_x();

        int get_y();

        int get_width();

        int get_height();

        int get_center_x();

        int get_center_y();

        std::vector<int> get_line_color();

        std::vector<int> get_filling_color();

        void show();

        void show_help();

        void show_filling();

        void hide();

        void hide_help();

        void hide_filling();
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
        Ellipse();

        Ellipse(int x, int y, int width, int height);

        void
        change_center_cords(int x, int y, int width,
                            int height);

        void set_angle(int angl);

        void set_line_width(int line_width);

        void set_help_text(std::string& text);

        void set_line_color(std::vector<int>& ln_col);

        void set_filling_color(std::vector<int>& fil_col);


        void set_style_line(int st_line);

        std::string get_type_object();

        std::string get_help_text();

        int get_style_line();

        int get_line_width();


        int get_angle();

        int get_x();

        int get_y();

        int get_width();

        int get_height();

        int get_center_x();

        int get_center_y();

        std::vector<int> get_line_color();

        std::vector<int> get_filling_color();

        void show();

        void show_help();

        void show_filling();

        void hide();

        void hide_help();

        void hide_filling();


    };

    class Arc : public Ellipse { //класс дуги, которая наслдуется от эллипса
    private:
        int start_angle = 0;
        int end_angle = 0;

    public:
        Arc(int x, int y, int width, int height, int st_angle, int end_angle);

        void set_arc_angles(int start_angle, int end_angle);

        void set_start_angle(int st_angle);

        void set_end_angle(int end_angle);

        int get_start_angle();

        int get_end_angle();

        std::vector<int> get_arc_angles();

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
        TransitionPoint();

        TransitionPoint(int number, int x, int y, int width,
                        int height);

        void
        change_center_cords(int x, int y, int width,
                            int height);


        void set_filling_color(std::vector<int>& fil_col);

        void set_help_text(std::string& help_text);

        void set_number(int num);

        std::string get_type_object();

        std::string get_help_text();

        int get_number();

        int get_x();

        int get_y();

        int get_width();

        int get_height();

        int get_center_x();

        int get_center_y();


        std::vector<int> get_filling_color();

        void show();

        void show_help();

        void show_filling();

        void hide();

        void hide_help();

        void hide_filling();

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
        TransitionButton(int number, int x, int y, int width, int height);


        void set_angle(int angl);

        void set_italic_font(bool italic);

        void set_bold_font(bool bold);

        void set_underlined_font(bool underlined);

        void set_crossed_font(bool crossed);

        void set_font(std::string& font_name, int font_size);

        void set_font(std::string& font_name, int font_size, std::vector<int>& font_color);

        void
        set_font(std::string& font_name, int font_size, std::vector<int>& font_color, bool bold_font, bool italic_font,
                 bool underlined_font, bool crossed_font);


        void set_auto_size_text(bool auto_size);

        void set_text(std::string& text);

        void set_font_name(std::string& font_name);

        void set_font_size(int font_size);

        void set_hAlignment(int hAlignment);

        void set_vAlignment(int vAlignment);

        void set_Alignment(std::vector<int>& al);

        void set_nuber(int num);

        void set_font_color(std::vector<int>& fn_col);


        int get_angle();


        int get_font_size();

        int get_number();

        bool get_bold_font();

        bool get_italic_font();

        bool get_crossed_font();

        bool get_underlined_font();

        bool get_auto_size_text();


        std::string get_text();

        std::string get_font_name();

        std::vector<int> get_font_color();


        std::string get_hAlignment();

        std::string get_vAlignment();

        std::vector<int> get_alignment();

    };

    class CrookedLine {                             //класс кривой линии
    protected:

        bool bool_show_help = false;                // показывать подсказку
        bool bool_show = true;                      //показывать прямоугольник

        bool bool_show_filling = false;                         //показывать заливку
        std::vector<int> line_color = {0, 0, 0};                //цвет линии
        std::vector<int> filling_color = {255, 255, 255};       //цвет заливки

        std::vector<std::vector <int>> points;

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
        CrookedLine();

        CrookedLine(std::vector<std::vector<int>> points_vector);

        void
        change_center_cords(
                std::vector<std::vector<int>> points_vector);

        void set_angle(int angl);

        void set_line_color(std::vector<int>& ln_col);

        void set_filling_color(std::vector<int>& fil_col);

        void set_help_text(std::string& text);


        void set_style_line(int st_line);

        std::string get_type_object();

        int get_style_line();

        int get_angle();

        int get_x();

        int get_y();

        int get_width();

        int get_height();

        int get_center_x();

        int get_center_y();

        std::string get_help_text();

        int get_line_width();

        std::vector<int> get_line_color();

        std::vector<int> get_filling_color();

        void show();

        void show_help();

        void show_filling();

        void hide();

        void hide_help();

        void hide_filling();

    };

    class Polygon : public CrookedLine { //класс многоугольника
    private:
        bool end_polygone;

    public:
        Polygon(std::vector<std::vector<int>> points_vector, bool end_polygon);

        bool get_end_polygon();

        void set_end_polygon(bool end_pol);


    };

}


