#include "SchemeObjectParser.h"

void SchemeObjectParser::parseNone(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                   int id_pos) {
    ;
}

void SchemeObjectParser::parseEllips(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                     int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter]);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter]);

    scheme_params.objects_vector.push_back(
            new Ellipse(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                        (360 - (int) angle) % 360,
                        width, line_style,
                        {pen.red, pen.green, pen.blue},
                        " Эллипс ",
                        true,
                        {brush.red, brush.green, brush.blue},
                        brush_style));

}

void
SchemeObjectParser::parseGoBtn(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                               int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    scheme_params.objects_vector.push_back(
            new TransitionButton(0, center_x - half_x, center_y - half_y,
                                 half_x * 2, half_y * 2, angle,
                                 {brush.red, brush.green, brush.blue},
                                 " Кнопка перехода ", true, 1));

}

void
SchemeObjectParser::parseGoPoint(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                 int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);


    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y = 0;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    scheme_params.objects_vector.push_back(
            new TransitionPoint(0, center_x - half_x, center_y - half_y,
                                half_x * 2, half_y * 2,
                                {pen.red, pen.green, pen.blue},
                                " Точка перехода ", true, 0));
}

void
SchemeObjectParser::parseGluePoint(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                   int id_pos) {
    ;
}

void SchemeObjectParser::parseLine(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                   int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter]);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 4;

    int32_t cord_x1;
    getSomeInt(buffer, cord_x1, 4, bytes_counter);

    int32_t cord_y1;
    getSomeInt(buffer, cord_y1, 4, bytes_counter);

    int32_t cord_x2;
    getSomeInt(buffer, cord_x2, 4, bytes_counter);

    int32_t cord_y2;
    getSomeInt(buffer, cord_y2, 4, bytes_counter);

    bytes_counter += 2;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    bytes_counter += 7;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter]);

    bytes_counter += 5;

    uint8_t end_arrow_style = static_cast<uint8_t> (buffer[bytes_counter++]);

    uint8_t start_arrow_style = static_cast<uint8_t> (buffer[bytes_counter]);

    scheme_params.objects_vector.push_back(
            new Line((int) round(center_x + cord_x1), (int) round(center_y + cord_y1),
                     (int) round(center_x + cord_x2), (int) round(center_y + cord_y2), "", "Линия",
                     true,
                     line_style, 0, width, start_arrow_style, end_arrow_style, {pen.red, pen.green, pen.blue}));
}

void SchemeObjectParser::parseText(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                   int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t text_length = 0;
    getSomeInt(buffer, text_length, 4, bytes_counter);

    std::string text;
    for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
        text += buffer[i];
    }
    bytes_counter += text_length;

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(buffer, font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(buffer, font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(buffer, font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 1; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(buffer, font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(buffer, font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(buffer, font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Text((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2, half_y * 2,
                         (360 - (int) angle) % 360,
                         text, " Текст ", line_style,
                         {brush.red, brush.green, brush.blue},
                         1, brush_style, font_name, font_size,
                         {font_color.red, font_color.green, font_color.blue},
                         font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                         font_autosize));
    }
}

void
SchemeObjectParser::parsePolygon(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                 int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter]);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    uint32_t amount_of_dots;
    getSomeInt(buffer, amount_of_dots, 4, bytes_counter);


    bool end_polygon = false;
    std::vector<std::vector<int>> coords;
    for (int32_t i = 0; i < amount_of_dots; ++i) {
        std::vector<int> pair;
        int32_t x;
        getSomeInt(buffer, x, 4, bytes_counter);

        int32_t y;
        getSomeInt(buffer, y, 4, bytes_counter);

        if (i == amount_of_dots - 1 and center_x + x == coords[0][0] and center_y + y == coords[0][1]) {
            end_polygon = true;
        } else {
            std::vector<int> pair_coords;
            coords.push_back(pair_coords);
            coords[i].push_back(center_x + x);
            coords[i].push_back(center_y + y);
        }
    }
    bytes_counter += 2;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t text_length = 0;
    getSomeInt(buffer, text_length, 4, bytes_counter);

    std::string text;
    for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
        text += buffer[i];
    }
    bytes_counter += text_length;

    scheme_params.objects_vector.push_back(
            new Polygon(coords, end_polygon,
                        (360 - (int) angle) % 360,
                        width, line_style, " Прямоугольник ",
                        {pen.red, pen.green, pen.blue},
                        {brush.red, brush.green, brush.blue},
                        true, brush_style));
}

void
SchemeObjectParser::parseRectangle(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                   int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter]);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y = 0;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter]);

    scheme_params.objects_vector.push_back(
            new Rectangle(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                          (360 - (int) angle) % 360,
                          width, line_style,
                          {pen.red, pen.green, pen.blue},
                          " Прямоугольник ", true, 0, 0,
                          {brush.red, brush.green, brush.blue},
                          brush_style));

}

void SchemeObjectParser::parseArc(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                  int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter]);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 16;

    uint32_t half_y;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    uint32_t start_angle;
    getSomeInt(buffer, start_angle, 4, bytes_counter);

    uint32_t end_angle;
    getSomeInt(buffer, end_angle, 4, bytes_counter);

    bytes_counter += 2;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter]);

    scheme_params.objects_vector.push_back(
            new Arc(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                    (360 - (int) angle) % 360, start_angle, end_angle,
                    width, line_style,
                    {pen.red, pen.green, pen.blue},
                    " Дуга ",
                    true,
                    {brush.red, brush.green, brush.blue},
                    brush_style));
}

void
SchemeObjectParser::parseTelecontrol(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                     int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);


    bytes_counter += 8;

    uint32_t half_y = 0;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t text_length = 0;
    getSomeInt(buffer, text_length, 4, bytes_counter);


    std::string text;
    for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
        text += buffer[i];
    }
    bytes_counter += text_length;

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(buffer, font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(buffer, font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(buffer, font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 2; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(buffer, font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(buffer, font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(buffer, font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Telecontrol((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                half_y * 2,
                                (360 - (int) angle) % 360,
                                text, " Телеуправление ", line_style,
                                {brush.red, brush.green, brush.blue},
                                1, brush_style, font_name, font_size,
                                {font_color.red, font_color.green, font_color.blue},
                                font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                font_autosize));
    }

}

void
SchemeObjectParser::parseTelemeasure(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                     int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);


    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y = 0;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t text_length = 0;
    getSomeInt(buffer, text_length, 4, bytes_counter);

    std::string text;
    for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
        text += buffer[i];
    }
    bytes_counter += text_length;

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(buffer, font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(buffer, font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(buffer, font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 2; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(buffer, font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(buffer, font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(buffer, font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Telemeasure((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                half_y * 2,
                                (360 - (int) angle) % 360,
                                text, " Телеизмерение ", line_style,
                                {brush.red, brush.green, brush.blue},
                                1, brush_style, font_name, font_size,
                                {font_color.red, font_color.green, font_color.blue},
                                font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                font_autosize));
    }
}

void
SchemeObjectParser::parseSignal(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);


    bytes_counter += 8;

    uint32_t half_y = 0;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t text_length = 0;
    getSomeInt(buffer, text_length, 4, bytes_counter);

    std::string text;
    for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
        text += buffer[i];
    }
    bytes_counter += text_length;

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(buffer, font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(buffer, font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(buffer, font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 2; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(buffer, font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(buffer, font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(buffer, font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Telesignalisation((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                      half_y * 2,
                                      (360 - (int) angle) % 360,
                                      text, " Телесигнализация ", line_style,
                                      {brush.red, brush.green, brush.blue},
                                      1, brush_style, font_name, font_size,
                                      {font_color.red, font_color.green, font_color.blue},
                                      font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                      font_autosize));
    }
}

void
SchemeObjectParser::parsePicture(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                                 int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x;
    getSomeFloat(buffer, center_x, 8, bytes_counter);

    bytes_counter += 16;

    double center_y;
    getSomeFloat(buffer, center_y, 8, bytes_counter);

    bytes_counter += 24;

    double angle;
    getSomeFloat(buffer, angle, 8, bytes_counter);

    bytes_counter += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter]);

    bytes_counter = id_pos + 4;

    uint32_t id = 0;
    getSomeInt(buffer, id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x = 0;
    getSomeInt(buffer, half_x, 4, bytes_counter);


    bytes_counter += 8;

    uint32_t half_y = 0;
    getSomeInt(buffer, half_y, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen;
    getColor(buffer, pen, bytes_counter);

    ssp::BGRColor brush;
    getColor(buffer, brush, bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t text_length = 0;
    getSomeInt(buffer, text_length, 4, bytes_counter);

    std::string text;
    for (int i = bytes_counter; i < text_length + bytes_counter; ++i) {
        text += buffer[i];
    }
    bytes_counter += text_length;

    bytes_counter += 89;

    uint8_t not_scale;
    not_scale = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t is_picture;
    is_picture = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t width_of_picture;
    getSomeInt(buffer, width_of_picture, 4, bytes_counter);

    uint32_t height_of_picture;
    getSomeInt(buffer, height_of_picture, 4, bytes_counter);

    uint8_t bit_depth;
    bit_depth = static_cast<uint8_t>(buffer[bytes_counter++]);

    std::vector<std::vector<ssp::BGRColor>> bitmap;
    for (uint32_t x = 0; x < width_of_picture; ++x) {
        std::vector<ssp::BGRColor> pixel_line;
        bitmap.push_back(pixel_line);
        for (uint32_t y = 0; y < height_of_picture; ++y) {
            ssp::BGRColor pixel;
            pixel.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
            pixel.green = static_cast<uint8_t>(buffer[bytes_counter++]);
            pixel.red = static_cast<uint8_t>(buffer[bytes_counter++]);
            bitmap[x].push_back(pixel);
        }
        bytes_counter += 2;
    }
    //TODO написать передачу картинки в кутэ

}

void
SchemeObjectParser::parseShape(const char* buffer, Scheme::SchemeParams& scheme_params, const uint32_t block_size,
                               int id_pos) {
    ;
}