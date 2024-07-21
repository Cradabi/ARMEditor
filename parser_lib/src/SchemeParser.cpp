#include <sys/stat.h>
#include "SchemeParser.h"


bool SchemeParser::setSchemeFile(const std::string& schemefile_path)
{
    size_t filename_end_index = schemefile_path.rfind('.') + 1;
    std::string file_format_check_string = schemefile_path.substr(filename_end_index);

    if (file_format_check_string != file_format_)
    {
        lae::printLog("Парсер схемы: Неверный формат файла", true);
        return false;
    }
    schemefile_path_ = schemefile_path;

    scheme_file_.open(schemefile_path, std::ios_base::binary);

    if (!scheme_file_)
    {
        lae::printLog("Парсер схемы: Файл схемы не был открыт", true, 12);
        return false;
    }

    scheme_params_->file_path = schemefile_path;

    return true;
}

bool SchemeParser::setLogsFile()
{
    size_t filename_start_index = schemefile_path_.rfind('/') + 1;
    size_t filename_end_index = schemefile_path_.rfind('.') - 1;

    uint8_t filename_size = filename_end_index - filename_start_index + 1;

    // Get the current time
    std::time_t now = std::time(0);

    // Convert the current time to a tm struct
    std::tm* timeinfo = std::localtime(&now);

    std::string date;
    date += std::to_string(timeinfo->tm_year + 1900) + "-";
    date += std::to_string(timeinfo->tm_mon + 1) + "-";
    date += std::to_string(timeinfo->tm_mday);

    std::string dir_name = "../logs/" + date;

    mkdir(dir_name.c_str(), 0777);

    logsfile_path_ = dir_name + '/'
        + schemefile_path_.substr(filename_start_index, filename_size)
        + ".log";

    logs_file_.open(logsfile_path_);

    if (!logs_file_)
    {
        lae::printLog("Парсер схемы: Файл логов не был открыт", true, 12);
        return false;
    }

    return true;
}

void SchemeParser::setSchemeParams(Scheme::SchemeParams& scheme_params)
{
    scheme_params_ = &scheme_params;
}


bool SchemeParser::getBool(std::ifstream& file)
{
    file.get(byte_);
    return static_cast<bool>(byte_);
}

void SchemeParser::getString(std::ifstream& file, std::string& some_string, uint32_t string_size)
{
    file.read(buffer_, string_size);
    buffer_[string_size] = '\0';
    some_string = std::string(buffer_);
}

// Шаблон получения целочисленного значения из файла
template <typename IntType>
void SchemeParser::getSomeInt(std::ifstream& file, IntType& some_int, uint8_t int_size)
{
    memset(buffer_, 0, sizeof(buffer_));
    file.read(buffer_, int_size);
    some_int = *reinterpret_cast<IntType*>(buffer_);
}

// Шаблон получения числового значения с плавающей точкой из буффера
template <typename FloatType>
void SchemeParser::getSomeFloat(std::ifstream& file, FloatType& some_float, uint8_t float_size)
{
    memset(buffer_, 0, sizeof(buffer_));
    file.read(buffer_, float_size);

    if (float_size == size_._32bits)
    {
        some_float = *reinterpret_cast<float*>(buffer_);
    }
    else if (float_size == size_._64bits)
    {
        some_float = *reinterpret_cast<double*>(buffer_);
    }
}

template void SchemeParser::getSomeFloat<float>(std::ifstream& file, float& some_int, uint8_t int_size);
template void SchemeParser::getSomeFloat<double>(std::ifstream& file, double& some_int, uint8_t int_size);

template void SchemeParser::getSomeInt<int8_t>(std::ifstream& file, int8_t& some_int, uint8_t int_size);
template void SchemeParser::getSomeInt<uint8_t>(std::ifstream& file, uint8_t& some_int, uint8_t int_size);

template void SchemeParser::getSomeInt<int16_t>(std::ifstream& file, int16_t& some_int, uint8_t int_size);
template void SchemeParser::getSomeInt<uint16_t>(std::ifstream& file, uint16_t& some_int, uint8_t int_size);

template void SchemeParser::getSomeInt<int32_t>(std::ifstream& file, int32_t& some_int, uint8_t int_size);
template void SchemeParser::getSomeInt<uint32_t>(std::ifstream& file, uint32_t& some_int, uint8_t int_size);

template void SchemeParser::getSomeInt<int64_t>(std::ifstream& file, int64_t& some_int, uint8_t int_size);
template void SchemeParser::getSomeInt<uint64_t>(std::ifstream& file, uint64_t& some_int, uint8_t int_size);
