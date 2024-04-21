#include "pqxx/pqxx"



pqxx::result connection_to_db() {
    try {
        // Создание объекта соединения с базой данных
        pqxx::connection conn("dbname=postgres user=postgres password=20052005 hostaddr=127.0.0.1 port=5432");

        // Проверка успешности подключения
        if (conn.is_open()) {

            // Выполнение SQL-запроса
            pqxx::work txn(conn);
            pqxx::result result = txn.exec("SELECT name, current_state FROM objects");
            txn.commit();
            conn.disconnect();
            return result;

//            // Вывод данных
//            for (const auto &row : result) {
//                for (const auto &field : row) {
//                    std::cout << field.c_str() << " ";
//                }
//                std::cout << std::endl;
//            }

        } else {
            //std::cerr << "Ошибка подключения к базе данных" << std::endl;
            conn.disconnect();
            exit(1);
        }


    }
    catch (const std::exception &e) {
        //std::cerr << "Ошибка: " << e.what() << std::endl;
        exit(1);
    }

}