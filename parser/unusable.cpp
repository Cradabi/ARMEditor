data_type = static_cast<uint8_t>(byte);

// Далее идет кол-во параметров схемы/объекта этого типа данных, если = 0, значит ничего не будет
// если >2 (3 и более) значит что-то пошло не так, нужно смотреть
//            SchemeFile.get(byte);
//            ++bytes_counter;
//            objects_amount = static_cast<uint8_t>(byte)

std::bitset<8> print_byte;

int32_t tmp_int = 0;
uint8_t tmp_byte = 0;
switch (data_type) {
case scheme_data_types.dtUnknown:
lae::WriteLog(LogsFile, "Unknown", true);
lae::WriteLog(LogsFile, byte);
lae::WriteLog(LogsFile, " : ");
print_byte = byte;
lae::WriteLog(LogsFile, print_byte, true);
break;
case scheme_data_types.dtInteger:
lae::WriteLog(LogsFile, "Integer: ", true);
tmp_int = GetSomeInt(tmp_int, 2);
lae::WriteLog(LogsFile, tmp_int, true);
bytes_counter += 2;
break;
case scheme_data_types.dtFloat:
lae::WriteLog(LogsFile, "Float: ", true);
break;
case scheme_data_types.dtPoint:
lae::WriteLog(LogsFile, "Point: ", true);
break;
case scheme_data_types.dtFont:
lae::WriteLog(LogsFile, "Font: ", true);
break;
case scheme_data_types.dtByte:
lae::WriteLog(LogsFile, "Byte: ", true);
tmp_byte = GetSomeInt(tmp_byte, 1);
lae::WriteLog(LogsFile, tmp_byte, true);
bytes_counter += 1;
break;
case scheme_data_types.dtRectangle:
lae::WriteLog(LogsFile, "Rectangle: ", true);
break;
case scheme_data_types.dtString:
lae::WriteLog(LogsFile, "String: ", true);
break;
case scheme_data_types.dtList:
lae::WriteLog(LogsFile, "List: ", true);
break;
case scheme_data_types.dtObject:
lae::WriteLog(LogsFile, "Object: ", true);
break;
case scheme_data_types.dtRecord:
lae::WriteLog(LogsFile, "Record: ", true);
break;
case scheme_data_types.dtElement:
lae::WriteLog(LogsFile, "Element: ", true);
break;
case scheme_data_types.dtLibraryObject:
lae::WriteLog(LogsFile, "LibraryObject: ", true);
break;
case scheme_data_types.dtLibrary:
lae::WriteLog(LogsFile, "Library: ", true);
break;
case scheme_data_types.dtBitmap:
lae::WriteLog(LogsFile, "Bitmap: ", true);
break;
case scheme_data_types.dtJPEGImage:
lae::WriteLog(LogsFile, "JPEGImage: ", true);
break;
default:
lae::WriteLog(LogsFile, byte);
lae::WriteLog(LogsFile, " : ");
print_byte = byte;
lae::WriteLog(LogsFile, print_byte, true);
break;
}
lae::WriteLog(LogsFile, byte);
lae::WriteLog(LogsFile, " : ");
print_byte = byte;
lae::WriteLog(LogsFile, print_byte, true);