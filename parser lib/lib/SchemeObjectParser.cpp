#include "SchemeObjectParser.h"

void SchemeObjectParser::parseCacheObject(int32_t lib_index, int32_t cache_size) {
    int32_t counter = 0;
    CacheFile<<lib_index;
    CacheFile<<cache_size;
    while(counter < cache_size){
        SchemeFile.get(byte);
        CacheFile<<byte;
        counter++;
    }

}


void SchemeObjectParser::parseObject(int32_t lib_index) {

    sop::ObjectParams object_params;

    object_params.lib_index = lib_index;

    getMatrix(object_params.coord_matrix, 3, 3);

    object_params.angle = getSomeFloat(object_params.angle, types_sizes._64bits);

    object_params.state = getSomeInt(object_params.state, types_sizes._32bits);

    object_params.hard_id = getSomeInt(object_params.hard_id, types_sizes._32bits);

    object_params.is_struct_object = getBool();
    object_params.is_lib_object = getBool();
    object_params.is_struct_object = getBool();

    if(!object_params.is_lib_object){
        object_params.name_length = getSomeInt(object_params.name_length, types_sizes._32bits);
        getString(object_params.name, object_params.name_length);
    }

    object_params.hint_length = getSomeInt(object_params.hint_length, types_sizes._32bits);
    getString(object_params.hint, object_params.hint_length);
    object_params.hint_show = getBool();

    object_params.tag = getSomeInt(object_params.tag, types_sizes._32bits);

    getMatrix(object_params.contur_real_matrix, 3, 9);
    getMatrix(object_params.contur_frame_matrix, 3, 9);

    object_params.reflection_possibility = getBool();
    if(!object_params.is_lib_object){
        object_params.horizontal_reflection_mx = getBool();
        object_params.vertical_reflection_my = getBool();
    }


    object_params.normal_state = getSomeInt(object_params.normal_state, types_sizes._32bits);

    object_params.has_ts = getBool();
    object_params.invalid = getBool();

    object_params.object_type = getSomeInt(object_params.object_type, types_sizes._32bits);

    object_params.index = getSomeInt(object_params.index, types_sizes._32bits);

    if(!object_params.is_lib_object){
        object_params.index_cache = getSomeInt(object_params.index_cache, types_sizes._32bits);
    }

    object_params.show = getBool();

    object_params.button_left_active = getBool();
    object_params.button_right_active = getBool();
    object_params.buttons_swapped = getBool();

    object_params.is_animated = getBool();
    object_params.animation_speed = getSomeInt(object_params.animation_speed, types_sizes._32bits);
    object_params.hide_when_animation_stopped = getBool();

    object_params.bgcolor_not_needed = getBool();

    if(object_params.is_lib_object){
        object_params.horizontal_reflection_mx = getBool();
        object_params.vertical_reflection_my = getBool();
        object_params.has_info_for_analysis = getBool();

    }

    if(!object_params.is_lib_object){
        object_params.glue_points_amount = getSomeInt(object_params.animation_speed, types_sizes._32bits);
        getVector(object_params.glue_points_vector, object_params.glue_points_amount);

        object_params.states_amount = getSomeInt(object_params.states_amount, types_sizes._32bits);
        object_params.primitives_in_state_amount = getSomeInt(object_params.primitives_in_state_amount,
                                                              types_sizes._32bits);
    }

    if (object_params.is_struct_object)
        parseStructObject();
    else if (object_params.is_lib_object)
        parseLibObject(object_params);
//    else if (object_params.is_text_object)
//        parseText();
    else
        parsePrimitive(object_params);

}

void SchemeObjectParser::parseLibObject(sop::ObjectParams& object_params){
    CacheFile.clear();
    CacheFile.seekg(0, std::ios_base::beg);
    int32_t lib_id;
    int32_t lib_size;
    CacheFile>>lib_id;
    CacheFile>>lib_size;
    while (lib_id != object_params.lib_index) {
        CacheFile.clear();
        int32_t actual_cursor = CacheFile.tellg();
        CacheFile.seekg(actual_cursor+lib_size, std::ios_base::beg);
        CacheFile>>lib_id;
        CacheFile>>lib_size;
    }


};

void SchemeObjectParser::parsePrimitive(sop::ObjectParams& object_params) {

    sop::PrimitiveParams primitive_params;


    primitive_params.points_amount = getSomeInt(primitive_params.points_amount, types_sizes._32bits);
    getVector(primitive_params.points_vector, primitive_params.points_amount);

    primitive_params.primitive_type = getSomeInt(primitive_params.primitive_type, types_sizes._8bits);

    primitive_params.ti_style = getSomeInt(primitive_params.ti_style, types_sizes._8bits);

    getColor(primitive_params.pen_color);
    getColor(primitive_params.brush_color);
    getColor(primitive_params.trans_color);

    primitive_params.is_transparent = getBool();

    primitive_params.brush_style = getSomeInt(primitive_params.brush_style, types_sizes._8bits);
    primitive_params.pen_style = getSomeInt(primitive_params.pen_style, types_sizes._8bits);
    primitive_params.pen_width = getSomeInt(primitive_params.pen_width, types_sizes._8bits);

    primitive_params.text_length = getSomeInt(primitive_params.text_length, types_sizes._32bits);
    getString(primitive_params.text, primitive_params.text_length);

    primitive_params.style_end = getSomeInt(primitive_params.style_end, types_sizes._8bits);
    primitive_params.style_start = getSomeInt(primitive_params.style_start, types_sizes._8bits);
    primitive_params.style_frame = getSomeInt(primitive_params.style_frame, types_sizes._8bits);

    primitive_params.connect = getSomeInt(primitive_params.connect, types_sizes._8bits);

    primitive_params.is_font = getBool();

    primitive_params.line_marker_amount = getSomeInt(primitive_params.line_marker_amount, types_sizes._32bits);


    getMatrix(primitive_params.indentity_matrix, 3, 3);

    primitive_params.primitive_angle = getSomeFloat(primitive_params.primitive_angle, types_sizes._64bits);

    primitive_params.show = getBool();

    if(primitive_params.is_font){
        getFont(primitive_params);
    }

    primitive_params.is_picture = getBool();

    std::string bmp_filepath = std::string();
    if (primitive_params.is_picture){
        getPicture(primitive_params, bmp_filepath);
    }

    primitive_params.koeff = getSomeFloat(primitive_params.koeff, types_sizes._64bits);

    primitive_params.caption_length = getSomeInt(primitive_params.caption_length, types_sizes._32bits);
    getString(primitive_params.caption, primitive_params.caption_length);

    primitive_params.has_info_for_analysis = getBool();

    switch (primitive_params.primitive_type) {
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
        case objects_types.ptPicture:
            break;
        default:
            lae::PrintLog("Парсер объектов: Неизвестный тип примитива\n");
            break;
    }
}

void SchemeObjectParser::getFont(sop::PrimitiveParams &primitive_params) {
    ;
}

void SchemeObjectParser::getPicture(sop::PrimitiveParams& primitive_params, std::string& bmp_filepath) {
    ++pictures_counter;

    bmp_filepath = std::to_string(pictures_counter);

    BMP bmp;

    primitive_params.width_of_picture = getSomeInt(primitive_params.width_of_picture, types_sizes._32bits);

    primitive_params.height_of_picture = getSomeInt(primitive_params.height_of_picture, types_sizes._32bits);

    primitive_params.bit_depth = getSomeInt(primitive_params.bit_depth, types_sizes._8bits);


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