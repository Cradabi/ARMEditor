#include "SchemeFileParser.h"

bool SchemeFileParser::parse(Scheme::SchemeParams& scheme_params, const std::string& schemefile_path)
{

    lae::printLog("Парсер начал работу", true);

    setSchemeParams(scheme_params);

    if (!setSchemeFile(schemefile_path))
        return false;

    if (!setLogsFile())
        return false;

    SchemeSectionsParser::parse();

    // Закрываем файлы
    scheme_file_.close();
    logs_file_.close();

    lae::printLog("Парсер схемы: Парсер отработал", true, 2);

    return true;
}

// Функция получения размера файла
void SchemeFileParser::getFileSize()
{
    scheme_file_.seekg(0, std::ios::end); // Курсор ставится в конец файла
    file_size_ = scheme_file_.tellg(); // Записывается позиция курсора

    scheme_file_.clear(); // С файла сбрасываются возможные ошибки чтения
    scheme_file_.seekg(0, std::ios::beg); // Курсор возвращается в начало файла

    lae::printLog("Размер файла схемы: ", false, 2);
    lae::printLog(file_size_, false, 2);
    lae::printLog(" байт", true, 2);

    lae::writeLog(logs_file_, "\nFile size: ");
    lae::writeLog(logs_file_, file_size_);
    lae::writeLog(logs_file_, " bytes\n", true);
}

