#include "SchemeObjectParser.h"
#include "SchemeParser.h"


void SchemeObjectParser::getVector(std::ifstream& File, std::vector<sop::Point>& some_vector, uint8_t vector_size)
{
    some_vector.resize(vector_size);
    for (uint8_t _element = 0; _element < vector_size; ++_element)
    {
        getSomeInt(File, some_vector[_element].x);
        getSomeInt(File, some_vector[_element].y);
    }
}

// Функция получения цвета
void SchemeObjectParser::getColor(std::ifstream& File, sop::BGRColor& color, bool is_buffer_filled)
{
    // Если буффер не заполнен, то заполняем его
    if (!is_buffer_filled)
    {
        File.read(buffer_, 3);
    }

    color.blue = static_cast<uint8_t>(buffer_[0]);
    color.green = static_cast<uint8_t>(buffer_[1]);
    color.red = static_cast<uint8_t>(buffer_[2]);
}

void SchemeObjectParser::getMatrix(std::ifstream& File, std::vector<std::vector<double>>& some_matrix, uint8_t size_y,
                                   uint8_t size_x)
{
    some_matrix.resize(size_y);
    for (uint8_t y = 0; y < size_y; ++y)
    {
        some_matrix[y].resize(size_x);
        for (uint8_t x = 0; x < size_x; ++x)
        {
            getSomeFloat(File, some_matrix[y][x]);
        }
    }
}

void SchemeObjectParser::rewriteCacheObject(int32_t lib_index, int32_t cache_size)
{
    CacheFileOut.write(reinterpret_cast<char*>(&lib_index), size_._32bits);
    CacheFileOut.write(reinterpret_cast<char*>(&cache_size), size_._32bits);

    uint32_t bytes_counter = 0;
    while (bytes_counter < cache_size)
    {
        ++bytes_counter;
        scheme_file_.read(buffer_, size_._8bits);
        CacheFileOut.write(buffer_, size_._8bits);
    }

    lae::writeLog(logs_file_, "\nWatch lower in OBJS section ⇓ \n", true);
}

void SchemeObjectParser::getButtonsInfo(std::ifstream& File, sop::ObjectParams& object_params)
{
    object_params.button_left_active = getBool(File);
    object_params.button_right_active = getBool(File);
    object_params.buttons_swapped = getBool(File);
}

void SchemeObjectParser::getAnimationInfo(std::ifstream& File, sop::ObjectParams& object_params)
{
    object_params.is_animated = getBool(File);
    getSomeInt(File, object_params.animation_speed);
    object_params.hide_when_animation_stopped = getBool(File);
}

void SchemeObjectParser::parseObject(std::ifstream& File, int32_t lib_index, int32_t nesting_level)
{
    sop::ObjectParams object_params;

    if (nesting_level > 1)
    {
        object_params.is_group_object = true;
    }

    object_params.lib_index = lib_index;

    getMatrix(File, object_params.coord_matrix, 3, 3);

    getSomeFloat(File, object_params.angle);

    getSomeInt(File, object_params.state);

    getSomeInt(File, object_params.hard_id);

    object_params.is_struct_object = getBool(File);
    object_params.is_lib_object = getBool(File);
    object_params.is_text_object = getBool(File);

    if (!object_params.is_lib_object)
    {
        getSomeInt(File, object_params.name_length);
        getString(File, object_params.name, object_params.name_length);
    }

    getSomeInt(File, object_params.hint_length);
    getString(File, object_params.hint, object_params.hint_length);
    object_params.hint_show = getBool(File);

    getSomeInt(File, object_params.tag);

    getMatrix(File, object_params.contur_real_matrix, 3, 9);
    getMatrix(File, object_params.contur_frame_matrix, 3, 9);

    object_params.reflection_possibility = getBool(File);
    if (!object_params.is_lib_object)
    {
        object_params.horizontal_reflection_mx = getBool(File);
        object_params.vertical_reflection_my = getBool(File);
    }

    getSomeInt(File, object_params.normal_state);

    object_params.has_ts = getBool(File);
    object_params.invalid = getBool(File);

    getSomeInt(File, object_params.object_type);

    getSomeInt(File, object_params.index);

    if (!object_params.is_lib_object)
    {
        getSomeInt(File, object_params.index_cache);
    }

    object_params.show = getBool(File);

    getButtonsInfo(File, object_params);

    getAnimationInfo(File, object_params);

    object_params.bgcolor_not_needed = getBool(File);

    if (object_params.is_lib_object)
    {
        object_params.horizontal_reflection_mx = getBool(File);
        object_params.vertical_reflection_my = getBool(File);
        object_params.has_info_for_analysis = getBool(File);
    }

    if (!object_params.is_lib_object)
    {
        getSomeInt(File, object_params.glue_points_amount);
        getVector(File, object_params.glue_points_vector, object_params.glue_points_amount);

        getSomeInt(File, object_params.states_amount);
        getSomeInt(File, object_params.primitives_in_state_amount);
    }

    //    if (object_params.is_struct_object)
    //        parseStructObject();
    if (object_params.is_lib_object)
    {
        // qDebug() << "Парсер объектов: читаю библ. объект...";
        parseLibObject(File, object_params);
        //    else if (object_params.is_text_object)
        //        parseText();
        // qDebug() << "OK";
    }
    else
    {
        // qDebug() << "Парсер объектов: читаю примитив...";
        parsePrimitive(File, object_params);
        // qDebug() << "OK";
    }

    writeObjectInfo(object_params);
}

void SchemeObjectParser::parseGroup(std::ifstream& File, int32_t nesting_level)
{
    sop::ObjectParams object_params;

    getMatrix(File, object_params.coord_matrix, 3, 3);

    getSomeFloat(File, object_params.angle);

    getSomeInt(File, object_params.state);

    getMatrix(File, object_params.contur_real_matrix, 3, 9);
    getMatrix(File, object_params.contur_frame_matrix, 3, 9);

    getSomeInt(File, object_params.index);

    writeObjectInfo(object_params);

    std::vector<std::vector<FiguresClasses::Primitive*>> patterns;
    patterns.emplace_back(group_objects_vector_);

    //TODO спросить по поводу отрицательных координат объектов
    scheme_params_->objects_vector.emplace_back(
        new GroupObject((int)round(object_params.contur_frame_matrix[0][0]),
                        (int)round(object_params.contur_frame_matrix[0][1]), ((int)round(
                            object_params.coord_matrix[0][2] - object_params.contur_frame_matrix[0][0])) * 2,
                        ((int)round(
                            object_params.coord_matrix[1][2] -
                            object_params.contur_frame_matrix[0][1])) * 2, object_params.angle,
                        object_params.index, object_params.state, object_params.name,
                        object_params.name, patterns, object_params.hint, object_params.show,
                        object_params.hint_show, 0, 0));

    if (nesting_level != 1)
    {
        group_objects_vector_.clear();
        group_objects_vector_.emplace_back(scheme_params_->objects_vector.back());
        scheme_params_->objects_vector.pop_back();
    }
    else
    {
        group_objects_vector_.clear();
    }
}

void SchemeObjectParser::parseLibObject(std::ifstream& File, sop::ObjectParams& lib_object_params)
{
    CacheFileIn.open(cachefile_path_, std::ios_base::binary);

    sop::ObjectParams actual_object_params;

    int32_t lib_id;
    int32_t lib_size;

    getSomeInt(CacheFileIn, lib_id);
    getSomeInt(CacheFileIn, lib_size);

    int32_t actual_cursor;
    while (lib_id != lib_object_params.lib_index)
    {
        actual_cursor = CacheFileIn.tellg();
        CacheFileIn.clear();
        CacheFileIn.seekg(actual_cursor + lib_size, std::ios_base::beg);

        getSomeInt(CacheFileIn, lib_id);
        getSomeInt(CacheFileIn, lib_size);
    }

    getMatrix(CacheFileIn, actual_object_params.coord_matrix, 3, 3);

    getSomeFloat(CacheFileIn, actual_object_params.angle);

    getSomeInt(CacheFileIn, actual_object_params.state);

    getSomeInt(CacheFileIn, actual_object_params.hard_id);

    actual_object_params.is_struct_object = getBool(CacheFileIn);
    actual_object_params.is_lib_object = getBool(CacheFileIn);
    actual_object_params.is_text_object = getBool(CacheFileIn);

    getSomeInt(CacheFileIn, actual_object_params.name_length);
    getString(CacheFileIn, actual_object_params.name, actual_object_params.name_length);

    getSomeInt(CacheFileIn, actual_object_params.hint_length);
    getString(CacheFileIn, actual_object_params.hint, actual_object_params.hint_length);
    actual_object_params.hint_show = getBool(CacheFileIn);

    getSomeInt(CacheFileIn, actual_object_params.tag);

    getMatrix(CacheFileIn, actual_object_params.contur_real_matrix, 3, 9);
    getMatrix(CacheFileIn, actual_object_params.contur_frame_matrix, 3, 9);

    actual_object_params.reflection_possibility = getBool(CacheFileIn);
    actual_object_params.horizontal_reflection_mx = getBool(CacheFileIn);
    actual_object_params.vertical_reflection_my = getBool(CacheFileIn);

    getSomeInt(CacheFileIn, actual_object_params.normal_state);

    actual_object_params.has_ts = getBool(CacheFileIn);
    actual_object_params.invalid = getBool(CacheFileIn);

    getSomeInt(CacheFileIn, actual_object_params.object_type);

    getSomeInt(CacheFileIn, actual_object_params.index);
    getSomeInt(CacheFileIn, actual_object_params.index_cache);

    actual_object_params.show = getBool(CacheFileIn);

    getButtonsInfo(CacheFileIn, actual_object_params);

    getAnimationInfo(CacheFileIn, actual_object_params);

    actual_object_params.bgcolor_not_needed = getBool(CacheFileIn);

    getSomeInt(CacheFileIn, actual_object_params.glue_points_amount);

    getVector(CacheFileIn, actual_object_params.glue_points_vector, actual_object_params.glue_points_amount);

    getSomeInt(CacheFileIn, actual_object_params.states_amount);
    getSomeInt(CacheFileIn,
               actual_object_params.primitives_in_state_amount);

    lae::writeLog(logs_file_, "\n\nLIB OBJECT PARAMS:");
    writeObjectInfo(lib_object_params);

    lae::writeLog(logs_file_, "\n\nACTUAL OBJECT PARAMS:");
    writeObjectInfo(actual_object_params);

    std::vector<Primitive*>* actual_vector;

    if (lib_object_params.is_group_object)
    {
        actual_vector = &group_objects_vector_;
    }
    else
    {
        actual_vector = &scheme_params_->objects_vector;
    }

    // LibraryObject tmp_lib_object(data);

    sop::PrimitiveParams primitive_params;
    std::vector<std::vector<Primitive*>> patterns;
    double maxAbs = std::max(std::abs(lib_object_params.coord_matrix[0][0]),
                             std::abs(lib_object_params.coord_matrix[0][1]));
    double radians = lib_object_params.angle * M_PI / 180.0; // Переводим градусы в радианы
    double sinValue = std::abs(std::sin(std::abs(radians))); // Находим синус модуля угла
    double cosValue = std::abs(std::cos(std::abs(radians)));
    double scale = 1;
    double scval = 1;

    // Проверка на синус, чтобы избежать деления на 0
    if (sinValue < 0 || sinValue > 1 || cosValue < 0 || cosValue > 1)
    {
        qDebug() << "Некорректный синус";
    }
    else
    {
        // Деление максимального числа по модулю на синус
        // qDebug() << sinValue << cosValue;
        scval = std::max(sinValue, cosValue);
        scale = maxAbs / scval;
    }
    // qDebug() << maxAbs << scval << scale;

    for (uint16_t _state = 0; _state < actual_object_params.states_amount; ++_state)
    {
        std::vector<Primitive*> primitives_in_pattern = {};
        //        for (int w = 0; w < actual_object_params.glue_points_amount; w++) {
        //            primitives_in_pattern.push_back(new Point((int) round(actual_object_params.glue_points_vector[w].x * scale),
        //                                                      (int) round(actual_object_params.glue_points_vector[w].y * scale),
        //                                                      4, {0, 0, 0}));
        //        }
        for (uint16_t _primitive = 0; _primitive < actual_object_params.primitives_in_state_amount; ++_primitive)
        {
            parsePrimitiveCommonFields(CacheFileIn, primitive_params);

            // primitive_params.has_info_for_analysis = getBool(CacheFileIn);

            primitive_params.is_picture = getBool(CacheFileIn);
            if (primitive_params.is_picture)
            {
                // qDebug() << "Парсер объектов: читаю картинку... ";
                getPicture(CacheFileIn, primitive_params, primitive_params.bmp_filepath);
                // qDebug() << "ОК";
            }

            // Нужные структуры:
            // lib_object_params лежит в OBJS обновляется только если есть другие объекты
            // actual_object_params лежит в CACH
            // primitive_params лежит в CACH обновляется с каждой итерацией, лежат подряд

            std::vector<std::vector<int>> points = {};
            bool polygon_end = false;

            double im1 = std::max(abs(primitive_params.indentity_matrix[0][0]), abs(primitive_params.indentity_matrix[0][1]));
            double im2 = std::max(abs(primitive_params.indentity_matrix[1][0]), abs(primitive_params.indentity_matrix[1][1]));
            double cosin = std::max(abs(sin(primitive_params.primitive_angle * (M_PI / 180.0))), abs(cos(primitive_params.primitive_angle * (M_PI / 180.0))));

            switch (primitive_params.primitive_type)
            {
            case objects_types_.ptNone:
                lae::printLog("Парсер объектов: Неизвестный тип примитива: ptNone\n");
                break;
            case objects_types_.ptGoBtn:
                primitives_in_pattern.push_back(
                    new TransitionButton(0, (int)round(primitive_params.indentity_matrix[0][2] * scale +
                                             primitive_params.points_vector[0].x * scale *
                                             im1/cosin),
                                         (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                             primitive_params.points_vector[0].y * scale *
                                             im2/cosin),
                                         (int)round((primitive_params.points_vector[2].x -
                                                 primitive_params.points_vector[0].x) * scale *
                                             im1/cosin),
                                         (int)round((primitive_params.points_vector[2].y -
                                                 primitive_params.points_vector[0].y) * scale *
                                             im2/cosin),
                                         (int)(360 - primitive_params.primitive_angle) % 360,
                                         {
                                             primitive_params.brush_color.red,
                                             primitive_params.brush_color.green,
                                             primitive_params.brush_color.blue
                                         }, "", primitive_params.show,
                                         primitive_params.brush_style, primitive_params.text,
                                         primitive_params.font.name,
                                         primitive_params.font.size,
                                         {
                                             primitive_params.font.color.red,
                                             primitive_params.font.color.green,
                                             primitive_params.font.color.blue
                                         },
                                         primitive_params.font.align_vertical,
                                         primitive_params.font.reserved, primitive_params.font.is_bold,
                                         primitive_params.font.is_italic,
                                         primitive_params.font.is_underlined, 0, 0));
                break;
            case objects_types_.ptGoPoint:
                primitives_in_pattern.push_back(
                    new TransitionPoint(0, (int)round(primitive_params.indentity_matrix[0][2] * scale +
                                            primitive_params.points_vector[0].x * scale *
                                            im1),
                                        (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                            primitive_params.points_vector[0].y * scale *
                                            im2),
                                        (int)round((primitive_params.points_vector[2].x -
                                                primitive_params.points_vector[0].x) * scale *
                                            im1),
                                        (int)round((primitive_params.points_vector[2].y -
                                                primitive_params.points_vector[0].y) * scale *
                                            im2),
                                        {
                                            primitive_params.brush_color.red,
                                            primitive_params.brush_color.green,
                                            primitive_params.brush_color.blue
                                        }, "", primitive_params.show,
                                        primitive_params.brush_style));
                break;
            case objects_types_.ptGluePoint:
                primitives_in_pattern.push_back(
                    new Point((int)round(primitive_params.points_vector[0].x * scale),
                              (int)round(primitive_params.points_vector[0].y * scale),
                              primitive_params.pen_width,
                              {
                                  primitive_params.pen_color.red, primitive_params.pen_color.green,
                                  primitive_params.pen_color.blue
                              }));
                break;
            case objects_types_.ptLine:
                primitives_in_pattern.push_back(
                    new Line((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                 primitive_params.points_vector[0].x * scale*im1/cosin),
                             (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                 primitive_params.points_vector[0].y * scale*im1/cosin),
                             (int)round(primitive_params.indentity_matrix[0][2] * scale +
                                 primitive_params.points_vector[1].x * scale*im1/cosin),
                             (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                 primitive_params.points_vector[1].y * scale*im1/cosin),
                             primitive_params.text, "", primitive_params.show,
                             primitive_params.pen_style, 0, primitive_params.pen_width,
                             primitive_params.style_start,
                             primitive_params.style_end,
                             {
                                 primitive_params.pen_color.red, primitive_params.pen_color.green,
                                 primitive_params.pen_color.blue
                             }, 0, 0, primitive_params.primitive_angle));
                break;
            case objects_types_.ptText:
                primitives_in_pattern.push_back(
                    new Text((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                 primitive_params.points_vector[0].x * scale *
                                 im1/cosin),
                             (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                 primitive_params.points_vector[0].y * scale *
                                 im2/cosin),
                             (int)round((primitive_params.points_vector[2].x -
                                     primitive_params.points_vector[0].x) * scale *
                                 im1/cosin),
                             (int)round((primitive_params.points_vector[2].y -
                                     primitive_params.points_vector[0].y) * scale *
                                 im2/cosin),
                             (int)(360 - primitive_params.primitive_angle) % 360, primitive_params.text,
                             "", primitive_params.pen_style, primitive_params.pen_width,
                             {
                                 primitive_params.brush_color.red,
                                 primitive_params.brush_color.green,
                                 primitive_params.brush_color.blue
                             }, primitive_params.show,
                             primitive_params.brush_style,
                             primitive_params.font.name, (int)round(primitive_params.font.size * scale),
                             {
                                 primitive_params.font.color.red, primitive_params.font.color.green,
                                 primitive_params.font.color.blue
                             }, primitive_params.font.align_vertical,
                             primitive_params.font.reserved, primitive_params.font.is_bold,
                             primitive_params.font.is_italic, primitive_params.font.is_underlined, 0, 0,
                             {
                                 primitive_params.pen_color.red, primitive_params.pen_color.green,
                                 primitive_params.pen_color.blue
                             }));
                break;
            case objects_types_.ptPolygon:
                for (int i = 0; i < primitive_params.points_amount; i++)
                {
                    if ((i + 1) == primitive_params.points_amount)
                    {
                        if (((int)round(primitive_params.points_vector[0].x * scale * im1/cosin) ==
                                points[0][0]) &&
                            ((int)round(primitive_params.points_vector[0].y * scale * im2/cosin) ==
                                points[0][1]))
                        {
                            polygon_end = true;
                        }
                        else
                        {
                            points.push_back({
                                (int)round(primitive_params.indentity_matrix[0][2] * scale +
                                    primitive_params.points_vector[i].x * scale *
                                    im1/cosin),
                                (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                    primitive_params.points_vector[i].y * scale *
                                    im2/cosin)
                            });
                            polygon_end = false;
                        }
                    }
                    else
                    {
                        points.push_back({
                            (int)round(primitive_params.indentity_matrix[0][2] * scale +
                                primitive_params.points_vector[i].x * scale *
                                im1/cosin),
                            (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                primitive_params.points_vector[i].y * scale *
                                im2/cosin)
                        });
                    }
                }
                primitives_in_pattern.push_back(
                    new Polygon(points, polygon_end, (int)(360 - primitive_params.primitive_angle) % 360,
                                primitive_params.pen_width, primitive_params.pen_style, "",
                                {
                                    primitive_params.pen_color.red, primitive_params.pen_color.green,
                                    primitive_params.pen_color.blue
                                },
                                {
                                    primitive_params.brush_color.red, primitive_params.brush_color.green,
                                    primitive_params.brush_color.blue
                                }, primitive_params.show,
                                (int)primitive_params.brush_style,
                                0, 0));
                break;
            case objects_types_.ptEllipse:
                primitives_in_pattern.push_back(
                    new Ellipse((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                    primitive_params.points_vector[0].x * scale *
                                    im1/cosin),
                                (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                    primitive_params.points_vector[0].y * scale *
                                    im2/cosin),
                                (int)round((primitive_params.points_vector[2].x -
                                        primitive_params.points_vector[0].x) * scale *
                                    im1/cosin),
                                (int)round((primitive_params.points_vector[2].y -
                                        primitive_params.points_vector[0].y) * scale *
                                    im2/cosin),
                                (int)(360 - primitive_params.primitive_angle) % 360,
                                primitive_params.pen_width, primitive_params.pen_style,
                                {
                                    primitive_params.pen_color.red, primitive_params.pen_color.green,
                                    primitive_params.pen_color.blue
                                }, "", primitive_params.show,
                                {
                                    primitive_params.brush_color.red, primitive_params.brush_color.green,
                                    primitive_params.brush_color.blue
                                }, primitive_params.brush_style,
                                0, 0));
                break;
            case objects_types_.ptRectangle:
                // qDebug() << scale;
                // qDebug() << primitive_params.indentity_matrix[0][2] << primitive_params.points_vector[0].x <<
                //     primitive_params.indentity_matrix[0][0];
                // qDebug() << primitive_params.indentity_matrix[1][2] << primitive_params.points_vector[0].y <<
                //     primitive_params.indentity_matrix[1][1];
                // qDebug() << primitive_params.points_vector[2].x << primitive_params.indentity_matrix[0][0] <<
                //     primitive_params.points_vector[0].x << primitive_params.indentity_matrix[0][0];
                // qDebug() << primitive_params.points_vector[2].y << primitive_params.indentity_matrix[1][1] <<
                //     primitive_params.points_vector[0].y << primitive_params.indentity_matrix[1][1];
                primitives_in_pattern.push_back(
                    new Rectangle((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                      primitive_params.points_vector[0].x * scale *
                                      im1),
                                  (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                      primitive_params.points_vector[0].y * scale *
                                      im2),
                                  (int)round((primitive_params.points_vector[2].x * scale *
                                      im1 -
                                      primitive_params.points_vector[0].x * scale *
                                      im1)),
                                  (int)round((primitive_params.points_vector[2].y * scale *
                                      im2 -
                                      primitive_params.points_vector[0].y * scale *
                                      im2)),
                                  (int)(360 - primitive_params.primitive_angle) % 360,
                                  primitive_params.pen_width, primitive_params.pen_style,
                                  {
                                      primitive_params.pen_color.red, primitive_params.pen_color.green,
                                      primitive_params.pen_color.blue
                                  }, "", primitive_params.show,
                                  0, 0,
                                  {
                                      primitive_params.brush_color.red, primitive_params.brush_color.green,
                                      primitive_params.brush_color.blue
                                  }, primitive_params.brush_style,
                                  0, 0));
                break;
            case objects_types_.ptDuga:
                primitives_in_pattern.push_back(
                    new Arc((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                primitive_params.points_vector[0].x * scale *
                                im1/cosin),
                            (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                primitive_params.points_vector[0].y * scale *
                                im2/cosin),
                            (int)round((primitive_params.points_vector[2].x -
                                    primitive_params.points_vector[0].x) * scale *
                                im1/cosin),
                            (int)round((primitive_params.points_vector[2].y -
                                    primitive_params.points_vector[0].y) * scale *
                                im2/cosin),
                            (int)(360 - primitive_params.primitive_angle) % 360,
                            (int)primitive_params.points_vector[4].x % 360,
                            (int)primitive_params.points_vector[4].y % 360,
                            primitive_params.pen_width, primitive_params.pen_style,
                            {
                                primitive_params.pen_color.red, primitive_params.pen_color.green,
                                primitive_params.pen_color.blue
                            }, "", primitive_params.show,
                            {
                                primitive_params.brush_color.red, primitive_params.brush_color.green,
                                primitive_params.brush_color.blue
                            }, primitive_params.brush_style,
                            0, 0));
                break;
            case objects_types_.ptTeleupr:
                primitives_in_pattern.push_back(
                    new Telecontrol((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                        primitive_params.points_vector[0].x * scale *
                                        im1/cosin),
                                    (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                        primitive_params.points_vector[0].y * scale *
                                        im2/cosin),
                                    (int)round((primitive_params.points_vector[2].x -
                                            primitive_params.points_vector[0].x) * scale *
                                        im1/cosin),
                                    (int)round((primitive_params.points_vector[2].y -
                                            primitive_params.points_vector[0].y) * scale *
                                        im2/cosin),
                                    (int)(360 - primitive_params.primitive_angle) % 360,
                                    primitive_params.text,
                                    "", primitive_params.pen_style, primitive_params.pen_width,
                                    {
                                        primitive_params.brush_color.red,
                                        primitive_params.brush_color.green,
                                        primitive_params.brush_color.blue
                                    }, primitive_params.show,
                                    primitive_params.brush_style,
                                    primitive_params.font.name, (int)round(primitive_params.font.size * scale),
                                    {
                                        primitive_params.font.color.red, primitive_params.font.color.green,
                                        primitive_params.font.color.blue
                                    },
                                    primitive_params.font.align_vertical,
                                    primitive_params.font.reserved, primitive_params.font.is_bold,
                                    primitive_params.font.is_italic, primitive_params.font.is_underlined, 0,
                                    0,
                                    {
                                        primitive_params.pen_color.red, primitive_params.pen_color.green,
                                        primitive_params.pen_color.blue
                                    }, 0));
                break;
            case objects_types_.ptTeleizm:
                primitives_in_pattern.push_back(
                    new Telemeasure((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                        primitive_params.points_vector[0].x * scale *
                                        im1/cosin),
                                    (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                        primitive_params.points_vector[0].y * scale *
                                        im2/cosin),
                                    (int)round((primitive_params.points_vector[2].x -
                                            primitive_params.points_vector[0].x) * scale *
                                        im1/cosin),
                                    (int)round((primitive_params.points_vector[2].y -
                                            primitive_params.points_vector[0].y) * scale *
                                        im2/cosin),
                                    (int)(360 - primitive_params.primitive_angle) % 360,
                                    primitive_params.text,
                                    "", primitive_params.pen_style, primitive_params.pen_width,
                                    {
                                        primitive_params.brush_color.red,
                                        primitive_params.brush_color.green,
                                        primitive_params.brush_color.blue
                                    }, primitive_params.show,
                                    primitive_params.brush_style,
                                    primitive_params.font.name, (int)round(primitive_params.font.size * scale),
                                    {
                                        primitive_params.font.color.red, primitive_params.font.color.green,
                                        primitive_params.font.color.blue
                                    },
                                    primitive_params.font.align_vertical,
                                    primitive_params.font.reserved, primitive_params.font.is_bold,
                                    primitive_params.font.is_italic, primitive_params.font.is_underlined, 0,
                                    0,
                                    {
                                        primitive_params.pen_color.red, primitive_params.pen_color.green,
                                        primitive_params.pen_color.blue
                                    }, 0));
                break;
            case objects_types_.ptSignal:
                primitives_in_pattern.push_back(
                    new Telesignalisation((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                              primitive_params.points_vector[0].x * scale *
                                              im1/cosin),
                                          (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                              primitive_params.points_vector[0].y * scale *
                                              im2/cosin),
                                          (int)round((primitive_params.points_vector[2].x -
                                                  primitive_params.points_vector[0].x) * scale *
                                              im1/cosin),
                                          (int)round((primitive_params.points_vector[2].y -
                                                  primitive_params.points_vector[0].y) * scale *
                                              im2/cosin),
                                          (int)(360 - primitive_params.primitive_angle) % 360,
                                          primitive_params.text,
                                          "", primitive_params.pen_style, primitive_params.pen_width,
                                          {
                                              primitive_params.brush_color.red,
                                              primitive_params.brush_color.green,
                                              primitive_params.brush_color.blue
                                          }, primitive_params.show,
                                          primitive_params.brush_style,
                                          primitive_params.font.name,
                                          (int)round(primitive_params.font.size * scale),
                                          {
                                              primitive_params.font.color.red,
                                              primitive_params.font.color.green,
                                              primitive_params.font.color.blue
                                          },
                                          primitive_params.font.align_vertical,
                                          primitive_params.font.reserved, primitive_params.font.is_bold,
                                          primitive_params.font.is_italic,
                                          primitive_params.font.is_underlined, 0, 0,
                                          {
                                              primitive_params.pen_color.red,
                                              primitive_params.pen_color.green,
                                              primitive_params.pen_color.blue
                                          }, 0));
                break;
            case objects_types_.ptPicture:
                qDebug() << primitive_params.trans_color.red << primitive_params.trans_color.green << primitive_params.trans_color.blue;
                primitives_in_pattern.push_back(
                    new Image((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                  primitive_params.points_vector[0].x * scale *
                                  im1/cosin),
                              (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                  primitive_params.points_vector[0].y * scale *
                                  im2/cosin),
                              (int)round((primitive_params.points_vector[2].x -
                                      primitive_params.points_vector[0].x) * scale *
                                  im1/cosin),
                              (int)round((primitive_params.points_vector[2].y -
                                      primitive_params.points_vector[0].y) * scale *
                                  im2/cosin),
                              primitive_params.bmp_filepath,
                              (int)(360 - primitive_params.primitive_angle) % 360,
                              primitive_params.pen_width,
                              primitive_params.pen_style,
                              {
                                  primitive_params.pen_color.red,
                                  primitive_params.pen_color.green,
                                  primitive_params.pen_color.blue
                              }, "",
                              primitive_params.show, 0,
                              {
                                  primitive_params.brush_color.red,
                                  primitive_params.brush_color.green,
                                  primitive_params.brush_color.blue
                              },
                              primitive_params.brush_style));
                break;
            case objects_types_.ptPolyLine:
                for (int i = 0; i < primitive_params.points_amount; i++)
                {
                    points.push_back({
                        (int)round(primitive_params.indentity_matrix[0][2] * scale +
                            primitive_params.points_vector[i].x * scale *
                            im1/cosin),
                        (int)round(primitive_params.indentity_matrix[1][2] * scale +
                            primitive_params.points_vector[i].y * scale *
                            im2/cosin)
                    });
                }
                primitives_in_pattern.push_back(
                    new CrookedLine(points, (int)(360 - primitive_params.primitive_angle) % 360,
                                    primitive_params.pen_width, primitive_params.pen_style, "",
                                    {
                                        primitive_params.pen_color.red, primitive_params.pen_color.green,
                                        primitive_params.pen_color.blue
                                    },
                                    {
                                        primitive_params.brush_color.red,
                                        primitive_params.brush_color.green,
                                        primitive_params.brush_color.blue
                                    }, primitive_params.show,
                                    (int)primitive_params.brush_style,
                                    0, 0));
                break;
            case objects_types_.ptShape:
                if (primitive_params.points_vector[4].y <= 4 ||
                    (primitive_params.points_vector[4].y >= 7 && primitive_params.points_vector[4].y != 20))
                {
                    primitives_in_pattern.push_back(new Rectangle(
                        (int)round(primitive_params.indentity_matrix[0][2] * scale +
                            primitive_params.points_vector[0].x * scale *
                            im1/cosin),
                        (int)round(primitive_params.indentity_matrix[1][2] * scale +
                            primitive_params.points_vector[0].y * scale *
                            im2/cosin),
                        (int)round(primitive_params.points_vector[2].x * scale *
                            im1 -
                            primitive_params.points_vector[0].x * scale *
                            im1/cosin),
                        (int)round(primitive_params.points_vector[2].y * scale *
                            im2 -
                            primitive_params.points_vector[0].y * scale *
                            im2/cosin),
                        (int)(360 - primitive_params.primitive_angle) % 360,
                        primitive_params.pen_width, primitive_params.pen_style,
                        {
                            primitive_params.pen_color.red, primitive_params.pen_color.green,
                            primitive_params.pen_color.blue
                        }, "", primitive_params.show,
                        0, 0,
                        {
                            primitive_params.brush_color.red, primitive_params.brush_color.green,
                            primitive_params.brush_color.blue
                        }, primitive_params.brush_style,
                        0, 0));
                }
                else
                {
                    primitives_in_pattern.push_back(
                        new Ellipse((int)round(primitive_params.indentity_matrix[0][2] * scale +
                                        primitive_params.points_vector[0].x * scale *
                                        im1),
                                    (int)round(primitive_params.indentity_matrix[1][2] * scale +
                                        primitive_params.points_vector[0].y * scale *
                                        im2),
                                    (int)round((primitive_params.points_vector[2].x * scale *
                                        im1 -
                                        primitive_params.points_vector[0].x * scale *
                                        im1)),
                                    (int)round((primitive_params.points_vector[2].y * scale *
                                        im2 -
                                        primitive_params.points_vector[0].y * scale *
                                        im2)),
                                    (int)(360 - primitive_params.primitive_angle) % 360,
                                    primitive_params.pen_width, primitive_params.pen_style,
                                    {
                                        primitive_params.pen_color.red, primitive_params.pen_color.green,
                                        primitive_params.pen_color.blue
                                    }, "", primitive_params.show,
                                    {
                                        primitive_params.brush_color.red,
                                        primitive_params.brush_color.green,
                                        primitive_params.brush_color.blue
                                    }, primitive_params.brush_style,
                                    0, 0));
                }
                break;
            default:
                lae::printLog("Парсер объектов: Неизвестный тип примитива: ");
                lae::printLog((int)primitive_params.primitive_type, true);
                break;
            }


            writePrimitiveParams(primitive_params);
            primitive_params = {};
        }
        //        for (int i = 0; i < primitives_in_pattern.size(), i++){
        //
        //        }

        patterns.push_back(primitives_in_pattern);
        primitive_params = {};


        getSomeFloat(CacheFileIn, primitive_params.koeff);

        getSomeInt(CacheFileIn, primitive_params.caption_length);
        getString(CacheFileIn, primitive_params.caption, primitive_params.caption_length);

        getSomeInt(CacheFileIn,
                   actual_object_params.primitives_in_state_amount);
    }
    actual_vector->emplace_back(
        new LibraryObject(abs((int)round(lib_object_params.contur_frame_matrix[0][0])),
                          abs((int)round(lib_object_params.contur_frame_matrix[0][1])), ((int)round(
                              lib_object_params.coord_matrix[0][2] - lib_object_params.contur_frame_matrix[0][0])) * 2,
                          ((int)round(
                              lib_object_params.coord_matrix[1][2] -
                              lib_object_params.contur_frame_matrix[0][1])) * 2, lib_object_params.angle,
                          lib_object_params.hard_id, lib_object_params.state, actual_object_params.name,
                          actual_object_params.name, patterns, lib_object_params.hint, lib_object_params.show,
                          lib_object_params.hint_show, lib_object_params.horizontal_reflection_mx,
                          lib_object_params.vertical_reflection_my));

    // TODO добавление либ. объекта в вектор
}

void SchemeObjectParser::parsePrimitiveCommonFields(std::ifstream& File, sop::PrimitiveParams& primitive_params)
{
    getSomeInt(File, primitive_params.points_amount);
    getVector(File, primitive_params.points_vector, primitive_params.points_amount);

    getSomeInt(File, primitive_params.primitive_type);

    getSomeInt(File, primitive_params.ti_style);

    getColor(File, primitive_params.pen_color);
    getColor(File, primitive_params.brush_color);
    getColor(File, primitive_params.trans_color);

    primitive_params.is_transparent = getBool(File);

    primitive_params.brush_style = getBool(File);
    getSomeInt(File, primitive_params.pen_style);
    getSomeInt(File, primitive_params.pen_width);

    getSomeInt(File, primitive_params.text_length);
    getString(File, primitive_params.text, primitive_params.text_length);

    getSomeInt(File, primitive_params.style_end);
    getSomeInt(File, primitive_params.style_start);
    getSomeInt(File, primitive_params.style_frame);

    getSomeInt(File, primitive_params.connect);

    primitive_params.is_font = getBool(File);
    if (primitive_params.is_font)
    {
        getFont(File, primitive_params);
    }

    getSomeInt(File, primitive_params.line_marker_amount);

    getMatrix(File, primitive_params.indentity_matrix, 3, 3);

    getSomeFloat(File, primitive_params.primitive_angle);

    primitive_params.show = getBool(File);
}

void SchemeObjectParser::parsePrimitive(std::ifstream& File, sop::ObjectParams& object_params)
{
    sop::PrimitiveParams primitive_params;
    // qDebug() << "Парсер объектов: читаю общие поля примитивов... ";
    parsePrimitiveCommonFields(File, primitive_params);
    // qDebug() << "ОК";

    primitive_params.is_picture = getBool(File);
    if (primitive_params.is_picture)
    {
        // qDebug() << "Парсер объектов: читаю картинку... ";
        getPicture(File, primitive_params, primitive_params.bmp_filepath);
        // qDebug() << "ОК";
    }

    getSomeFloat(File, primitive_params.koeff);

    getSomeInt(File, primitive_params.caption_length);
    getString(File, primitive_params.caption, primitive_params.caption_length);

    primitive_params.has_info_for_analysis = getBool(File);

    // Нужные структуры:
    // object_params лежит в OBJS
    // primitive_params лежит в OBJS

    std::vector<Primitive*>* actual_vector;

    if (object_params.is_group_object)
    {
        actual_vector = &group_objects_vector_;
    }
    else
    {
        actual_vector = &scheme_params_->objects_vector;
    }

    double c_m1 = std::max(abs(object_params.coord_matrix[0][0]), abs(object_params.coord_matrix[0][1]));
    double c_m2 = std::max(abs(object_params.coord_matrix[1][0]), abs(object_params.coord_matrix[1][1]));
    double cosin = std::max(abs(sin(object_params.angle * (M_PI / 180.0))), abs(cos(object_params.angle * (M_PI / 180.0))));
    // if (abs(object_params.coord_matrix[0][0]) >= abs(object_params.coord_matrix[0][1])) {
    //     c_m1 = object_params.coord_matrix[0][0];
    //     c_m2 = object_params.coord_matrix[1][1];
    // } else {
    //     c_m1 = object_params.coord_matrix[0][1];
    //     c_m2 = object_params.coord_matrix[1][0];
    // }

    // double c_m = std::max(c_m1, c_m2);

    // qDebug() << c_m1 << c_m2;

    std::vector<std::vector<int>> points = {};
    bool polygon_end = false;
    //    qDebug() << QString::fromStdString(primitive_params.bmp_filepath);
    // qDebug() << primitive_params.primitive_type;
    switch (primitive_params.primitive_type)
    {
    case objects_types_.ptNone:
        // qDebug() << "неизвестно";
        lae::printLog("Парсер объектов: Неизвестный тип примитива: ptNone\n");
        break;
    case objects_types_.ptGoBtn:
        // qDebug() << "gobtn";
        actual_vector->emplace_back(
            new TransitionButton(object_params.index, (int)round(object_params.coord_matrix[0][2] -
                                     abs((int)round(
                                         primitive_params.points_vector[0].x *
                                         c_m1/cosin))),
                                 (int)round(object_params.coord_matrix[1][2] -
                                     abs((int)round(primitive_params.points_vector[0].y *
                                         c_m2/cosin))),
                                 abs((int)round(
                                     primitive_params.points_vector[0].x * 2 *
                                     c_m1/cosin)),
                                 abs((int)round(
                                     primitive_params.points_vector[0].y * 2 *
                                     c_m2/cosin)),
                                 (int)(360 - object_params.angle) % 360, {
                                     primitive_params.brush_color.red,
                                     primitive_params.brush_color.green,
                                     primitive_params.brush_color.blue
                                 },
                                 object_params.hint, object_params.show, primitive_params.brush_style,
                                 primitive_params.text, primitive_params.font.name, primitive_params.font.size,
                                 {
                                     primitive_params.font.color.red, primitive_params.font.color.green,
                                     primitive_params.font.color.blue
                                 }, primitive_params.font.align_vertical,
                                 primitive_params.font.reserved, primitive_params.font.is_bold,
                                 primitive_params.font.is_italic, primitive_params.font.is_underlined, 0, 0));
        break;
    case objects_types_.ptGoPoint:
        // qDebug() << "gopoint";
        actual_vector->emplace_back(new TransitionPoint(object_params.index,
                                                        object_params.coord_matrix[0][2] -
                                                        abs(primitive_params.points_vector[0].x),
                                                        object_params.coord_matrix[1][2] -
                                                        abs(primitive_params.points_vector[0].y),
                                                        abs(primitive_params.points_vector[0].x) * 2,
                                                        abs(primitive_params.points_vector[0].y) *
                                                        2, {
                                                            primitive_params.brush_color.red,
                                                            primitive_params.brush_color.green,
                                                            primitive_params.brush_color.blue
                                                        },
                                                        object_params.hint, object_params.show,
                                                        primitive_params.brush_style));
        break;
    case objects_types_.ptGluePoint:
        // qDebug() << "gluepoint";
        actual_vector->emplace_back(
            new Point(object_params.coord_matrix[0][2] + primitive_params.points_vector[0].x,
                      object_params.coord_matrix[1][2] + primitive_params.points_vector[0].y,
                      primitive_params.pen_width,
                      {
                          primitive_params.pen_color.red, primitive_params.pen_color.green,
                          primitive_params.pen_color.blue
                      }));
        break;
    case objects_types_.ptLine:
        actual_vector->emplace_back(
            new Line((int)round(object_params.coord_matrix[0][2] +
                         (primitive_params.points_vector[0].x * c_m1) / cosin),
                     (int)round(object_params.coord_matrix[1][2] +
                         (primitive_params.points_vector[0].y * c_m1) / cosin),
                     (int)round(object_params.coord_matrix[0][2] +
                         (primitive_params.points_vector[1].x * c_m1) / cosin),
                     (int)round(object_params.coord_matrix[1][2] +
                         (primitive_params.points_vector[1].y * c_m1) / cosin),
                     primitive_params.text, object_params.hint, object_params.show,
                     primitive_params.pen_style, 0, primitive_params.pen_width,
                     primitive_params.style_start,
                     primitive_params.style_end,
                     {
                         primitive_params.pen_color.red, primitive_params.pen_color.green,
                         primitive_params.pen_color.blue
                     }, object_params.horizontal_reflection_mx,
                     object_params.vertical_reflection_my, object_params.angle));
        break;
    case objects_types_.ptText:
        // qDebug() << "text";
        actual_vector->emplace_back(
            new Text((int)round(object_params.coord_matrix[0][2] -
                         abs((int)round(primitive_params.points_vector[0].x *
                             c_m1/cosin))),
                     (int)round(object_params.coord_matrix[1][2] -
                         abs((int)round(primitive_params.points_vector[0].y *
                             c_m2/cosin))),
                     abs((int)round(
                         primitive_params.points_vector[0].x * 2 * c_m1/cosin)),
                     abs((int)round(
                         primitive_params.points_vector[0].y * 2 * c_m2/cosin)),
                     (int)(360 - object_params.angle) % 360,
                     primitive_params.text,
                     object_params.hint, primitive_params.pen_style, primitive_params.pen_width,
                     {
                         primitive_params.brush_color.red,
                         primitive_params.brush_color.green,
                         primitive_params.brush_color.blue
                     }, object_params.show, primitive_params.brush_style,
                     primitive_params.font.name, primitive_params.font.size,
                     {
                         primitive_params.font.color.red, primitive_params.font.color.green,
                         primitive_params.font.color.blue
                     }, primitive_params.font.align_vertical,
                     primitive_params.font.reserved, primitive_params.font.is_bold,
                     primitive_params.font.is_italic, primitive_params.font.is_underlined, 0, 0,
                     {
                         primitive_params.pen_color.red, primitive_params.pen_color.green,
                         primitive_params.pen_color.blue
                     }));
        break;
    case objects_types_.ptPolygon:
        // qDebug() << "polygon";
        for (int i = 0; i < primitive_params.points_amount; i++)
        {
            if ((i + 1) == primitive_params.points_amount)
            {
                if (((int)object_params.coord_matrix[0][2] + primitive_params.points_vector[i].x ==
                        points[0][0]) &&
                    ((int)object_params.coord_matrix[1][2] + primitive_params.points_vector[i].y ==
                        points[0][1]))
                {
                    polygon_end = true;
                }
                else
                {
                    points.push_back({
                        (int)(object_params.coord_matrix[0][2] +
                            primitive_params.points_vector[i].x *
                            c_m1/cosin),
                        (int)(object_params.coord_matrix[1][2] +
                            primitive_params.points_vector[i].y *
                            c_m2/cosin)
                    });
                    polygon_end = false;
                }
            }
            else
            {
                points.push_back({
                    (int)(object_params.coord_matrix[0][2] +
                        primitive_params.points_vector[i].x *
                        c_m1/cosin),
                    (int)(object_params.coord_matrix[1][2] +
                        primitive_params.points_vector[i].y *
                        c_m2/cosin)
                });
            }
        }
    // qDebug() << "Полигон считан";
        actual_vector->emplace_back(
            new Polygon(points, polygon_end, (int)(360 - object_params.angle) % 360,
                        primitive_params.pen_width, primitive_params.pen_style, object_params.hint,
                        {
                            primitive_params.pen_color.red, primitive_params.pen_color.green,
                            primitive_params.pen_color.blue
                        },
                        {
                            primitive_params.brush_color.red, primitive_params.brush_color.green,
                            primitive_params.brush_color.blue
                        }, object_params.show,
                        (int)primitive_params.brush_style,
                        object_params.horizontal_reflection_mx, object_params.vertical_reflection_my));
    // qDebug() << "Полигон записан";
        break;
    case objects_types_.ptEllipse:
        // qDebug() << "ellipse";
        actual_vector->emplace_back(
            new Ellipse(object_params.coord_matrix[0][2] - abs((int)round(
                            primitive_params.points_vector[0].x * c_m1/cosin)),
                        object_params.coord_matrix[1][2] - abs((int)round(
                            primitive_params.points_vector[0].y * c_m2/cosin)),
                        abs((int)round(
                            primitive_params.points_vector[0].x * c_m1/cosin)) * 2,
                        abs((int)round(
                            primitive_params.points_vector[0].y * c_m2/cosin)) * 2,
                        (int)(360 - object_params.angle) % 360,
                        primitive_params.pen_width, primitive_params.pen_style,
                        {
                            primitive_params.pen_color.red, primitive_params.pen_color.green,
                            primitive_params.pen_color.blue
                        }, object_params.hint, object_params.show,
                        {
                            primitive_params.brush_color.red, primitive_params.brush_color.green,
                            primitive_params.brush_color.blue
                        }, primitive_params.brush_style,
                        object_params.horizontal_reflection_mx, object_params.vertical_reflection_my));
        break;
    case objects_types_.ptRectangle:
        // qDebug() << "rect";
        actual_vector->emplace_back(
            new Rectangle(object_params.coord_matrix[0][2] - abs((int)round(
                              primitive_params.points_vector[0].x * c_m1/cosin)),
                          object_params.coord_matrix[1][2] - abs((int)round(
                              primitive_params.points_vector[0].y * c_m2/cosin)),
                          abs((int)round(
                              primitive_params.points_vector[0].x * c_m1/cosin)) * 2,
                          abs((int)round(
                              primitive_params.points_vector[0].y * c_m2/cosin)) * 2,
                          (int)(360 - object_params.angle) % 360,
                          primitive_params.pen_width, primitive_params.pen_style,
                          {
                              primitive_params.pen_color.red, primitive_params.pen_color.green,
                              primitive_params.pen_color.blue
                          }, object_params.hint, object_params.show, 0, 0,
                          {
                              primitive_params.brush_color.red, primitive_params.brush_color.green,
                              primitive_params.brush_color.blue
                          }, primitive_params.brush_style,
                          object_params.horizontal_reflection_mx, object_params.vertical_reflection_my));
        break;
    case objects_types_.ptDuga:
        // qDebug() << "duga";
        actual_vector->emplace_back(
            new Arc(object_params.coord_matrix[0][2] - abs((int)round(
                        primitive_params.points_vector[0].x * c_m1/cosin)),
                    object_params.coord_matrix[1][2] - abs((int)round(
                        primitive_params.points_vector[0].y * c_m2/cosin)),
                    abs((int)round(
                        primitive_params.points_vector[0].x * c_m1/cosin)) * 2,
                    abs((int)round(
                        primitive_params.points_vector[0].y * c_m2/cosin)) * 2,
                    (int)(360 - object_params.angle) % 360, (int)primitive_params.points_vector[4].x % 360,
                    (int)primitive_params.points_vector[4].y % 360,
                    primitive_params.pen_width, primitive_params.pen_style,
                    {
                        primitive_params.pen_color.red, primitive_params.pen_color.green,
                        primitive_params.pen_color.blue
                    }, object_params.hint, object_params.show,
                    {
                        primitive_params.brush_color.red, primitive_params.brush_color.green,
                        primitive_params.brush_color.blue
                    }, primitive_params.brush_style,
                    object_params.horizontal_reflection_mx, object_params.vertical_reflection_my));
        break;
    case objects_types_.ptTeleupr:
        // qDebug() << "telepupr";
        actual_vector->emplace_back(
            new Telecontrol((int)round(object_params.coord_matrix[0][2] -
                                abs((int)round(primitive_params.points_vector[0].x *
                                    c_m1/cosin))),
                            (int)round(object_params.coord_matrix[1][2] -
                                abs((int)round(primitive_params.points_vector[0].y *
                                    c_m2/cosin))),
                            abs((int)round(
                                primitive_params.points_vector[0].x * 2 *
                                c_m1/cosin)),
                            abs((int)round(
                                primitive_params.points_vector[0].y * 2 *
                                c_m2/cosin)),
                            (int)(360 - object_params.angle) % 360,
                            primitive_params.text,
                            object_params.hint, primitive_params.pen_style, primitive_params.pen_width,
                            {
                                primitive_params.brush_color.red,
                                primitive_params.brush_color.green,
                                primitive_params.brush_color.blue
                            }, object_params.show,
                            primitive_params.brush_style,
                            primitive_params.font.name, primitive_params.font.size,
                            {
                                primitive_params.font.color.red, primitive_params.font.color.green,
                                primitive_params.font.color.blue
                            }, primitive_params.font.align_vertical,
                            primitive_params.font.reserved, primitive_params.font.is_bold,
                            primitive_params.font.is_italic, primitive_params.font.is_underlined, 0, 0,
                            {
                                primitive_params.pen_color.red, primitive_params.pen_color.green,
                                primitive_params.pen_color.blue
                            }, object_params.hard_id));
        break;
    case objects_types_.ptTeleizm:
        // qDebug() << "teleizm";
        actual_vector->emplace_back(
            new Telemeasure((int)round(object_params.coord_matrix[0][2] -
                                abs((int)round(primitive_params.points_vector[0].x *
                                    c_m1/cosin))),
                            (int)round(object_params.coord_matrix[1][2] -
                                abs((int)round(primitive_params.points_vector[0].y *
                                    c_m2/cosin))),
                            abs((int)round(
                                primitive_params.points_vector[0].x * 2 *
                                c_m1/cosin)),
                            abs((int)round(
                                primitive_params.points_vector[0].y * 2 *
                                c_m2/cosin)),
                            (int)(360 - object_params.angle) % 360,
                            primitive_params.text,
                            object_params.hint, primitive_params.pen_style, primitive_params.pen_width,
                            {
                                primitive_params.brush_color.red,
                                primitive_params.brush_color.green,
                                primitive_params.brush_color.blue
                            }, object_params.show,
                            primitive_params.brush_style,
                            primitive_params.font.name, primitive_params.font.size,
                            {
                                primitive_params.font.color.red, primitive_params.font.color.green,
                                primitive_params.font.color.blue
                            }, primitive_params.font.align_vertical,
                            primitive_params.font.reserved, primitive_params.font.is_bold,
                            primitive_params.font.is_italic, primitive_params.font.is_underlined, 0, 0,
                            {
                                primitive_params.pen_color.red, primitive_params.pen_color.green,
                                primitive_params.pen_color.blue
                            }, object_params.hard_id));
        break;
    case objects_types_.ptSignal:
        // qDebug() << "signal";
        actual_vector->emplace_back(
            new Telesignalisation((int)round(object_params.coord_matrix[0][2] -
                                      abs((int)round(primitive_params.points_vector[0].x *
                                          c_m1/cosin))),
                                  (int)round(object_params.coord_matrix[1][2] -
                                      abs((int)round(primitive_params.points_vector[0].y *
                                          c_m2/cosin))),
                                  abs((int)round(
                                      primitive_params.points_vector[0].x * 2 *
                                      c_m1/cosin)),
                                  abs((int)round(
                                      primitive_params.points_vector[0].y * 2 *
                                      c_m2/cosin)),
                                  (int)(360 - object_params.angle) % 360,
                                  primitive_params.text,
                                  object_params.hint, primitive_params.pen_style, primitive_params.pen_width,
                                  {
                                      primitive_params.brush_color.red,
                                      primitive_params.brush_color.green,
                                      primitive_params.brush_color.blue
                                  }, object_params.show,
                                  primitive_params.brush_style,
                                  primitive_params.font.name, primitive_params.font.size,
                                  {
                                      primitive_params.font.color.red, primitive_params.font.color.green,
                                      primitive_params.font.color.blue
                                  }, primitive_params.font.align_vertical,
                                  primitive_params.font.reserved, primitive_params.font.is_bold,
                                  primitive_params.font.is_italic, primitive_params.font.is_underlined, 0, 0,
                                  {
                                      primitive_params.pen_color.red, primitive_params.pen_color.green,
                                      primitive_params.pen_color.blue
                                  }, object_params.hard_id));
        break;
    case objects_types_.ptPicture:
        // qDebug() << "picture";
        qDebug() << primitive_params.trans_color.red << primitive_params.trans_color.green << primitive_params.trans_color.blue;
        actual_vector->emplace_back(
            new Image(object_params.coord_matrix[0][2] - abs(primitive_params.points_vector[0].x*c_m1/cosin),
                      object_params.coord_matrix[1][2] - abs(primitive_params.points_vector[0].y*c_m2/cosin),
                      abs(primitive_params.points_vector[0].x*c_m1/cosin) * 2,
                      abs(primitive_params.points_vector[0].y*c_m2/cosin) * 2, primitive_params.bmp_filepath,
                      (int)(360 - object_params.angle) % 360, primitive_params.pen_width,
                      primitive_params.pen_style,
                      {
                          primitive_params.pen_color.red, primitive_params.pen_color.green,
                          primitive_params.pen_color.blue
                      }, object_params.hint,
                      object_params.show, 0, {
                          primitive_params.brush_color.red,
                          primitive_params.brush_color.green,
                          primitive_params.brush_color.blue
                      },
                      primitive_params.brush_style));
        break;
    case objects_types_.ptPolyLine:
        // qDebug() << "polyline";
        for (int i = 0; i < primitive_params.points_amount; i++)
        {
            points.push_back({
                (int)(object_params.coord_matrix[0][2] +
                    primitive_params.points_vector[i].x *
                    c_m1/cosin),
                (int)(object_params.coord_matrix[1][2] +
                    primitive_params.points_vector[i].y *
                    c_m2/cosin)
            });
        }
        actual_vector->emplace_back(
            new CrookedLine(points, (int)(360 - object_params.angle) % 360,
                            primitive_params.pen_width, primitive_params.pen_style, object_params.hint,
                            {
                                primitive_params.pen_color.red, primitive_params.pen_color.green,
                                primitive_params.pen_color.blue
                            },
                            {
                                primitive_params.brush_color.red, primitive_params.brush_color.green,
                                primitive_params.brush_color.blue
                            }, object_params.show,
                            (int)primitive_params.brush_style,
                            object_params.horizontal_reflection_mx, object_params.vertical_reflection_my));
        break;
    case objects_types_.ptShape:
        if (primitive_params.points_vector[4].y <= 4 ||
            (primitive_params.points_vector[4].y >= 7 && primitive_params.points_vector[4].y != 20))
        {
            actual_vector->emplace_back(
                new Rectangle(object_params.coord_matrix[0][2] - abs((int)round(
                                  primitive_params.points_vector[0].x * c_m1/cosin)),
                              object_params.coord_matrix[1][2] - abs((int)round(
                                  primitive_params.points_vector[0].y * c_m2/cosin)),
                              abs((int)round(
                                  primitive_params.points_vector[0].x * c_m1/cosin)) *
                              2,
                              abs((int)round(
                                  primitive_params.points_vector[0].y * c_m2/cosin)) *
                              2,
                              (int)(360 - primitive_params.primitive_angle) % 360,
                              primitive_params.pen_width, primitive_params.pen_style,
                              {
                                  primitive_params.pen_color.red, primitive_params.pen_color.green,
                                  primitive_params.pen_color.blue
                              }, "", primitive_params.show, 0, 0,
                              {
                                  primitive_params.brush_color.red, primitive_params.brush_color.green,
                                  primitive_params.brush_color.blue
                              }, primitive_params.brush_style,
                              0, 0));
        }
        else
        {
            actual_vector->emplace_back(
                new Ellipse(object_params.coord_matrix[0][2] - abs((int)round(
                                primitive_params.points_vector[0].x * c_m1/cosin)),
                            object_params.coord_matrix[1][2] - abs((int)round(
                                primitive_params.points_vector[0].y * c_m2/cosin)),
                            abs((int)round(
                                primitive_params.points_vector[0].x * c_m1/cosin)) *
                            2,
                            abs((int)round(
                                primitive_params.points_vector[0].y * c_m2/cosin)) *
                            2,
                            (int)(360 - primitive_params.primitive_angle) % 360,
                            primitive_params.pen_width, primitive_params.pen_style,
                            {
                                primitive_params.pen_color.red, primitive_params.pen_color.green,
                                primitive_params.pen_color.blue
                            }, "", primitive_params.show,
                            {
                                primitive_params.brush_color.red, primitive_params.brush_color.green,
                                primitive_params.brush_color.blue
                            }, primitive_params.brush_style,
                            0, 0));
        }
        break;
    default:
        lae::printLog("Парсер объектов: Неизвестный тип примитива: ");
        lae::printLog((int)primitive_params.primitive_type, true);
        break;
    }
    writePrimitiveParams(primitive_params);
}

void SchemeObjectParser::getFont(std::ifstream& File, sop::PrimitiveParams& primitive_params)
{
    getSomeInt(File, primitive_params.font.size);

    primitive_params.font.is_bold = getBool(File);
    primitive_params.font.is_italic = getBool(File);
    primitive_params.font.is_underlined = getBool(File);

    getSomeInt(File, primitive_params.font.name_length);
    getString(File, primitive_params.font.name, primitive_params.font.name_length);

    File.read(buffer_, 3);
    primitive_params.font.color.red = static_cast<uint8_t>(buffer_[0]);
    primitive_params.font.color.green = static_cast<uint8_t>(buffer_[1]);
    primitive_params.font.color.blue = static_cast<uint8_t>(buffer_[2]);

    getSomeInt(File, primitive_params.font.align_horizontal);
    getSomeInt(File, primitive_params.font.align_vertical);

    getSomeInt(File, primitive_params.font.reserved);

    primitive_params.font.autosize = getBool(File);

    getSomeInt(File, primitive_params.font.width);
    getSomeInt(File, primitive_params.font.height);

    getSomeInt(File, primitive_params.font.descent);
}

void
SchemeObjectParser::getPicture(std::ifstream& File, sop::PrimitiveParams& primitive_params, std::string& bmp_filepath)
{
    ++pictures_counter;

    getSomeInt(File, primitive_params.width_of_picture);
    getSomeInt(File, primitive_params.height_of_picture);
    getSomeInt(File, primitive_params.bit_depth);

    bmp_filepath = std::to_string(pictures_counter);

    BMP bmp;

    primitive_params.pixmap.resize(primitive_params.height_of_picture,
                                   std::vector<sop::BGRColor>(primitive_params.width_of_picture));
    int picture_slide = (primitive_params.width_of_picture * 3) % 4;
    picture_slide == 3 ? picture_slide = 1 : picture_slide = picture_slide;
    for (uint32_t y = 0; y < primitive_params.height_of_picture; ++y)
    {
        for (uint32_t x = 0; x < primitive_params.width_of_picture; ++x)
        {
            sop::BGRColor pixel;

            File.read(buffer_, 3);

            pixel.blue = static_cast<uint8_t>(buffer_[0]);
            pixel.green = static_cast<uint8_t>(buffer_[1]);
            pixel.red = static_cast<uint8_t>(buffer_[2]);
            primitive_params.pixmap[y][x] = pixel;
        }

        File.read(buffer_, picture_slide);
    }

    bmp.makeBmp(bmp_filepath, primitive_params.pixmap);

    bmp_filepath = "../parser_lib/cache/tmp_pictures/" + bmp_filepath + ".bmp";
}

void SchemeObjectParser::writeObjectInfo(const sop::ObjectParams& object_params)
{
    lae::writeLog(logs_file_, "\nOBJECT INFO", true);

    lae::writeLog(logs_file_, "is in group: ");
    lae::writeLog(logs_file_, object_params.is_group_object, true);

    lae::writeLog(logs_file_, "lib_index: ");
    lae::writeLog(logs_file_, object_params.lib_index, true);

    lae::writeLog(logs_file_, "coord_matrix: ", true);
    for (int i = 0; i < object_params.coord_matrix.size(); i++)
    {
        for (int j = 0; j < object_params.coord_matrix[i].size(); j++)
        {
            lae::writeLog(logs_file_, object_params.coord_matrix[i][j]);
            lae::writeLog(logs_file_, ' ');
        }
        lae::writeLog(logs_file_, '\n');
    }

    lae::writeLog(logs_file_, "angle: ");
    lae::writeLog(logs_file_, object_params.angle, true);

    lae::writeLog(logs_file_, "state: ");
    lae::writeLog(logs_file_, object_params.state, true);

    lae::writeLog(logs_file_, "hard_id: ");
    lae::writeLog(logs_file_, object_params.hard_id, true);

    lae::writeLog(logs_file_, "is_struct_object: ");
    lae::writeLog(logs_file_, object_params.is_struct_object, true);

    lae::writeLog(logs_file_, "is_lib_object: ");
    lae::writeLog(logs_file_, object_params.is_lib_object, true);

    lae::writeLog(logs_file_, "is_text_object: ");
    lae::writeLog(logs_file_, object_params.is_text_object, true);

    lae::writeLog(logs_file_, "name_length: ");
    lae::writeLog(logs_file_, object_params.name_length, true);

    lae::writeLog(logs_file_, "name: ");
    lae::writeLog(logs_file_, object_params.name, true);

    lae::writeLog(logs_file_, "hint_length: ");
    lae::writeLog(logs_file_, object_params.hint_length, true);

    lae::writeLog(logs_file_, "hint: ");
    lae::writeLog(logs_file_, object_params.hint, true);

    lae::writeLog(logs_file_, "hint_show: ");
    lae::writeLog(logs_file_, object_params.hint_show, true);

    lae::writeLog(logs_file_, "tag: ");
    lae::writeLog(logs_file_, object_params.tag, true);

    lae::writeLog(logs_file_, "contur_real_matrix: ", true);
    for (int i = 0; i < object_params.contur_real_matrix.size(); i++)
    {
        for (int j = 0; j < object_params.contur_real_matrix[i].size(); j++)
        {
            lae::writeLog(logs_file_, object_params.contur_real_matrix[i][j]);
            lae::writeLog(logs_file_, ' ');
        }
        lae::writeLog(logs_file_, '\n');
    }

    lae::writeLog(logs_file_, "contur_frame_matrix: ", true);
    for (int i = 0; i < object_params.contur_frame_matrix.size(); i++)
    {
        for (int j = 0; j < object_params.contur_frame_matrix[i].size(); j++)
        {
            lae::writeLog(logs_file_, object_params.contur_frame_matrix[i][j]);
            lae::writeLog(logs_file_, ' ');
        }
        lae::writeLog(logs_file_, '\n');
    }

    lae::writeLog(logs_file_, "reflection_possibility: ");
    lae::writeLog(logs_file_, object_params.reflection_possibility, true);

    lae::writeLog(logs_file_, "horizontal_reflection_mx: ");
    lae::writeLog(logs_file_, object_params.horizontal_reflection_mx, true);

    lae::writeLog(logs_file_, "vertical_reflection_my: ");
    lae::writeLog(logs_file_, object_params.vertical_reflection_my, true);

    lae::writeLog(logs_file_, "normal_state: ");
    lae::writeLog(logs_file_, object_params.normal_state, true);

    lae::writeLog(logs_file_, "has_ts: ");
    lae::writeLog(logs_file_, object_params.has_ts, true);

    lae::writeLog(logs_file_, "invalid: ");
    lae::writeLog(logs_file_, object_params.invalid, true);

    lae::writeLog(logs_file_, "object_type: ");
    lae::writeLog(logs_file_, object_params.object_type, true);

    lae::writeLog(logs_file_, "index: ");
    lae::writeLog(logs_file_, object_params.index, true);

    lae::writeLog(logs_file_, "index_cache: ");
    lae::writeLog(logs_file_, object_params.index_cache, true);

    lae::writeLog(logs_file_, "show: ");
    lae::writeLog(logs_file_, object_params.show, true);

    lae::writeLog(logs_file_, "button_left_active: ");
    lae::writeLog(logs_file_, object_params.button_left_active, true);

    lae::writeLog(logs_file_, "button_right_active: ");
    lae::writeLog(logs_file_, object_params.button_right_active, true);

    lae::writeLog(logs_file_, "buttons_swapped: ");
    lae::writeLog(logs_file_, object_params.buttons_swapped, true);

    lae::writeLog(logs_file_, "is_animated: ");
    lae::writeLog(logs_file_, object_params.is_animated, true);

    lae::writeLog(logs_file_, "animation_speed: ");
    lae::writeLog(logs_file_, object_params.animation_speed, true);

    lae::writeLog(logs_file_, "hide_when_animation_stopped: ");
    lae::writeLog(logs_file_, object_params.hide_when_animation_stopped, true);

    lae::writeLog(logs_file_, "bgcolor_not_needed: ");
    lae::writeLog(logs_file_, object_params.bgcolor_not_needed, true);

    lae::writeLog(logs_file_, "glue_points_amount: ");
    lae::writeLog(logs_file_, object_params.glue_points_amount, true);

    lae::writeLog(logs_file_, "glue_points_vector: ", true);
    for (int i = 0; i < object_params.glue_points_vector.size(); i++)
    {
        lae::writeLog(logs_file_, "x: ");
        lae::writeLog(logs_file_, object_params.glue_points_vector[i].x);
        lae::writeLog(logs_file_, " y: ");
        lae::writeLog(logs_file_, object_params.glue_points_vector[i].y, true);
    }

    lae::writeLog(logs_file_, "states_amount: ");
    lae::writeLog(logs_file_, object_params.states_amount, true);

    lae::writeLog(logs_file_, "primitives_in_state_amount: ");
    lae::writeLog(logs_file_, object_params.primitives_in_state_amount, true);

    lae::writeLog(logs_file_, "has_info_for_analysis: ");
    lae::writeLog(logs_file_, object_params.has_info_for_analysis, true);
}

void SchemeObjectParser::writePrimitiveParams(const sop::PrimitiveParams& primitive_params)
{
    lae::writeLog(logs_file_, "\nPRIMITIVE PARAMS", true);

    lae::writeLog(logs_file_, "points_amount: ");
    lae::writeLog(logs_file_, primitive_params.points_amount, true);

    lae::writeLog(logs_file_, "points_vector: ", true);
    for (int i = 0; i < primitive_params.points_vector.size(); i++)
    {
        lae::writeLog(logs_file_, primitive_params.points_vector[i].x);
        lae::writeLog(logs_file_, ' ');
        lae::writeLog(logs_file_, primitive_params.points_vector[i].y, true);
    }

    lae::writeLog(logs_file_, "primitive_type: ");
    lae::writeLog(logs_file_, (int)primitive_params.primitive_type, true);

    lae::writeLog(logs_file_, "ti_style: ");
    lae::writeLog(logs_file_, (int)primitive_params.ti_style, true);

    lae::writeLog(logs_file_, "pen_color: ", true);
    lae::writeLog(logs_file_, "r: ");
    lae::writeLog(logs_file_, (int)primitive_params.pen_color.red, true);
    lae::writeLog(logs_file_, "g: ");
    lae::writeLog(logs_file_, (int)primitive_params.pen_color.green, true);
    lae::writeLog(logs_file_, "b: ");
    lae::writeLog(logs_file_, (int)primitive_params.pen_color.blue, true);

    lae::writeLog(logs_file_, "brush_color: ", true);
    lae::writeLog(logs_file_, "r: ");
    lae::writeLog(logs_file_, (int)primitive_params.brush_color.red, true);
    lae::writeLog(logs_file_, "g: ");
    lae::writeLog(logs_file_, (int)primitive_params.brush_color.green, true);
    lae::writeLog(logs_file_, "b: ");
    lae::writeLog(logs_file_, (int)primitive_params.brush_color.blue, true);

    lae::writeLog(logs_file_, "trans_color: ");
    lae::writeLog(logs_file_, "r: ");
    lae::writeLog(logs_file_, (int)primitive_params.trans_color.red, true);
    lae::writeLog(logs_file_, "g: ");
    lae::writeLog(logs_file_, (int)primitive_params.trans_color.green, true);
    lae::writeLog(logs_file_, "b: ");
    lae::writeLog(logs_file_, (int)primitive_params.trans_color.blue, true);

    lae::writeLog(logs_file_, "is_transparent: ");
    lae::writeLog(logs_file_, (int)primitive_params.is_transparent, true);

    lae::writeLog(logs_file_, "brush_style: ");
    lae::writeLog(logs_file_, (int)primitive_params.brush_style, true);

    lae::writeLog(logs_file_, "pen_style: ");
    lae::writeLog(logs_file_, (int)primitive_params.pen_style, true);

    lae::writeLog(logs_file_, "pen_width: ");
    lae::writeLog(logs_file_, (int)primitive_params.pen_width, true);

    lae::writeLog(logs_file_, "text_length: ");
    lae::writeLog(logs_file_, primitive_params.text_length, true);

    lae::writeLog(logs_file_, "text: ");
    lae::writeLog(logs_file_, primitive_params.text, true);

    lae::writeLog(logs_file_, "style_end: ");
    lae::writeLog(logs_file_, primitive_params.style_end, true);

    lae::writeLog(logs_file_, "style_start: ");
    lae::writeLog(logs_file_, primitive_params.style_start, true);

    lae::writeLog(logs_file_, "style_frame: ");
    lae::writeLog(logs_file_, primitive_params.style_frame, true);

    lae::writeLog(logs_file_, "is_font: ");
    lae::writeLog(logs_file_, primitive_params.is_font, true);

    if (primitive_params.is_font)
        writeFontInfo(primitive_params);

    lae::writeLog(logs_file_, "connect: ");
    lae::writeLog(logs_file_, primitive_params.connect, true);

    lae::writeLog(logs_file_, "line_marker_amount: ");
    lae::writeLog(logs_file_, primitive_params.line_marker_amount, true);

    lae::writeLog(logs_file_, "indentity_matrix: ", true);
    for (int i = 0; i < primitive_params.indentity_matrix.size(); i++)
    {
        for (int j = 0; j < primitive_params.indentity_matrix[i].size(); j++)
        {
            lae::writeLog(logs_file_, primitive_params.indentity_matrix[i][j]);
            lae::writeLog(logs_file_, ' ');
        }
        lae::writeLog(logs_file_, '\n');
    }

    lae::writeLog(logs_file_, "primitive_angle: ");
    lae::writeLog(logs_file_, primitive_params.primitive_angle, true);

    lae::writeLog(logs_file_, "show: ");
    lae::writeLog(logs_file_, primitive_params.show, true);

    lae::writeLog(logs_file_, "is_picture: ");
    lae::writeLog(logs_file_, primitive_params.is_picture, true);

    lae::writeLog(logs_file_, "width_of_picture: ");
    lae::writeLog(logs_file_, primitive_params.width_of_picture, true);

    lae::writeLog(logs_file_, "height_of_picture: ");
    lae::writeLog(logs_file_, primitive_params.height_of_picture, true);

    lae::writeLog(logs_file_, "bit_depth: ");
    lae::writeLog(logs_file_, (int)primitive_params.bit_depth, true);

    lae::writeLog(logs_file_, "pixmap: ");
    lae::writeLog(logs_file_, "true", true);

    lae::writeLog(logs_file_, "bmp_filepath: ");
    lae::writeLog(logs_file_, primitive_params.bmp_filepath, true);

    lae::writeLog(logs_file_, "koeff: ");
    lae::writeLog(logs_file_, primitive_params.koeff, true);

    lae::writeLog(logs_file_, "caption_length: ");
    lae::writeLog(logs_file_, primitive_params.caption_length, true);

    lae::writeLog(logs_file_, "caption: ");
    lae::writeLog(logs_file_, primitive_params.caption, true);

    lae::writeLog(logs_file_, "has_info_for_analysis: ");
    lae::writeLog(logs_file_, primitive_params.has_info_for_analysis, true);
}

void SchemeObjectParser::writeFontInfo(const sop::PrimitiveParams& primitive_params)
{
    lae::writeLog(logs_file_, "size: ");
    lae::writeLog(logs_file_, primitive_params.font.size, true);

    lae::writeLog(logs_file_, "is_bold: ");
    lae::writeLog(logs_file_, primitive_params.font.is_bold, true);

    lae::writeLog(logs_file_, "is_italic: ");
    lae::writeLog(logs_file_, primitive_params.font.is_italic, true);

    lae::writeLog(logs_file_, "is_underlined: ");
    lae::writeLog(logs_file_, primitive_params.font.is_underlined, true);

    lae::writeLog(logs_file_, "name_length: ");
    lae::writeLog(logs_file_, primitive_params.font.name_length, true);

    lae::writeLog(logs_file_, "name: ");
    lae::writeLog(logs_file_, primitive_params.font.name, true);
    lae::writeLog(logs_file_, "color: ", true);
    lae::writeLog(logs_file_, "r: ");
    lae::writeLog(logs_file_, (int)primitive_params.font.color.red, true);
    lae::writeLog(logs_file_, "g: ");
    lae::writeLog(logs_file_, (int)primitive_params.font.color.green, true);
    lae::writeLog(logs_file_, "b: ");
    lae::writeLog(logs_file_, (int)primitive_params.font.color.blue, true);

    lae::writeLog(logs_file_, "align_horizontal: ");
    lae::writeLog(logs_file_, (int)primitive_params.font.align_horizontal, true);

    lae::writeLog(logs_file_, "align_vertical: ");
    lae::writeLog(logs_file_, (int)primitive_params.font.align_vertical, true);

    lae::writeLog(logs_file_, "reserved: ");
    lae::writeLog(logs_file_, primitive_params.font.reserved, true);

    lae::writeLog(logs_file_, "autosize: ");
    lae::writeLog(logs_file_, primitive_params.font.autosize, true);

    lae::writeLog(logs_file_, "width: ");
    lae::writeLog(logs_file_, primitive_params.font.width, true);

    lae::writeLog(logs_file_, "height: ");
    lae::writeLog(logs_file_, primitive_params.font.height, true);

    lae::writeLog(logs_file_, "descent: ");
    lae::writeLog(logs_file_, primitive_params.font.descent, true);
}
