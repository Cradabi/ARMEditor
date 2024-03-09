#include "SchemeObjectParser.h"

#include <tuple>


std::tuple<double, double, double> SchemeObjectParser::getCenterAndAngle(uint32_t &bytes_counter_temp) {

    double center_x;
    getSomeFloat(center_x, 8, bytes_counter_temp);

    bytes_counter_temp += 16;

    double center_y;
    getSomeFloat(center_y, 8, bytes_counter_temp);

    bytes_counter_temp += 24;

    double angle;
    getSomeFloat(angle, 8, bytes_counter_temp);

    return std::make_tuple(center_x, center_y, angle);
}

std::tuple<bool, bool, bool> SchemeObjectParser::getReflections(uint32_t &bytes_counter_temp) {
    bytes_counter_temp += 456;

    bool reflection_posibility = static_cast<bool>(buffer[bytes_counter_temp++]);
    bool reflection_verctical = static_cast<bool>(buffer[bytes_counter_temp++]);
    bool reflection_horizantal = static_cast<bool>(buffer[bytes_counter_temp]);

    return std::make_tuple(reflection_posibility, reflection_verctical, reflection_horizantal);

}

std::tuple<uint32_t, uint32_t, uint32_t> SchemeObjectParser::getIdAndHalves(uint32_t &bytes_counter_temp) {
    uint32_t id;
    getSomeInt(id, 4, bytes_counter_temp);

    bytes_counter_temp += 12;

    uint32_t half_x = 0;
    getSomeInt(half_x, 4, bytes_counter_temp);

    bytes_counter_temp += 8;

    uint32_t half_y = 0;
    getSomeInt(half_y, 4, bytes_counter_temp);

    return std::make_tuple(id, half_x, half_y);
}

std::tuple<ssp::BGRColor, ssp::BGRColor> SchemeObjectParser::getColors(uint32_t &bytes_counter_temp) {
    ssp::BGRColor pen;
    getColor(pen, bytes_counter_temp);

    ssp::BGRColor brush;
    getColor(brush, bytes_counter_temp);

    return std::make_tuple(pen, brush);
}

std::tuple<bool, uint8_t, uint8_t> SchemeObjectParser::getStylesAndWidth(uint32_t &bytes_counter_temp) {
    bool brush_style;
    brush_style = static_cast<bool>(buffer[bytes_counter_temp++]);

    uint8_t line_style;
    line_style = static_cast<uint8_t>(buffer[bytes_counter_temp++]);

    uint8_t width;
    width = static_cast<uint8_t>(buffer[bytes_counter_temp++]);

    return std::make_tuple(brush_style, line_style, width);
}

std::tuple<uint32_t, std::string> SchemeObjectParser::getText_(uint32_t &bytes_counter_temp) {
    uint32_t text_length = 0;
    getSomeInt(text_length, 4, bytes_counter_temp);

    std::string text;
    for (int i = bytes_counter_temp; i < text_length + bytes_counter_temp; ++i) {
        text += buffer[i];
    }
    bytes_counter_temp += text_length;
    return std::make_tuple(text_length, text);
}

void
SchemeObjectParser::parseRectangle(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                   int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bool reflection_posibility, reflection_verctical, reflection_horizantal;
    std::tie(reflection_posibility, reflection_verctical, reflection_horizantal) = getReflections(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    scheme_params.objects_vector.push_back(
            new Rectangle(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                          (360 - (int) angle) % 360,
                          width, line_style,
                          {pen.red, pen.green, pen.blue},
                          " Прямоугольник ", true, 0, 0,
                          {brush.red, brush.green, brush.blue},
                          brush_style, 0, 0));

}

void SchemeObjectParser::parseEllips(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                     int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);


    bool reflection_posibility, reflection_verctical, reflection_horizantal;
    std::tie(reflection_posibility, reflection_verctical, reflection_horizantal) = getReflections(bytes_counter);

    bytes_counter = id_pos + 4;


    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    scheme_params.objects_vector.push_back(
            new Ellipse(center_x - half_x, center_y - half_y, half_x * 2, half_y * 2,
                        (360 - (int) angle) % 360,
                        width, line_style,
                        {pen.red, pen.green, pen.blue},
                        " Эллипс ",
                        true,
                        {brush.red, brush.green, brush.blue},
                        brush_style, 0, 0));

}

void SchemeObjectParser::parseText(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                   int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    uint32_t text_length = 0;
    std::string text;
    std::tie(text_length, text) = getText_(bytes_counter);

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 1; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Text((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2, half_y * 2,
                         (360 - (int) angle) % 360,
                         text, " Текст ", line_style, width,
                         {brush.red, brush.green, brush.blue},
                         1, brush_style, font_name, font_size,
                         {font_color.red, font_color.green, font_color.blue},
                         font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                         1));
    }
}

void
SchemeObjectParser::parsePolygon(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                 int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bool reflection_posibility, reflection_verctical, reflection_horizantal;
    std::tie(reflection_posibility, reflection_verctical, reflection_horizantal) = getReflections(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(id, 4, bytes_counter);

    uint32_t amount_of_dots;
    getSomeInt(amount_of_dots, 4, bytes_counter);


    bool end_polygon = false;
    std::vector<std::vector<int>> coords;
    for (int32_t i = 0; i < amount_of_dots; ++i) {
        std::vector<int> pair;
        int32_t x;
        getSomeInt(x, 4, bytes_counter);

        int32_t y;
        getSomeInt(y, 4, bytes_counter);

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

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    uint32_t text_length = 0;
    std::string text;
    std::tie(text_length, text) = getText_(bytes_counter);

    scheme_params.objects_vector.push_back(
            new Polygon(coords, end_polygon,
                        (360 - (int) angle) % 360,
                        width, line_style, " Прямоугольник ",
                        {pen.red, pen.green, pen.blue},
                        {brush.red, brush.green, brush.blue},
                        true, brush_style, 0, 0));
}

void
SchemeObjectParser::parseTelecontrol(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                     int id_pos) {

    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    uint32_t text_length = 0;
    std::string text;
    std::tie(text_length, text) = getText_(bytes_counter);

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 2; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Telecontrol((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                half_y * 2,
                                (360 - (int) angle) % 360,
                                text, " Телеуправление ", line_style, width,
                                {brush.red, brush.green, brush.blue},
                                1, brush_style, font_name, font_size,
                                {font_color.red, font_color.green, font_color.blue},
                                font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                1));
    }

}

void
SchemeObjectParser::parseTelemeasure(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                     int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    uint32_t text_length = 0;
    std::string text;
    std::tie(text_length, text) = getText_(bytes_counter);

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 2; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Telemeasure((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                half_y * 2,
                                (360 - (int) angle) % 360,
                                text, " Телеизмерение ", line_style, width,
                                {brush.red, brush.green, brush.blue},
                                1, brush_style, font_name, font_size,
                                {font_color.red, font_color.green, font_color.blue},
                                font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                1));
    }
}

void
SchemeObjectParser::parseSignal(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    uint32_t text_length = 0;
    std::string text;
    std::tie(text_length, text) = getText_(bytes_counter);

    bytes_counter += 4;

    uint8_t font_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

    if (font_bool) {
        uint32_t font_size;
        getSomeInt(font_size, 4, bytes_counter);

        uint8_t bold_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t italic_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint8_t underlined_bool = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_name_length;
        getSomeInt(font_name_length, 4, bytes_counter);

        std::string font_name;
        for (int i = bytes_counter; i < font_name_length + bytes_counter; ++i) {
            font_name += buffer[i];
        }
        bytes_counter += font_name_length;

        ssp::BGRColor font_color;
        getColor(font_color, bytes_counter);

        uint8_t font_align_horz = static_cast<uint8_t>(buffer[bytes_counter++]);
        uint8_t font_align_vert = static_cast<uint8_t>(buffer[bytes_counter++]);
        bytes_counter += 2; //MB цвет заливки

        uint8_t font_autosize = static_cast<uint8_t>(buffer[bytes_counter++]);

        uint32_t font_width;
        getSomeInt(font_width, 4, bytes_counter);

        uint32_t font_height;
        getSomeInt(font_height, 4, bytes_counter);

        uint32_t font_descent;
        getSomeInt(font_descent, 4, bytes_counter);

        scheme_params.objects_vector.push_back(
                new Telesignalisation((int) round(center_x - half_x), (int) round(center_y - half_y), half_x * 2,
                                      half_y * 2,
                                      (360 - (int) angle) % 360,
                                      text, " Телесигнализация ", line_style, width,
                                      {brush.red, brush.green, brush.blue},
                                      1, brush_style, font_name, font_size,
                                      {font_color.red, font_color.green, font_color.blue},
                                      font_align_horz, font_align_vert, bold_bool, italic_bool, underlined_bool, 0,
                                      1));
    }
}

void
SchemeObjectParser::parsePicture(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                 int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bool reflection_posibility, reflection_verctical, reflection_horizantal;
    std::tie(reflection_posibility, reflection_verctical, reflection_horizantal) = getReflections(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    uint32_t text_length = 0;
    std::string text;
    std::tie(text_length, text) = getText_(bytes_counter);

    bytes_counter += 89;

    uint8_t not_scale;
    not_scale = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint8_t is_picture;
    is_picture = static_cast<uint8_t>(buffer[bytes_counter++]);

    uint32_t width_of_picture;
    getSomeInt(width_of_picture, 4, bytes_counter);

    uint32_t height_of_picture;
    getSomeInt(height_of_picture, 4, bytes_counter);

    uint8_t bit_depth;
    bit_depth = static_cast<uint8_t>(buffer[bytes_counter++]);

    for (uint32_t x = 0; x < width_of_picture; ++x) {
        for (uint32_t y = 0; y < height_of_picture; ++y) {
            ssp::BGRColor pixel;
            pixel.blue = static_cast<uint8_t>(buffer[bytes_counter++]);
            pixel.green = static_cast<uint8_t>(buffer[bytes_counter++]);
            pixel.red = static_cast<uint8_t>(buffer[bytes_counter++]);
        }
        bytes_counter += 2;
    }


}

void SchemeObjectParser::parseLine(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                   int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bool reflection_posibility, reflection_verctical, reflection_horizantal;
    std::tie(reflection_posibility, reflection_verctical, reflection_horizantal) = getReflections(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(id, 4, bytes_counter);

    bytes_counter += 4;

    int32_t cord_x1;
    getSomeInt(cord_x1, 4, bytes_counter);

    int32_t cord_y1;
    getSomeInt(cord_y1, 4, bytes_counter);

    int32_t cord_x2;
    getSomeInt(cord_x2, 4, bytes_counter);

    int32_t cord_y2;
    getSomeInt(cord_y2, 4, bytes_counter);

    bytes_counter += 2;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    bytes_counter += 5;

    uint8_t end_arrow_style = static_cast<uint8_t> (buffer[bytes_counter++]);

    uint8_t start_arrow_style = static_cast<uint8_t> (buffer[bytes_counter]);

    scheme_params.objects_vector.push_back(
            new Line((int) round(center_x + cord_x1), (int) round(center_y + cord_y1),
                     (int) round(center_x + cord_x2), (int) round(center_y + cord_y2), "", "Линия",
                     true,
                     line_style, 0, width, start_arrow_style, end_arrow_style, {pen.red, pen.green, pen.blue},
                     0, 0));
}

void SchemeObjectParser::parseArc(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                  int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bool reflection_posibility, reflection_verctical, reflection_horizantal;
    std::tie(reflection_posibility, reflection_verctical, reflection_horizantal) = getReflections(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(id, 4, bytes_counter);

    bytes_counter += 12;

    int32_t half_x = 0;
    getSomeInt(half_x, 4, bytes_counter);

    bytes_counter += 16;

    int32_t half_y;
    getSomeInt(half_y, 4, bytes_counter);

    int32_t start_angle;
    getSomeInt(start_angle, 4, bytes_counter);

    int32_t end_angle;
    getSomeInt(end_angle, 4, bytes_counter);

    bytes_counter += 2;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    bytes_counter += 4;

    bool brush_style;
    uint8_t line_style, width;
    std::tie(brush_style, line_style, width) = getStylesAndWidth(bytes_counter);

    scheme_params.objects_vector.push_back(
            new Arc(center_x - abs(half_x), center_y - abs(half_y), abs(half_x) * 2, abs(half_y) * 2,
                    (360 - (int) angle) % 360, start_angle, end_angle,
                    width, line_style,
                    {pen.red, pen.green, pen.blue},
                    " Дуга ",
                    true,
                    {brush.red, brush.green, brush.blue},
                    brush_style, 0, 0));
}

void
SchemeObjectParser::parseGoBtn(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                               int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id;
    getSomeInt(id, 4, bytes_counter);

    bytes_counter += 12;

    uint32_t half_x;
    getSomeInt(half_x, 4, bytes_counter);

    bytes_counter += 8;

    uint32_t half_y;
    getSomeInt(half_x, 4, bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    scheme_params.objects_vector.push_back(
            new TransitionButton(0, center_x - half_x, center_y - half_y,
                                 half_x * 2, half_y * 2, angle,
                                 {brush.red, brush.green, brush.blue},
                                 " Кнопка перехода ", true, 1));

}

void
SchemeObjectParser::parseGoPoint(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                 int id_pos) {
    uint32_t bytes_counter = 16;

    double center_x, center_y, angle;
    std::tie(center_x, center_y, angle) = getCenterAndAngle(bytes_counter);

    bytes_counter = id_pos + 4;

    uint32_t id, half_x, half_y;
    std::tie(id, half_x, half_y) = getIdAndHalves(bytes_counter);

    bytes_counter += 10;

    ssp::BGRColor pen, brush;
    std::tie(pen, brush) = getColors(bytes_counter);

    scheme_params.objects_vector.push_back(
            new TransitionPoint(0, center_x - half_x, center_y - half_y,
                                half_x * 2, half_y * 2,
                                {pen.red, pen.green, pen.blue},
                                " Точка перехода ", true, 0));
}

void
SchemeObjectParser::parseShape(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                               int id_pos) {
    ;
}

void
SchemeObjectParser::parseGluePoint(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                   int id_pos) {
    ;
}

void SchemeObjectParser::parseNone(Scheme::SchemeParams &scheme_params, const uint32_t block_size,
                                   int id_pos) {
    ;
}