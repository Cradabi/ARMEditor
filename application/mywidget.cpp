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

    view->scheme_params.deleteOBJS();

    SchemeFileParser parser;
    if (!parser.parse(view->scheme_params, filepath)) {
        parser.parse(view->scheme_params, "../schemes_exp/emptyscheme.схема");
    }

    QSqlQuery db_request_result = connection_to_db();
    QSqlQuery db_request_result_cp = connection_to_cp_db();
    std::string help_text;

    for (auto object: view->scheme_params.objects_vector) {
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
                    object->set_text(db_request_result.value(3).toString().toStdString());
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
                    object->set_text(db_request_result.value(3).toString().toStdString());
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
                    object->set_text(db_request_result.value(3).toString().toStdString());
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

    this->setFixedSize(view->scheme_params.width, view->scheme_params.height);

    view->resize(view->scheme_params.width, view->scheme_params.height);
    layout->addWidget(view);

    QPixmap pix(view->scheme_params.width, view->scheme_params.height);
    QColor bgColor = {view->scheme_params.bgColor.red, view->scheme_params.bgColor.green, view->scheme_params.bgColor.blue};
    pix.fill(bgColor);

    QPainter *painter = new QPainter(&pix);

    Scheme scheme(view->scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);
}

