#include "mywidget.h"

#include "parser_lib/SchemeFileParser.h"
#include "db_lib/db_connection.h"



MyWidget::MyWidget()
{
    // layout = new QVBoxLayout(this);
    // scene = new QGraphicsScene(this);
    // view = new MyView(scene);
    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    db_request_result_actual = connection_to_db();
    db_request_result_cp_actual = connection_to_cp_db();

    draw_new_scheme("../schemes_exp/emptyscheme.схема");
}

void MyWidget::draw_new_scheme(const std::string& filepath)
{
    if (view != nullptr)
    {
        delete layout;
        delete scene;
        delete view;
    }

    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new MyView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->scheme_params.deleteOBJS();

    SchemeFileParser parser;
    if (!parser.parse(view->scheme_params, filepath))
    {
        parser.parse(view->scheme_params, "../schemes_exp/emptyscheme.схема");
    }

    make_bd_objects();

    startThread();

    this->setFixedSize(view->scheme_params.width, view->scheme_params.height);

    view->resize(view->scheme_params.width, view->scheme_params.height);
    layout->addWidget(view);

    QPixmap pix(view->scheme_params.width, view->scheme_params.height);
    QColor bgColor = {
        view->scheme_params.bgColor.red, view->scheme_params.bgColor.green, view->scheme_params.bgColor.blue
    };
    pix.fill(bgColor);

    QPainter* painter = new QPainter(&pix);

    Scheme scheme(view->scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);
}


void MyWidget::make_bd_objects()
{
    for (auto object : view->scheme_params.objects_vector)
    {
        if (object->get_id())
        {
            view->bd_objects[object->get_id()] = object;
        }
    }
}
