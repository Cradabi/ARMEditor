/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_create;
    QAction *action_open;
    QAction *action_save;
    QAction *action_save_as;
    QAction *action_export_metafile;
    QAction *action_export_xml;
    QAction *action_preview;
    QAction *action_print_xml;
    QAction *action_exit;
    QAction *action_cancel;
    QAction *action_repeat;
    QAction *action_cut;
    QAction *action_copy;
    QAction *action_paste;
    QAction *action_paste_here;
    QAction *action_duplicate;
    QAction *action_find;
    QAction *action_select_all;
    QAction *action_align_left;
    QAction *action_align_right;
    QAction *action_align_horizontal_center;
    QAction *action_align_up;
    QAction *action_align_down;
    QAction *action_align_vertical_center;
    QAction *action_align_by_widest;
    QAction *action_align_by_tighest;
    QAction *action_tallest;
    QAction *action_lowest;
    QAction *action_binding_mode;
    QAction *action_ruler;
    QAction *action_inspector;
    QAction *action_connect_to_database;
    QAction *action_objects_repository;
    QAction *action_statistics;
    QAction *action_set_scheme;
    QAction *action_clean_scheme;
    QAction *action_relocate;
    QAction *action_offset_transition_numbers;
    QAction *action_check_animation_transitions;
    QAction *action_copy_as_picture;
    QAction *action_set_info_cedp;
    QAction *action_give_info_cedp;
    QAction *action_set_objects;
    QAction *action_set_editor;
    QAction *action_reference;
    QAction *action_about_program;
    QAction *action1_2;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line;
    QPushButton *pushButton_close;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *line_2;
    QListView *listView;
    QMenuBar *menubar;
    QMenu *menu_file;
    QMenu *menu_recently_opened_files;
    QMenu *menu_edit;
    QMenu *menu_align_objects;
    QMenu *menu_align_sizes;
    QMenu *menu_view;
    QMenu *menu_scheme;
    QMenu *menu_service_functions;
    QMenu *menu_service;
    QMenu *menu_reference;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 840);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        action_create = new QAction(MainWindow);
        action_create->setObjectName(QStringLiteral("action_create"));
        action_open = new QAction(MainWindow);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_save = new QAction(MainWindow);
        action_save->setObjectName(QStringLiteral("action_save"));
        action_save_as = new QAction(MainWindow);
        action_save_as->setObjectName(QStringLiteral("action_save_as"));
        action_export_metafile = new QAction(MainWindow);
        action_export_metafile->setObjectName(QStringLiteral("action_export_metafile"));
        action_export_xml = new QAction(MainWindow);
        action_export_xml->setObjectName(QStringLiteral("action_export_xml"));
        action_preview = new QAction(MainWindow);
        action_preview->setObjectName(QStringLiteral("action_preview"));
        action_print_xml = new QAction(MainWindow);
        action_print_xml->setObjectName(QStringLiteral("action_print_xml"));
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        action_cancel = new QAction(MainWindow);
        action_cancel->setObjectName(QStringLiteral("action_cancel"));
        action_repeat = new QAction(MainWindow);
        action_repeat->setObjectName(QStringLiteral("action_repeat"));
        action_cut = new QAction(MainWindow);
        action_cut->setObjectName(QStringLiteral("action_cut"));
        action_copy = new QAction(MainWindow);
        action_copy->setObjectName(QStringLiteral("action_copy"));
        action_paste = new QAction(MainWindow);
        action_paste->setObjectName(QStringLiteral("action_paste"));
        action_paste_here = new QAction(MainWindow);
        action_paste_here->setObjectName(QStringLiteral("action_paste_here"));
        action_duplicate = new QAction(MainWindow);
        action_duplicate->setObjectName(QStringLiteral("action_duplicate"));
        action_find = new QAction(MainWindow);
        action_find->setObjectName(QStringLiteral("action_find"));
        action_select_all = new QAction(MainWindow);
        action_select_all->setObjectName(QStringLiteral("action_select_all"));
        action_align_left = new QAction(MainWindow);
        action_align_left->setObjectName(QStringLiteral("action_align_left"));
        action_align_right = new QAction(MainWindow);
        action_align_right->setObjectName(QStringLiteral("action_align_right"));
        action_align_horizontal_center = new QAction(MainWindow);
        action_align_horizontal_center->setObjectName(QStringLiteral("action_align_horizontal_center"));
        action_align_up = new QAction(MainWindow);
        action_align_up->setObjectName(QStringLiteral("action_align_up"));
        action_align_down = new QAction(MainWindow);
        action_align_down->setObjectName(QStringLiteral("action_align_down"));
        action_align_vertical_center = new QAction(MainWindow);
        action_align_vertical_center->setObjectName(QStringLiteral("action_align_vertical_center"));
        action_align_by_widest = new QAction(MainWindow);
        action_align_by_widest->setObjectName(QStringLiteral("action_align_by_widest"));
        action_align_by_tighest = new QAction(MainWindow);
        action_align_by_tighest->setObjectName(QStringLiteral("action_align_by_tighest"));
        action_tallest = new QAction(MainWindow);
        action_tallest->setObjectName(QStringLiteral("action_tallest"));
        action_lowest = new QAction(MainWindow);
        action_lowest->setObjectName(QStringLiteral("action_lowest"));
        action_binding_mode = new QAction(MainWindow);
        action_binding_mode->setObjectName(QStringLiteral("action_binding_mode"));
        action_ruler = new QAction(MainWindow);
        action_ruler->setObjectName(QStringLiteral("action_ruler"));
        action_inspector = new QAction(MainWindow);
        action_inspector->setObjectName(QStringLiteral("action_inspector"));
        action_connect_to_database = new QAction(MainWindow);
        action_connect_to_database->setObjectName(QStringLiteral("action_connect_to_database"));
        action_objects_repository = new QAction(MainWindow);
        action_objects_repository->setObjectName(QStringLiteral("action_objects_repository"));
        action_statistics = new QAction(MainWindow);
        action_statistics->setObjectName(QStringLiteral("action_statistics"));
        action_set_scheme = new QAction(MainWindow);
        action_set_scheme->setObjectName(QStringLiteral("action_set_scheme"));
        action_clean_scheme = new QAction(MainWindow);
        action_clean_scheme->setObjectName(QStringLiteral("action_clean_scheme"));
        action_relocate = new QAction(MainWindow);
        action_relocate->setObjectName(QStringLiteral("action_relocate"));
        action_offset_transition_numbers = new QAction(MainWindow);
        action_offset_transition_numbers->setObjectName(QStringLiteral("action_offset_transition_numbers"));
        action_check_animation_transitions = new QAction(MainWindow);
        action_check_animation_transitions->setObjectName(QStringLiteral("action_check_animation_transitions"));
        action_copy_as_picture = new QAction(MainWindow);
        action_copy_as_picture->setObjectName(QStringLiteral("action_copy_as_picture"));
        action_set_info_cedp = new QAction(MainWindow);
        action_set_info_cedp->setObjectName(QStringLiteral("action_set_info_cedp"));
        action_give_info_cedp = new QAction(MainWindow);
        action_give_info_cedp->setObjectName(QStringLiteral("action_give_info_cedp"));
        action_set_objects = new QAction(MainWindow);
        action_set_objects->setObjectName(QStringLiteral("action_set_objects"));
        action_set_editor = new QAction(MainWindow);
        action_set_editor->setObjectName(QStringLiteral("action_set_editor"));
        action_reference = new QAction(MainWindow);
        action_reference->setObjectName(QStringLiteral("action_reference"));
        action_about_program = new QAction(MainWindow);
        action_about_program->setObjectName(QStringLiteral("action_about_program"));
        action1_2 = new QAction(MainWindow);
        action1_2->setObjectName(QStringLiteral("action1_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 1251, 761));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        line = new QFrame(verticalLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        pushButton_close = new QPushButton(verticalLayoutWidget);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        sizePolicy1.setHeightForWidth(pushButton_close->sizePolicy().hasHeightForWidth());
        pushButton_close->setSizePolicy(sizePolicy1);
        pushButton_close->setMaximumSize(QSize(20, 20));

        horizontalLayout_3->addWidget(pushButton_close);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        scrollArea = new QScrollArea(verticalLayoutWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1020, 717));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        line_2 = new QFrame(verticalLayoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        listView = new QListView(verticalLayoutWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(listView);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 30));
        menubar->setNativeMenuBar(true);
        menu_file = new QMenu(menubar);
        menu_file->setObjectName(QStringLiteral("menu_file"));
        menu_file->setTearOffEnabled(false);
        menu_file->setToolTipsVisible(false);
        menu_recently_opened_files = new QMenu(menu_file);
        menu_recently_opened_files->setObjectName(QStringLiteral("menu_recently_opened_files"));
        menu_edit = new QMenu(menubar);
        menu_edit->setObjectName(QStringLiteral("menu_edit"));
        menu_align_objects = new QMenu(menu_edit);
        menu_align_objects->setObjectName(QStringLiteral("menu_align_objects"));
        menu_align_sizes = new QMenu(menu_edit);
        menu_align_sizes->setObjectName(QStringLiteral("menu_align_sizes"));
        menu_view = new QMenu(menubar);
        menu_view->setObjectName(QStringLiteral("menu_view"));
        menu_scheme = new QMenu(menubar);
        menu_scheme->setObjectName(QStringLiteral("menu_scheme"));
        menu_service_functions = new QMenu(menu_scheme);
        menu_service_functions->setObjectName(QStringLiteral("menu_service_functions"));
        menu_service = new QMenu(menubar);
        menu_service->setObjectName(QStringLiteral("menu_service"));
        menu_reference = new QMenu(menubar);
        menu_reference->setObjectName(QStringLiteral("menu_reference"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_file->menuAction());
        menubar->addAction(menu_edit->menuAction());
        menubar->addAction(menu_view->menuAction());
        menubar->addAction(menu_scheme->menuAction());
        menubar->addAction(menu_service->menuAction());
        menubar->addAction(menu_reference->menuAction());
        menu_file->addAction(action_create);
        menu_file->addAction(action_open);
        menu_file->addSeparator();
        menu_file->addAction(action_save);
        menu_file->addAction(action_save_as);
        menu_file->addSeparator();
        menu_file->addAction(action_export_metafile);
        menu_file->addAction(action_export_xml);
        menu_file->addSeparator();
        menu_file->addAction(action_preview);
        menu_file->addAction(action_print_xml);
        menu_file->addSeparator();
        menu_file->addAction(menu_recently_opened_files->menuAction());
        menu_file->addSeparator();
        menu_file->addAction(action_exit);
        menu_recently_opened_files->addAction(action1_2);
        menu_edit->addAction(action_cancel);
        menu_edit->addAction(action_repeat);
        menu_edit->addSeparator();
        menu_edit->addAction(action_cut);
        menu_edit->addAction(action_copy);
        menu_edit->addAction(action_paste);
        menu_edit->addAction(action_paste_here);
        menu_edit->addAction(action_duplicate);
        menu_edit->addAction(action_find);
        menu_edit->addSeparator();
        menu_edit->addAction(action_select_all);
        menu_edit->addSeparator();
        menu_edit->addAction(menu_align_objects->menuAction());
        menu_edit->addAction(menu_align_sizes->menuAction());
        menu_align_objects->addAction(action_align_left);
        menu_align_objects->addAction(action_align_right);
        menu_align_objects->addAction(action_align_horizontal_center);
        menu_align_objects->addSeparator();
        menu_align_objects->addAction(action_align_up);
        menu_align_objects->addAction(action_align_down);
        menu_align_objects->addAction(action_align_vertical_center);
        menu_align_sizes->addAction(action_align_by_widest);
        menu_align_sizes->addAction(action_align_by_tighest);
        menu_align_sizes->addAction(action_tallest);
        menu_align_sizes->addAction(action_lowest);
        menu_view->addAction(action_binding_mode);
        menu_view->addAction(action_ruler);
        menu_view->addSeparator();
        menu_view->addAction(action_inspector);
        menu_scheme->addAction(action_connect_to_database);
        menu_scheme->addSeparator();
        menu_scheme->addAction(action_objects_repository);
        menu_scheme->addAction(action_statistics);
        menu_scheme->addAction(menu_service_functions->menuAction());
        menu_scheme->addSeparator();
        menu_scheme->addAction(action_set_scheme);
        menu_service_functions->addAction(action_clean_scheme);
        menu_service_functions->addSeparator();
        menu_service_functions->addAction(action_relocate);
        menu_service_functions->addAction(action_offset_transition_numbers);
        menu_service_functions->addSeparator();
        menu_service_functions->addAction(action_check_animation_transitions);
        menu_service_functions->addSeparator();
        menu_service_functions->addAction(action_copy_as_picture);
        menu_service_functions->addSeparator();
        menu_service_functions->addAction(action_set_info_cedp);
        menu_service_functions->addAction(action_give_info_cedp);
        menu_service->addAction(action_set_objects);
        menu_service->addSeparator();
        menu_service->addAction(action_set_editor);
        menu_reference->addAction(action_reference);
        menu_reference->addSeparator();
        menu_reference->addAction(action_about_program);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_create->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        action_open->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        action_save->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        action_save_as->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", nullptr));
        action_export_metafile->setText(QApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 \320\274\320\265\321\202\320\260\321\204\320\260\320\271\320\273...", nullptr));
        action_export_xml->setText(QApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202 \320\262 XML...", nullptr));
        action_preview->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\262\320\260\321\200\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \320\277\321\200\320\276\321\201\320\274\320\276\321\202\321\200", nullptr));
        action_print_xml->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\207\320\260\321\202\321\214 XML", nullptr));
        action_exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        action_cancel->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        action_repeat->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214", nullptr));
        action_cut->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\200\320\265\320\267\320\260\321\202\321\214", nullptr));
        action_copy->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        action_paste->setText(QApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
        action_paste_here->setText(QApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \320\267\320\264\320\265\321\201\321\214", nullptr));
        action_duplicate->setText(QApplication::translate("MainWindow", "\320\224\321\203\320\261\320\273\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        action_find->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270/\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214...", nullptr));
        action_select_all->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\264\320\265\320\273\320\270\321\202\321\214 \320\262\321\201\320\265", nullptr));
        action_align_left->setText(QApplication::translate("MainWindow", "\320\237\320\276 \320\273\320\265\320\262\320\276\320\274\321\203 \320\272\321\200\320\260\321\216", nullptr));
        action_align_right->setText(QApplication::translate("MainWindow", "\320\237\320\276 \320\277\321\200\320\260\320\262\320\276\320\274\321\203 \320\272\321\200\320\260\321\216", nullptr));
        action_align_horizontal_center->setText(QApplication::translate("MainWindow", "\320\237\320\276 \321\201\320\265\321\200\320\265\320\264\320\270\320\275\320\265", nullptr));
        action_align_up->setText(QApplication::translate("MainWindow", "\320\237\320\276 \320\262\320\265\321\200\321\205\320\275\320\265\320\274\321\203 \320\272\321\200\320\260\321\216", nullptr));
        action_align_down->setText(QApplication::translate("MainWindow", "\320\237\320\276 \320\275\320\270\320\266\320\275\320\265\320\274\321\203 \320\272\321\200\320\260\321\216", nullptr));
        action_align_vertical_center->setText(QApplication::translate("MainWindow", "\320\237\320\276 \321\206\320\265\320\275\321\202\321\200\321\203", nullptr));
        action_align_by_widest->setText(QApplication::translate("MainWindow", "\320\237\320\276 \321\201\320\260\320\274\320\276\320\274\321\203 \321\210\320\270\321\200\320\276\320\272\320\276\320\274\321\203", nullptr));
        action_align_by_tighest->setText(QApplication::translate("MainWindow", "\320\237\320\276 \321\201\320\260\320\274\320\276\320\274\321\203 \321\203\320\267\320\272\320\276\320\274\321\203", nullptr));
        action_tallest->setText(QApplication::translate("MainWindow", "\320\237\320\276 \321\201\320\260\320\274\320\276\320\274\321\203 \320\262\321\213\321\201\320\276\320\272\320\276\320\274\321\203", nullptr));
        action_lowest->setText(QApplication::translate("MainWindow", "\320\237\320\276 \321\201\320\260\320\274\320\276\320\274\321\203 \320\275\320\270\320\267\320\272\320\276\320\274\321\203", nullptr));
        action_binding_mode->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274 \320\277\321\200\320\270\320\262\321\217\320\267\320\272\320\270", nullptr));
        action_ruler->setText(QApplication::translate("MainWindow", "\320\233\320\270\320\275\320\265\320\271\320\272\320\260", nullptr));
        action_inspector->setText(QApplication::translate("MainWindow", "\320\230\320\275\321\201\320\277\320\265\320\272\321\202\320\276\321\200 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", nullptr));
        action_connect_to_database->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\272 \320\261\320\260\320\267\320\265 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        action_objects_repository->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\277\320\276\320\267\320\270\321\202\320\276\321\200\320\270\320\271 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", nullptr));
        action_statistics->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        action_set_scheme->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\201\321\205\320\265\320\274\321\213", nullptr));
        action_clean_scheme->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260 \321\201\321\205\320\265\320\274\321\213", nullptr));
        action_relocate->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\265\321\201\321\202\320\270...", nullptr));
        action_offset_transition_numbers->setText(QApplication::translate("MainWindow", "\320\241\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\275\320\276\320\274\320\265\321\200\320\276\320\262 \320\277\320\265\321\200\320\265\321\205\320\276\320\264\320\276\320\262", nullptr));
        action_check_animation_transitions->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260 \320\277\321\200\320\270\320\262\321\217\320\267\320\272\320\270 \320\260\320\275\320\270\320\274\320\260\321\206\320\270\320\270", nullptr));
        action_copy_as_picture->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\320\272 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\321\203", nullptr));
        action_set_info_cedp->setText(QApplication::translate("MainWindow", "\320\241\321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\216 \320\276 \320\272\321\200\321\203\320\263\320\265 \320\264\320\273\321\217 \320\246\320\255\320\224\320\237", nullptr));
        action_give_info_cedp->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\264\320\260\321\202\321\214 \320\270\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\216 \320\276 \320\272\321\200\321\203\320\263\320\265 \320\262 \320\246\320\255\320\224\320\237", nullptr));
        action_set_objects->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262", nullptr));
        action_set_editor->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200\320\260", nullptr));
        action_reference->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        action_about_program->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        action1_2->setText(QApplication::translate("MainWindow", "1", nullptr));
        pushButton_close->setText(QApplication::translate("MainWindow", ">", nullptr));
        menu_file->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        menu_recently_opened_files->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\275\320\264\320\260\320\262\320\275\320\276 \320\276\321\202\320\272\321\200\321\213\321\202\321\213\321\205 \321\204\320\260\320\271\320\273\320\276\320\262", nullptr));
        menu_edit->setTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
        menu_align_objects->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\321\200\320\276\320\262\320\275\321\217\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202\321\213", nullptr));
        menu_align_sizes->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\321\200\320\276\320\262\320\275\321\217\321\202\321\214 \321\200\320\260\320\267\320\274\320\265\321\200\321\213", nullptr));
        menu_view->setTitle(QApplication::translate("MainWindow", "\320\222\320\270\320\264", nullptr));
        menu_scheme->setTitle(QApplication::translate("MainWindow", "\320\241\321\205\320\265\320\274\320\260", nullptr));
        menu_service_functions->setTitle(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\270\321\201\320\275\321\213\320\265 \321\204\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
        menu_service->setTitle(QApplication::translate("MainWindow", "\320\241\320\265\321\200\320\262\320\270\321\201", nullptr));
        menu_reference->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
