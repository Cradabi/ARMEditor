#include "SchemeObjectParser.h"

void SchemeObjectParser::rewriteCacheObject(int32_t lib_index, int32_t cache_size) {

    SchemeFile.read(buffer, cache_size);

    CacheFileOut.write((char*) &lib_index, types_sizes._32bits);
    CacheFileOut.write((char*) &cache_size, types_sizes._32bits);
    CacheFileOut.write(buffer, cache_size);

    lae::WriteLog(LogsFile, "\nWatch lower in OBJS section ⇓ \n", true);

}


void SchemeObjectParser::parseObject(int32_t lib_index) {

    sop::ObjectParams object_params;

    object_params.lib_index = lib_index;

    getMatrix(object_params.coord_matrix, 3, 3);

    object_params.angle = getSomeFloat(object_params.angle);

    object_params.state = getSomeInt(object_params.state);

    object_params.hard_id = getSomeInt(object_params.hard_id);

    object_params.is_struct_object = getBool();
    object_params.is_lib_object = getBool();
    object_params.is_struct_object = getBool();

    if (!object_params.is_lib_object) {
        object_params.name_length = getSomeInt(object_params.name_length);
        getString(object_params.name, object_params.name_length);
    }

    object_params.hint_length = getSomeInt(object_params.hint_length);
    getString(object_params.hint, object_params.hint_length);
    object_params.hint_show = getBool();

    object_params.tag = getSomeInt(object_params.tag);

    getMatrix(object_params.contur_real_matrix, 3, 9);
    getMatrix(object_params.contur_frame_matrix, 3, 9);

    object_params.reflection_possibility = getBool();
    if (!object_params.is_lib_object) {
        object_params.horizontal_reflection_mx = getBool();
        object_params.vertical_reflection_my = getBool();
    }


    object_params.normal_state = getSomeInt(object_params.normal_state);

    object_params.has_ts = getBool();
    object_params.invalid = getBool();

    object_params.object_type = getSomeInt(object_params.object_type);

    object_params.index = getSomeInt(object_params.index);

    if (!object_params.is_lib_object) {
        object_params.index_cache = getSomeInt(object_params.index_cache);
    }

    object_params.show = getBool();

    object_params.button_left_active = getBool();
    object_params.button_right_active = getBool();
    object_params.buttons_swapped = getBool();

    object_params.is_animated = getBool();
    object_params.animation_speed = getSomeInt(object_params.animation_speed);
    object_params.hide_when_animation_stopped = getBool();

    object_params.bgcolor_not_needed = getBool();

    if (object_params.is_lib_object) {
        object_params.horizontal_reflection_mx = getBool();
        object_params.vertical_reflection_my = getBool();
        object_params.has_info_for_analysis = getBool();
    }

    if (!object_params.is_lib_object) {
        object_params.glue_points_amount = getSomeInt(object_params.animation_speed);
        getVector(object_params.glue_points_vector, object_params.glue_points_amount);

        object_params.states_amount = getSomeInt(object_params.states_amount);
        object_params.primitives_in_state_amount = getSomeInt(object_params.primitives_in_state_amount);
    }

    if (object_params.is_struct_object)
        parseStructObject();
    else if (object_params.is_lib_object)
        parseLibObject(object_params);
//    else if (object_params.is_text_object)
//        parseText();
    else
        parsePrimitive(object_params);

    writeObjectInfo(object_params);
}

void SchemeObjectParser::parseLibObject(sop::ObjectParams& lib_object_params) {
    CacheFileIn.open(cachefile_path, std::ios_base::binary);

    sop::ObjectParams actual_object_params;

    int32_t lib_id;
    int32_t lib_size;

    CacheFileIn.read(buffer, types_sizes._32bits);
    lib_id = getSomeInt(lib_id, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    lib_size = getSomeInt(lib_size, true);

    int32_t actual_cursor;
    while (lib_id != lib_object_params.lib_index) {
        actual_cursor = CacheFileIn.tellg();
        CacheFileIn.clear();
        CacheFileIn.seekg(actual_cursor + lib_size, std::ios_base::beg);

        CacheFileIn.read(buffer, types_sizes._32bits);
        lib_id = getSomeInt(lib_id, true);

        CacheFileIn.read(buffer, types_sizes._32bits);
        lib_size = getSomeInt(lib_size, true);
    }

    CacheFileIn.read(buffer, 3 * 3 * types_sizes._64bits);
    getMatrix(actual_object_params.coord_matrix, 3, 3, true);

    CacheFileIn.read(buffer, types_sizes._64bits);
    actual_object_params.angle = getSomeFloat(actual_object_params.angle, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.state = getSomeInt(actual_object_params.state, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.hard_id = getSomeInt(actual_object_params.hard_id, true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.is_struct_object = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.is_lib_object = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.is_struct_object = getBool(true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.name_length = getSomeInt(actual_object_params.name_length, true);
    CacheFileIn.read(buffer, actual_object_params.name_length);
    getString(actual_object_params.name, actual_object_params.name_length, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.hint_length = getSomeInt(actual_object_params.hint_length, true);
    CacheFileIn.read(buffer, actual_object_params.hint_length);
    getString(actual_object_params.hint, actual_object_params.hint_length, true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.hint_show = getBool(true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.tag = getSomeInt(actual_object_params.tag, true);

    CacheFileIn.read(buffer, 3 * 9 * types_sizes._64bits);
    getMatrix(actual_object_params.contur_real_matrix, 3, 9, true);
    CacheFileIn.read(buffer, 3 * 9 * types_sizes._64bits);
    getMatrix(actual_object_params.contur_frame_matrix, 3, 9, true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.reflection_possibility = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.horizontal_reflection_mx = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.vertical_reflection_my = getBool(true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.normal_state = getSomeInt(actual_object_params.normal_state, true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.has_ts = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.invalid = getBool(true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.object_type = getSomeInt(actual_object_params.object_type, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.index = getSomeInt(actual_object_params.index, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.index_cache = getSomeInt(actual_object_params.index_cache, true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.show = getBool(true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.button_left_active = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.button_right_active = getBool(true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.buttons_swapped = getBool(true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.is_animated = getBool(true);
    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.animation_speed = getSomeInt(actual_object_params.animation_speed, true);
    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.hide_when_animation_stopped = getBool(true);

    CacheFileIn.read(buffer, types_sizes._8bits);
    actual_object_params.bgcolor_not_needed = getBool(true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.glue_points_amount = getSomeInt(actual_object_params.animation_speed, true);

    CacheFileIn.read(buffer, actual_object_params.glue_points_amount * types_sizes._32bits);
    getVector(actual_object_params.glue_points_vector, actual_object_params.glue_points_amount, true);

    CacheFileIn.read(buffer, types_sizes._32bits);
    actual_object_params.states_amount = getSomeInt(actual_object_params.states_amount, true);
    actual_object_params.primitives_in_state_amount = getSomeInt(actual_object_params.primitives_in_state_amount, true);

    lae::WriteLog(LogsFile, "Lib object params:", true);
    writeObjectInfo(lib_object_params);

    lae::WriteLog(LogsFile, "Actual object params:", true);
    writeObjectInfo(actual_object_params);

    for (uint16_t _state = 0; _state < actual_object_params.states_amount; ++_state) {
        for (uint16_t _primitive = 0; _primitive < actual_object_params.primitives_in_state_amount; ++_primitive) {

            sop::PrimitiveParams primitive_params;

            CacheFileIn.read(buffer, types_sizes._32bits);
            primitive_params.points_amount = getSomeInt(primitive_params.points_amount, true);
            CacheFileIn.read(buffer, primitive_params.points_amount * types_sizes._32bits);
            getVector(primitive_params.points_vector, primitive_params.points_amount, true);

            CacheFileIn.read(buffer, types_sizes._32bits);
            primitive_params.primitive_type = getSomeInt(primitive_params.primitive_type, true);

            CacheFileIn.read(buffer, types_sizes._32bits);
            primitive_params.ti_style = getSomeInt(primitive_params.ti_style, true);

            CacheFileIn.read(buffer, 3);
            getColor(primitive_params.pen_color, true);
            CacheFileIn.read(buffer, 3);
            getColor(primitive_params.brush_color, true);
            CacheFileIn.read(buffer, 3);
            getColor(primitive_params.trans_color, true);

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.is_transparent = getBool(true);

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.brush_style = getSomeInt(primitive_params.brush_style, true);
            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.pen_style = getSomeInt(primitive_params.pen_style, true);
            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.pen_width = getSomeInt(primitive_params.pen_width, true);

            CacheFileIn.read(buffer, types_sizes._32bits);
            primitive_params.text_length = getSomeInt(primitive_params.text_length, true);
            CacheFileIn.read(buffer, primitive_params.text_length);
            getString(primitive_params.text, primitive_params.text_length, true);

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.style_end = getSomeInt(primitive_params.style_end, true);
            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.style_start = getSomeInt(primitive_params.style_start, true);
            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.style_frame = getSomeInt(primitive_params.style_frame, true);

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.connect = getSomeInt(primitive_params.connect, true);

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.is_font = getBool(true);

            CacheFileIn.read(buffer, types_sizes._32bits);
            primitive_params.line_marker_amount = getSomeInt(primitive_params.line_marker_amount, true);

            CacheFileIn.read(buffer, 3 * 3 * types_sizes._64bits);
            getMatrix(primitive_params.indentity_matrix, 3, 3, true);

            CacheFileIn.read(buffer, types_sizes._64bits);
            primitive_params.primitive_angle = getSomeFloat(primitive_params.primitive_angle, true);

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.show = getBool(true);

            if (primitive_params.is_font) {
                getFont(primitive_params, true);
            }

            if (_primitive == actual_object_params.primitives_in_state_amount - 1) {

                CacheFileIn.read(buffer, types_sizes._64bits);
                primitive_params.koeff = getSomeFloat(primitive_params.koeff, true);

                CacheFileIn.read(buffer, types_sizes._32bits);
                primitive_params.caption_length = getSomeInt(primitive_params.caption_length, true);
                CacheFileIn.read(buffer, primitive_params.caption_length);
                getString(primitive_params.caption, primitive_params.caption_length, true);

            }

            CacheFileIn.read(buffer, types_sizes._8bits);
            primitive_params.has_info_for_analysis = getBool(true);

            switch (primitive_params.primitive_type) {
                case objects_types.ptNone:
                    lae::PrintLog("Парсер объектов: Неизвестный тип примитива: ptNone\n");
                    break;
                case objects_types.ptGoBtn:
                    break;
                case objects_types.ptGoPoint:
                    break;
                case objects_types.ptGluePoint:
                    break;
                case objects_types.ptLine:
                    break;
                case objects_types.ptPolygon:
                    break;
                case objects_types.ptEllipse:
                    break;
                case objects_types.ptRectangle:
                    break;
                case objects_types.ptDuga:
                    break;
                case objects_types.ptTeleupr:
                    break;
                case objects_types.ptTeleizm:
                    break;
                case objects_types.ptSignal:
                    break;
                case objects_types.ptShape:
                    break;
                default:
                    lae::PrintLog("Парсер объектов: Неизвестный тип примитива\n");
                    break;
            }
            writePrimitiveParams(primitive_params);
        }
    }
};

void SchemeObjectParser::parsePrimitive(sop::ObjectParams& object_params) {

    sop::PrimitiveParams primitive_params;


    primitive_params.points_amount = getSomeInt(primitive_params.points_amount);
    getVector(primitive_params.points_vector, primitive_params.points_amount);

    primitive_params.primitive_type = getSomeInt(primitive_params.primitive_type);

    primitive_params.ti_style = getSomeInt(primitive_params.ti_style);

    getColor(primitive_params.pen_color);
    getColor(primitive_params.brush_color);
    getColor(primitive_params.trans_color);

    primitive_params.is_transparent = getBool();

    primitive_params.brush_style = getSomeInt(primitive_params.brush_style);
    primitive_params.pen_style = getSomeInt(primitive_params.pen_style);
    primitive_params.pen_width = getSomeInt(primitive_params.pen_width);

    primitive_params.text_length = getSomeInt(primitive_params.text_length);
    getString(primitive_params.text, primitive_params.text_length);

    primitive_params.style_end = getSomeInt(primitive_params.style_end);
    primitive_params.style_start = getSomeInt(primitive_params.style_start);
    primitive_params.style_frame = getSomeInt(primitive_params.style_frame);

    primitive_params.connect = getSomeInt(primitive_params.connect);

    primitive_params.is_font = getBool();

    primitive_params.line_marker_amount = getSomeInt(primitive_params.line_marker_amount);

    getMatrix(primitive_params.indentity_matrix, 3, 3);

    primitive_params.primitive_angle = getSomeFloat(primitive_params.primitive_angle);

    primitive_params.show = getBool();

    if (primitive_params.is_font) {
        getFont(primitive_params);
    }

    primitive_params.is_picture = getBool();

    if (primitive_params.is_picture) {
        getPicture(primitive_params, primitive_params.bmp_filepath);
    }

    primitive_params.koeff = getSomeFloat(primitive_params.koeff);

    primitive_params.caption_length = getSomeInt(primitive_params.caption_length);
    getString(primitive_params.caption, primitive_params.caption_length);

    primitive_params.has_info_for_analysis = getBool();

    switch (primitive_params.primitive_type) {
        case objects_types.ptNone:
            lae::PrintLog("Парсер объектов: Неизвестный тип примитива: ptNone\n");
            break;
        case objects_types.ptGoBtn:
            break;
        case objects_types.ptGoPoint:
            break;
        case objects_types.ptGluePoint:
            break;
        case objects_types.ptLine:
            break;
        case objects_types.ptPolygon:
            break;
        case objects_types.ptEllipse:
            break;
        case objects_types.ptRectangle:
            break;
        case objects_types.ptDuga:
            break;
        case objects_types.ptTeleupr:
            break;
        case objects_types.ptTeleizm:
            break;
        case objects_types.ptSignal:
            break;
        case objects_types.ptShape:
            break;
        default:
            lae::PrintLog("Парсер объектов: Неизвестный тип примитива\n");
            break;
    }
    writePrimitiveParams(primitive_params);
}

void SchemeObjectParser::getFont(sop::PrimitiveParams& primitive_params, bool is_buffer_filled) {
    ;
}

void SchemeObjectParser::getPicture(sop::PrimitiveParams& primitive_params, std::string& bmp_filepath,
                                    bool is_buffer_filled) {
    ++pictures_counter;

    bmp_filepath = std::to_string(pictures_counter);

    BMP bmp;

    primitive_params.width_of_picture = getSomeInt(primitive_params.width_of_picture);

    primitive_params.height_of_picture = getSomeInt(primitive_params.height_of_picture);

    primitive_params.bit_depth = getSomeInt(primitive_params.bit_depth);


    primitive_params.pixmap.resize(primitive_params.height_of_picture,
                                   std::vector<sop::BGRColor>(primitive_params.width_of_picture));

    for (uint32_t y = 0; y < primitive_params.height_of_picture; ++y) {
        for (uint32_t x = 0; x < primitive_params.width_of_picture; ++x) {
            sop::BGRColor pixel;

            SchemeFile.read(buffer, 3);

            pixel.blue = static_cast<uint8_t>(buffer[0]);
            pixel.green = static_cast<uint8_t>(buffer[1]);
            pixel.red = static_cast<uint8_t>(buffer[2]);
            primitive_params.pixmap[y][x] = pixel;
        }
        SchemeFile.read(buffer, 2);
    }

    bmp.makeBmp(bmp_filepath, primitive_params.pixmap);

    bmp_filepath = "../parser lib/tmp_pictures/" + bmp_filepath + ".bmp";

}

void SchemeObjectParser::writeObjectInfo(const sop::ObjectParams& object_params) {
    lae::WriteLog(LogsFile, "lib_index: ");
    lae::WriteLog(LogsFile, object_params.lib_index, true);

    lae::WriteLog(LogsFile, "coord_matrix: ");
    for (int i = 0; i < object_params.coord_matrix.size(); i++) {
        for (int j = 0; j < object_params.coord_matrix[i].size(); j++) {
            lae::WriteLog(LogsFile, object_params.coord_matrix[i][j], ' ');
        }
        lae::WriteLog(LogsFile, '\n');
    }

    lae::WriteLog(LogsFile, "angle: ");
    lae::WriteLog(LogsFile, object_params.angle, true);

    lae::WriteLog(LogsFile, "state: ");
    lae::WriteLog(LogsFile, object_params.state, true);

    lae::WriteLog(LogsFile, "hard_id: ");
    lae::WriteLog(LogsFile, object_params.hard_id, true);

    lae::WriteLog(LogsFile, "is_struct_object: ");
    lae::WriteLog(LogsFile, object_params.is_struct_object, true);

    lae::WriteLog(LogsFile, "is_lib_object: ");
    lae::WriteLog(LogsFile, object_params.is_lib_object, true);

    lae::WriteLog(LogsFile, "is_text_object: ");
    lae::WriteLog(LogsFile, object_params.is_text_object, true);

    lae::WriteLog(LogsFile, "name_length: ");
    lae::WriteLog(LogsFile, object_params.name_length, true);

    lae::WriteLog(LogsFile, "name: ");
    lae::WriteLog(LogsFile, object_params.name, true);

    lae::WriteLog(LogsFile, "hint_length: ");
    lae::WriteLog(LogsFile, object_params.hint_length, true);

    lae::WriteLog(LogsFile, "hint: ");
    lae::WriteLog(LogsFile, object_params.hint, true);

    lae::WriteLog(LogsFile, "hint_show: ");
    lae::WriteLog(LogsFile, object_params.hint_show, true);

    lae::WriteLog(LogsFile, "tag: ");
    lae::WriteLog(LogsFile, object_params.tag, true);

    lae::WriteLog(LogsFile, "contur_real_matrix: ");
    for (int i = 0; i < object_params.contur_real_matrix.size(); i++) {
        for (int j = 0; j < object_params.contur_real_matrix[i].size(); j++) {
            lae::WriteLog(LogsFile, object_params.contur_real_matrix[i][j], ' ');
        }
        lae::WriteLog(LogsFile, '\n');
    }

    lae::WriteLog(LogsFile, "contur_frame_matrix: ");
    for (int i = 0; i < object_params.contur_frame_matrix.size(); i++) {
        for (int j = 0; j < object_params.contur_frame_matrix[i].size(); j++) {
            lae::WriteLog(LogsFile, object_params.contur_frame_matrix[i][j], ' ');
        }
        lae::WriteLog(LogsFile, '\n');
    }

    lae::WriteLog(LogsFile, "reflection_possibility: ");
    lae::WriteLog(LogsFile, object_params.reflection_possibility, true);

    lae::WriteLog(LogsFile, "horizontal_reflection_mx: ");
    lae::WriteLog(LogsFile, object_params.horizontal_reflection_mx, true);

    lae::WriteLog(LogsFile, "vertical_reflection_my: ");
    lae::WriteLog(LogsFile, object_params.vertical_reflection_my, true);

    lae::WriteLog(LogsFile, "normal_state: ");
    lae::WriteLog(LogsFile, object_params.normal_state, true);

    lae::WriteLog(LogsFile, "has_ts: ");
    lae::WriteLog(LogsFile, object_params.has_ts, true);

    lae::WriteLog(LogsFile, "invalid: ");
    lae::WriteLog(LogsFile, object_params.invalid, true);

    lae::WriteLog(LogsFile, "object_type: ");
    lae::WriteLog(LogsFile, object_params.object_type, true);

    lae::WriteLog(LogsFile, "index: ");
    lae::WriteLog(LogsFile, object_params.index, true);

    lae::WriteLog(LogsFile, "index_cache: ");
    lae::WriteLog(LogsFile, object_params.index_cache, true);

    lae::WriteLog(LogsFile, "show: ");
    lae::WriteLog(LogsFile, object_params.show, true);

    lae::WriteLog(LogsFile, "button_left_active: ");
    lae::WriteLog(LogsFile, object_params.button_left_active, true);

    lae::WriteLog(LogsFile, "button_right_active: ");
    lae::WriteLog(LogsFile, object_params.button_right_active, true);

    lae::WriteLog(LogsFile, "buttons_swapped: ");
    lae::WriteLog(LogsFile, object_params.buttons_swapped, true);

    lae::WriteLog(LogsFile, "is_animated: ");
    lae::WriteLog(LogsFile, object_params.is_animated, true);

    lae::WriteLog(LogsFile, "animation_speed: ");
    lae::WriteLog(LogsFile, object_params.animation_speed, true);

    lae::WriteLog(LogsFile, "hide_when_animation_stopped: ");
    lae::WriteLog(LogsFile, object_params.hide_when_animation_stopped, true);

    lae::WriteLog(LogsFile, "bgcolor_not_needed: ");
    lae::WriteLog(LogsFile, object_params.bgcolor_not_needed, true);

    lae::WriteLog(LogsFile, "glue_points_amount: ");
    lae::WriteLog(LogsFile, object_params.glue_points_amount, true);

    lae::WriteLog(LogsFile, "glue_points_vector: ", true);
    for (int i = 0; i < object_params.glue_points_vector.size(); i++) {
        lae::WriteLog(LogsFile, "x: ");
        lae::WriteLog(LogsFile, object_params.glue_points_vector[i].x);
        lae::WriteLog(LogsFile, " y: ");
        lae::WriteLog(LogsFile, object_params.glue_points_vector[i].y, true);
    }

    lae::WriteLog(LogsFile, "states_amount: ");
    lae::WriteLog(LogsFile, object_params.states_amount, true);

    lae::WriteLog(LogsFile, "primitives_in_state_amount: ");
    lae::WriteLog(LogsFile, object_params.primitives_in_state_amount, true);

    lae::WriteLog(LogsFile, "has_info_for_analysis: ");
    lae::WriteLog(LogsFile, object_params.has_info_for_analysis, true);
}

void SchemeObjectParser::writePrimitiveParams(const sop::PrimitiveParams& primitive_params) {
    lae::WriteLog(LogsFile, "points_amount: ");
    lae::WriteLog(LogsFile, primitive_params.points_amount, true);

    lae::WriteLog(LogsFile, "points_vector: ");
    for (int i = 0; i < primitive_params.points_vector.size(); i++) {
        lae::WriteLog(LogsFile, primitive_params.points_vector[i].x);
        lae::WriteLog(LogsFile, " ");
        lae::WriteLog(LogsFile, primitive_params.points_vector[i].y, true);
    }

    lae::WriteLog(LogsFile, "primitive_type: ");
    lae::WriteLog(LogsFile, primitive_params.primitive_type, true);

    lae::WriteLog(LogsFile, "ti_style: ");
    lae::WriteLog(LogsFile, primitive_params.ti_style, true);

    lae::WriteLog(LogsFile, "pen_color: ", true);
    lae::WriteLog(LogsFile, "r: ");
    lae::WriteLog(LogsFile, primitive_params.pen_color.red, true);
    lae::WriteLog(LogsFile, "g: ");
    lae::WriteLog(LogsFile, primitive_params.pen_color.green, true);
    lae::WriteLog(LogsFile, "b: ");
    lae::WriteLog(LogsFile, primitive_params.pen_color.blue, true);

    lae::WriteLog(LogsFile, "brush_color: ", true);
    lae::WriteLog(LogsFile, "r: ");
    lae::WriteLog(LogsFile, primitive_params.brush_color.red, true);
    lae::WriteLog(LogsFile, "g: ");
    lae::WriteLog(LogsFile, primitive_params.brush_color.green, true);
    lae::WriteLog(LogsFile, "b: ");
    lae::WriteLog(LogsFile, primitive_params.brush_color.blue, true);

    lae::WriteLog(LogsFile, "trans_color: ");
    lae::WriteLog(LogsFile, primitive_params.trans_color, true);
    lae::WriteLog(LogsFile, "r: ");
    lae::WriteLog(LogsFile, primitive_params.trans_color.red, true);
    lae::WriteLog(LogsFile, "g: ");
    lae::WriteLog(LogsFile, primitive_params.trans_color.green, true);
    lae::WriteLog(LogsFile, "b: ");
    lae::WriteLog(LogsFile, primitive_params.trans_color.blue, true);

    lae::WriteLog(LogsFile, "is_transparent: ");
    lae::WriteLog(LogsFile, primitive_params.is_transparent, true);

    lae::WriteLog(LogsFile, "brush_style: ");
    lae::WriteLog(LogsFile, primitive_params.brush_style, true);

    lae::WriteLog(LogsFile, "pen_style: ");
    lae::WriteLog(LogsFile, primitive_params.pen_style, true);

    lae::WriteLog(LogsFile, "pen_width: ");
    lae::WriteLog(LogsFile, primitive_params.pen_width, true);

    lae::WriteLog(LogsFile, "text_length: ");
    lae::WriteLog(LogsFile, primitive_params.text_length, true);

    lae::WriteLog(LogsFile, "text: ");
    lae::WriteLog(LogsFile, primitive_params.text, true);

    lae::WriteLog(LogsFile, "style_end: ");
    lae::WriteLog(LogsFile, primitive_params.style_end, true);

    lae::WriteLog(LogsFile, "style_start: ");
    lae::WriteLog(LogsFile, primitive_params.style_start, true);

    lae::WriteLog(LogsFile, "style_frame: ");
    lae::WriteLog(LogsFile, primitive_params.style_frame, true);

    lae::WriteLog(LogsFile, "is_font: ");
    lae::WriteLog(LogsFile, primitive_params.is_font, true);

    lae::WriteLog(LogsFile, "connect: ");
    lae::WriteLog(LogsFile, primitive_params.connect, true);

    lae::WriteLog(LogsFile, "line_marker_amount: ");
    lae::WriteLog(LogsFile, primitive_params.line_marker_amount, true);

    lae::WriteLog(LogsFile, "indentity_matrix: ");
    for (int i = 0; i < primitive_params.indentity_matrix.size(); i++) {
        for (int j = 0; j < primitive_params.indentity_matrix[i].size(); j++) {
            lae::WriteLog(LogsFile, primitive_params.indentity_matrix[i][j], ' ');
        }
        lae::WriteLog(LogsFile, '\n');
    }

    lae::WriteLog(LogsFile, "primitive_angle: ");
    lae::WriteLog(LogsFile, primitive_params.primitive_angle, true);

    lae::WriteLog(LogsFile, "show: ");
    lae::WriteLog(LogsFile, primitive_params.show, true);

    lae::WriteLog(LogsFile, "is_picture: ");
    lae::WriteLog(LogsFile, primitive_params.is_picture, true);

    lae::WriteLog(LogsFile, "width_of_picture: ");
    lae::WriteLog(LogsFile, primitive_params.width_of_picture, true);

    lae::WriteLog(LogsFile, "height_of_picture: ");
    lae::WriteLog(LogsFile, primitive_params.height_of_picture, true);

    lae::WriteLog(LogsFile, "bit_depth: ");
    lae::WriteLog(LogsFile, primitive_params.bit_depth, true);

    lae::WriteLog(LogsFile, "pixmap: ");
    lae::WriteLog(LogsFile, "он тут есть правда", true);

    lae::WriteLog(LogsFile, "bmp_filepath: ");
    lae::WriteLog(LogsFile, primitive_params.bmp_filepath, true);

    lae::WriteLog(LogsFile, "koeff: ");
    lae::WriteLog(LogsFile, primitive_params.koeff, true);

    lae::WriteLog(LogsFile, "caption_length: ");
    lae::WriteLog(LogsFile, primitive_params.caption_length, true);

    lae::WriteLog(LogsFile, "caption: ");
    lae::WriteLog(LogsFile, primitive_params.caption, true);

    lae::WriteLog(LogsFile, "has_info_for_analysis: ");
    lae::WriteLog(LogsFile, primitive_params.has_info_for_analysis, true);
}
