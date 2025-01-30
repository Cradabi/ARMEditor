#include "MainWidget.h"
#include "parser_lib/SchemeFileParser.h"
#include "db_lib/DBManager.h"

void MainWidget::updateDB()
{
    if (!view->scheme_params.objects_vector.size())
        return;

    db_request_result_previous = db_request_result_actual;

    db_request_result_actual = DBManager::getInstance().getObjects();

    FiguresClasses::Primitive* cur_prim;

    while (db_request_result_actual.next())
    {
        int objectId = db_request_result_actual.value(0).toInt();
        if (view->bd_objects.find(objectId) != view->bd_objects.end())
        {
            cur_prim = view->bd_objects[objectId];
            if (cur_prim->get_type_object() == "Библиотечный объект")
            {
                int currentState = db_request_result_actual.value(2).toInt();
                if(currentState >= 0)
                {
                    cur_prim->set_condition(currentState);
                }
                else
                {
                    DBManager::getInstance().updateLibraryState(0, objectId);
                    cur_prim->set_condition(0);
                }
            }
            else if (cur_prim->get_type_object() == "Телеизмерение")
            {
                cur_prim->set_text(db_request_result_actual.value(3).toString().toStdString());
            }
        }
    }

    updateScene();
}

MainWidget::MainWidget(MainWindow *_main_window)
    : main_window(_main_window)
{
    db_request_result_actual = DBManager::getInstance().getObjects();
    db_request_result_cp_actual = DBManager::getInstance().getCPObjects();

    draw_new_scheme("../schemes_exp/emptyscheme.схема");
}

void MainWidget::draw_new_scheme(const std::string& filepath)
{
    if (view != nullptr)
    {
        delete layout;
        delete scene;
        delete view;
    }

    layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new MainView(scene, main_window);
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

    updateScene();
}

void MainWidget::make_bd_objects()
{
    for (auto object : view->scheme_params.objects_vector)
    {
        if (object->get_id())
        {
            view->bd_objects[object->get_id()] = object;
        }
    }
}

void MainWidget::startThread()
{
    emit updateDB();
    if (m_thread)
    {
        stopThread();
    }

    m_thread = new QThread(this);
    m_timer = new QTimer();
    m_timer->moveToThread(m_thread);

    connect(m_thread, &QThread::started, m_timer, [=]()
    {
        m_timer->start(60000);
    });

    connect(m_timer, &QTimer::timeout, this, &MainWidget::updateDB);
    connect(this, &MainWidget::stopTimerSignal, this, &MainWidget::stopTimerAndDelete);

    m_thread->start();
}

void MainWidget::stopThread()
{
    emit stopTimerSignal();
}

void MainWidget::stopTimerAndDelete() {
    if (m_timer) {
        m_timer->stop();
        delete m_timer;
        m_timer = nullptr;
    }
    if (m_thread) {
        m_thread->quit();
        m_thread->wait();
        delete m_thread;
        m_thread = nullptr;
    }
}

void MainWidget::updateScene()
{
    QPixmap pix(view->scheme_params.width, view->scheme_params.height);
    QColor bgColor = {
        view->scheme_params.bgColor.red, view->scheme_params.bgColor.green, view->scheme_params.bgColor.blue
    };
    pix.fill(bgColor);

    QPainter* painter = new QPainter(&pix);

    Scheme scheme(view->scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->clear();
    scene->addPixmap(pix);
}