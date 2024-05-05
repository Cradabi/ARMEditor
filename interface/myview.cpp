#include "myview.h"

void MyView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos().x() << " " << event->pos().y();
        QPoint originalpoint(event->pos().x(), event->pos().y());

        // for (auto object : current_scheme_params.objects_vector)
        // {
        //     std::string tp_obj = object->get_type_object();
        //     if (tp_obj == "Библиотечный объект")
        //     {
        //         ;
        //     }else if (tp_obj == "Телеизмерение")
        //     {
        //         ;
        //     }else if (tp_obj == "Телеконтроль")
        //     {
        //         ;
        //     }else if (tp_obj == "Телесигнализация")
        //     {
        //         ;
        //     }
        // }

        QMenu *newWindow = new QMenu();

        int xOffset = 20;
        int yOffset = -20;
        newWindow->move(event->pos().x() + xOffset, event->pos().y() + yOffset);

        QVBoxLayout *mainLayout = new QVBoxLayout(newWindow);

        QHBoxLayout *row1Layout = new QHBoxLayout();
        QLabel *label1 = new QLabel("Label 1:");
        QLineEdit *lineEdit1 = new QLineEdit();
        row1Layout->addWidget(label1);
        row1Layout->addWidget(lineEdit1);

        QHBoxLayout *row2Layout = new QHBoxLayout();
        QLabel *label2 = new QLabel("Label 2:");
        QLineEdit *lineEdit2 = new QLineEdit();
        row2Layout->addWidget(label2);
        row2Layout->addWidget(lineEdit2);

        QPushButton *saveButton = new QPushButton("&Сохранить");

        mainLayout->addLayout(row1Layout);
        mainLayout->addLayout(row2Layout);
        mainLayout->addWidget(saveButton);

        newWindow->show();
    }
}