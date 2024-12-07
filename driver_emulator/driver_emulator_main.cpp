#include <QCoreApplication>
#include "lib/driver_emulator.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Создаем экземпляр эмулятора
    DriverEmulator emulator;

    // Запускаем сервер на порту 1234
    if (!emulator.startServer(3011)) {
        return -1; // Если сервер не запустился, завершаем программу
    }

    qDebug() << "Эмулятор драйвера телемеханики запущен.";
    return app.exec();
}