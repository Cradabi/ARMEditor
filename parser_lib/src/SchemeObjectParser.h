#pragma once

#include <cmath>
#include <bitset>

#include "SchemeFileNS.h"
#include "SchemeParser.h"
#include "../primitives_lib/SchemeClass.h"
#include "../bmp_additional/BMPFile.h"

#include "QDebug"

using namespace FiguresClasses;

class SchemeObjectParser : public SchemeParser
{
    const std::string cachefile_path_ = "../parser_lib/cache/tmp.cache";
    std::ofstream CacheFileOut; // Файл для временного хранения кеша объектов
    std::ifstream CacheFileIn; // Файл для временного хранения кеша объектов
    bool is_cache_open{false};

    uint32_t pictures_counter{0};

    std::vector<Primitive*> group_objects_vector_;

    // Функция получения цвета
    void getColor(std::ifstream& File, sop::BGRColor& color, bool is_buffer_filled = false);

    void getMatrix(std::ifstream& File, std::vector<std::vector<double>>& some_matrix, uint8_t size_y, uint8_t size_x);

    void getVector(std::ifstream& File, std::vector<sop::Point>& some_vector, uint8_t vector_size);

    void getFont(std::ifstream& File, sop::PrimitiveParams& primitive_params);

    void getPicture(std::ifstream& File, sop::PrimitiveParams& primitive_params, std::string& bmp_filepath);

    void parseObject(std::ifstream& File, int32_t lib_index, int32_t nesting_level);

    void parseGroup(std::ifstream& File, int32_t nesting_level);

    void getButtonsInfo(std::ifstream& File, sop::ObjectParams& object_params);

    void getAnimationInfo(std::ifstream& File, sop::ObjectParams& object_params);

    void rewriteCacheObject(int32_t lib_index, int32_t cache_size);

    void parsePrimitiveCommonFields(std::ifstream& File, sop::PrimitiveParams& primitive_params);

    void parsePrimitive(std::ifstream& File, sop::ObjectParams& object_params);

    //  void parseTextObject();

    //  void parseStructObject() {};

    void parseLibObject(std::ifstream& File, sop::ObjectParams& object_params);

    void writeFontInfo(const sop::PrimitiveParams& primitive_params);

    void writeObjectInfo(const sop::ObjectParams& object_params);

    void writePrimitiveParams(const sop::PrimitiveParams& primitive_params);

protected:
    SchemeObjectParser()
    {
        CacheFileOut.open(cachefile_path_, std::ofstream::out | std::ios_base::trunc);
        CacheFileOut.close();
    }

    ~SchemeObjectParser() = default;

    // Главная функция парсера объектов
    bool parse(int32_t lib_index, bool is_object = false, int32_t nasting_level = 1,
               bool is_cache = false, int32_t cache_size = 0)
    {

        // lae::printLog("Парсер объектов: начал работу", true);
        // qDebug() << "Парсер объектов: начал работу";

        if (!is_cache)
        {
            if (!is_object)
            {
                // lae::printLog("Парсер объектов: читаю группу... ");
                // qDebug() << "Парсер объектов: читаю группу... ";
                parseGroup(scheme_file_, nasting_level);
                // lae::printLog("ОК", true);
                // qDebug() << "OK";
            }
            else
            {
                // lae::printLog("Парсер объектов: читаю объект... ");
                // qDebug() << "Парсер объектов: читаю объект... ";
                parseObject(scheme_file_, lib_index, nasting_level);
               // lae::printLog("ОК", true);
               // qDebug() << "OK";
            }
        }
        else
        {
            // lae::printLog("Парсер объектов: читаю кэш... ");
            // qDebug() << "Парсер объектов: читаю кэш... ";
            CacheFileOut.open(cachefile_path_, std::ios_base::binary | std::ios_base::app);
            rewriteCacheObject(lib_index, cache_size);
            // lae::printLog("ОК", true);
           // Debug() << "OK";
        }

        CacheFileOut.close();
        CacheFileIn.close();

        // lae::printLog("Парсер объектов: отработал", true);

        // qDebug() << "Парсер объектов: отработал";

        return true;
    }
};
