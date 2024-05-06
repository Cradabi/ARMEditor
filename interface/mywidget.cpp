#include "mywidget.h"


#include "parser_lib/SchemeFileParser.h"
#include "db_lib/db_connection.h"

MyWidget::MyWidget() {
    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new MyView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    draw_new_scheme("../schemes_exp/emptyscheme.схема");
}

void MyWidget::draw_new_scheme(const std::string &filepath) {
    delete layout;
    delete scene;
    delete view;

    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new MyView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Scheme::SchemeParams tmp_scheme_params;


    SchemeFileParser parser(tmp_scheme_params);
    if (!parser.parse(filepath)) {
        parser.parse("../schemes_exp/emptyscheme.схема");
    }

    QSqlQuery db_request_result = connection_to_db();
    QSqlQuery db_request_result_cp = connection_to_cp_db();
    std::string help_text;

    for (auto object: tmp_scheme_params.objects_vector) {
        if (object->get_type_object() == "Библиотечный объект") {
            while (db_request_result.next()) {
                if (db_request_result.value(0).toInt() == object->get_id()) {
                    object->set_condition(db_request_result.value(2).toInt());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt()) {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result.seek(0);
            db_request_result_cp.seek(0);
        } else if (object->get_type_object() == "Телеизмерение") {
            while (db_request_result.next()) {
                if (db_request_result.value(0).toInt() == object->get_id()) {
                    object->set_condition(db_request_result.value(3).toInt());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt()) {
                            std::string cur_value = db_request_result.value(4).toString().toStdString();
                            object->set_text(cur_value);

                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result.seek(0);
            db_request_result_cp.seek(0);
        } else if (object->get_type_object() == "Телеконтроль") {
            while (db_request_result.next()) {
                if (db_request_result.value(0).toInt() == object->get_id()) {
                    object->set_condition(db_request_result.value(3).toInt());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt()) {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result.seek(0);
            db_request_result_cp.seek(0);
        } else if (object->get_type_object() == "Телесигнализация") {
            while (db_request_result.next()) {
                if (db_request_result.value(0).toInt() == object->get_id()) {
                    object->set_condition(db_request_result.value(3).toInt());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt()) {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result.seek(0);
            db_request_result_cp.seek(0);
        }

    }
    //QVector<Primitive*> vector_obj = tmp_scheme_params.objects_vector;

    QVector<QVector<QVariant>> qtVector = {};
    QVector<QVariant> cur_vec = {};
    QString qString = "";
    for(auto object: tmp_scheme_params.objects_vector) {
        cur_vec.append(object->get_x());
        cur_vec.append(object->get_y());
        cur_vec.append(object->get_width());
        cur_vec.append(object->get_height());
        cur_vec.append(object->get_angle());
        cur_vec.append(object->get_id());
        qString = QString::fromStdString(object->get_text());
        cur_vec.append(qString);
        qString = QString::fromStdString(object->get_type_object());
        cur_vec.append(qString);
        qtVector.append(cur_vec);
        cur_vec = {};
    }

   //ткрываем файл для записи
    QFile file("/home/chekhov/github/ARMEditor/interface/save.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Не удалось открыть файл для записи";
        exit(0);
    }

    // Записываем QVector в файл
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_11);
    out << qtVector;

    file.close();

    this->setFixedSize(tmp_scheme_params.width, tmp_scheme_params.height);

    view->resize(tmp_scheme_params.width, tmp_scheme_params.height);
    layout->addWidget(view);

    QPixmap pix(tmp_scheme_params.width, tmp_scheme_params.height);
    QColor bgColor = {tmp_scheme_params.bgColor.red, tmp_scheme_params.bgColor.green, tmp_scheme_params.bgColor.blue};
    pix.fill(bgColor);

    QPainter *painter = new QPainter(&pix);

    Scheme scheme(tmp_scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);
}

