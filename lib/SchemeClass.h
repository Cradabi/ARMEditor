#include <lib/FiguresClasses.cpp>
#include <QApplication>
#include <QWidget>
#include <QPainter>


class Scheme{
private:
    int width = 0;
    int height = 0;
    int version = 0;
    int scale = 1;
    int scale_in_ARM = 1;
    int fonts_number = 0;
    int objects_number = 0;
    int groups_number = 0;

    std::string name_scheme = "";
    std::string file_path = "";
    std::string bd_name = "";
    std::string server = "";

    std::vector <FiguresClasses::Line> line_vector;
    std::vector <FiguresClasses::Rectangle> rectangle_vector;
    std::vector <FiguresClasses::Ellipse> ellipse_vector;
    std::vector <FiguresClasses::Arc> arc_vector;
    std::vector <FiguresClasses::Polygon> polygon_vector;
    std::vector <FiguresClasses::CrookedLine> crooked_line_vector;
    std::vector <FiguresClasses::Text> text_vector;
    std::vector <FiguresClasses::Image> image_vector;
    std::vector <FiguresClasses::TransitionPoint> tr_p_vector;
    std::vector <FiguresClasses::TransitionButton> tr_b_vector;
    std::vector <FiguresClasses::Telecontrol> telecontrol_vector;
    std::vector <FiguresClasses::Telemeasure> telemeasure_vector;
    std::vector <FiguresClasses::Telesignalisation> telesignalisation_vector;
    std::vector <Qt::Alignment> v_alignment_vector = {Qt::AlignTop, Qt::AlignVCenter, Qt::AlignBottom};
    std::vector <Qt::Alignment> h_alignment_vector = {Qt::AlignLeft, Qt::AlignHCenter, Qt::AlignRight};
    std::vector <Qt::PenStyle> style_vector = {Qt::NoPen, Qt::SolidLine, Qt::DashLine, Qt::DotLine, Qt::DashDotLine, Qt::DashDotDotLine, Qt::CustomDashLine};

public:
    Scheme(int _width, int _height, const std::string& _name, const std::string& file_path, const std::string& bd, const std::string& server, int version, int scale, int scale_in_ARM, int fonts_number, int objects_number, int group_number,  const std::vector <FiguresClasses::Line>& _line, const std::vector <FiguresClasses::Rectangle>& _rect, const std::vector <FiguresClasses::Ellipse>& _el, const std::vector <FiguresClasses::Arc>& _arc, const std::vector <FiguresClasses::Polygon>& _poly, const std::vector <FiguresClasses::CrookedLine>& _crook, const std::vector <FiguresClasses::Text>& _text, const std::vector <FiguresClasses::Image>& _image, const std::vector <FiguresClasses::TransitionPoint>& _tr_p, const std::vector <FiguresClasses::TransitionButton>& _tr_b, const std::vector <FiguresClasses::Telecontrol>& _telec, const std::vector <FiguresClasses::Telemeasure>& _telem, const std::vector <FiguresClasses::Telesignalisation>& _teles);

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
};
