#include <lib/FiguresClasses.cpp>
#include <QApplication>
#include <QWidget>
#include <QPainter>


class Scheme {
public:

#pragma pack(push, 1)
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

        std::vector<FiguresClasses::Line> line_vector;
        std::vector<FiguresClasses::Rectangle> rectangle_vector;
        std::vector<FiguresClasses::Ellipse> ellipse_vector;
        std::vector<FiguresClasses::Arc> arc_vector;
        std::vector<FiguresClasses::Polygon> polygon_vector;
        std::vector<FiguresClasses::CrookedLine> crooked_line_vector;
        std::vector<FiguresClasses::Text> text_vector;
        std::vector<FiguresClasses::Image> image_vector;
        std::vector<FiguresClasses::TransitionPoint> tr_p_vector;
        std::vector<FiguresClasses::TransitionButton> tr_b_vector;
        std::vector<FiguresClasses::Telecontrol> telecontrol_vector;
        std::vector<FiguresClasses::Telemeasure> telemeasure_vector;
        std::vector<FiguresClasses::Telesignalisation> telesignalisation_vector;
    };
#pragma pack(pop)

private:

    SchemeParams actual_params;

    std::vector<Qt::Alignment> v_alignment_vector = {Qt::AlignTop, Qt::AlignVCenter, Qt::AlignBottom};
    std::vector<Qt::Alignment> h_alignment_vector = {Qt::AlignLeft, Qt::AlignHCenter, Qt::AlignRight};
    std::vector<Qt::PenStyle> style_vector = {Qt::NoPen, Qt::SolidLine, Qt::DashLine, Qt::DotLine, Qt::DashDotLine,
                                              Qt::DashDotDotLine, Qt::CustomDashLine};

public:
    // Конструктор пустой схемы
    Scheme() = default;

    // Конструктор схемы с заданными параметрами
    Scheme(const SchemeParams &input_params) {
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

    void draw_line(FiguresClasses::Line &pol, QPainter &painter);

    void draw_rect(FiguresClasses::Rectangle &rect, QPainter &painter);

    void draw_ellipse(FiguresClasses::Ellipse &el, QPainter &painter);

    void draw_arc(FiguresClasses::Arc &arc, QPainter &painter);

    void draw_polygon(FiguresClasses::Polygon &poly, QPainter &painter);

    void draw_crooked_line(FiguresClasses::CrookedLine &crook, QPainter &painter);

    void draw_text(FiguresClasses::Text &text, QPainter &painter);

    void draw_image(FiguresClasses::Image &image, QPainter &painter);

    void draw_transition_point(FiguresClasses::TransitionPoint &tr_p, QPainter &painter);

    void draw_transition_button(FiguresClasses::TransitionButton &tr_b, QPainter &painter);

    void draw_set(QPainter &painter);

    void draw_telecontrol(FiguresClasses::Telecontrol &text, QPainter &painter);

    void draw_telemeasure(FiguresClasses::Telemeasure &text, QPainter &painter);

    void draw_telesignalisation(FiguresClasses::Telesignalisation &text, QPainter &painter);

    void draw_scheme(QPainter &painter);

    void add_object(FiguresClasses::Line &add_line);

    void add_object(FiguresClasses::Rectangle &add_rect);

    void add_object(FiguresClasses::Ellipse &add_el);

    void add_object(FiguresClasses::Arc &add_arc);

    void add_object(FiguresClasses::Polygon &add_poly);

    void add_object(FiguresClasses::CrookedLine &add_crook);

    void add_object(FiguresClasses::Text &add_text);

    void add_object(FiguresClasses::Image &add_image);

    void add_object(FiguresClasses::TransitionPoint &add_tr_p);

    void add_object(FiguresClasses::TransitionButton &add_tr_b);

    void add_object(FiguresClasses::Telecontrol &add_telec);

    void add_object(FiguresClasses::Telemeasure &add_telem);

    void add_object(FiguresClasses::Telesignalisation &add_teles);
};
