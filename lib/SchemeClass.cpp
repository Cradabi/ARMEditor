#include "SchemeClass.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>


void Scheme::set_width(int input_width) {
    actual_params.width = input_width;
}

void Scheme::set_height(int input_height) {
    actual_params.height = input_height;
}

void Scheme::set_version(int input_version) {
    actual_params.version = input_version;
}

void Scheme::set_scale(int input_scale) {
    actual_params.scale = input_scale;
}

void Scheme::set_scale_in_ARM(int input_scale_in_ARM) {
    actual_params.scale_in_ARM = input_scale_in_ARM;
}

void Scheme::set_fonts_number(int input_fonts_amount) {
    actual_params.fonts_amount = input_fonts_amount;
}

void Scheme::set_objects_number(int input_objects_number) {
    actual_params.objects_amount = input_objects_number;
}

void Scheme::set_groups_number(int input_groups_number) {
    actual_params.groups_amount = input_groups_number;
}

void Scheme::set_name_scheme(const std::string &input_name) {
    actual_params.name_scheme = input_name;
}

void Scheme::set_file_path(const std::string &input_file_path) {
    actual_params.file_path = input_file_path;
}

void Scheme::set_bd_name(const std::string &input_bd) {
    actual_params.name_bd = input_bd;
}

void Scheme::set_server(const std::string &input_server) {
    actual_params.server = input_server;
}

int Scheme::get_width() {
    return actual_params.width;
}

int Scheme::get_height() {
    return actual_params.height;
}

int Scheme::get_version() {
    return actual_params.version;
}

int Scheme::get_scale() {
    return actual_params.scale;
}

int Scheme::get_scale_in_ARM() {
    return actual_params.scale_in_ARM;
}

int Scheme::get_fonts_number() {
    return actual_params.fonts_amount;
}

int Scheme::get_objects_number() {
    return actual_params.objects_amount;
}

int Scheme::get_groups_number() {
    return actual_params.groups_amount;
}

std::string Scheme::get_name_scheme() {
    return actual_params.name_scheme;
}

std::string Scheme::get_file_path() {
    return actual_params.file_path;
}

std::string Scheme::get_bd_name() {
    return actual_params.name_bd;
}

std::string Scheme::get_server() {
    return actual_params.server;
}

void Scheme::draw_line(FiguresClasses::Line &pol, QPainter &painter) {
    QColor color_line = {pol.get_line_color()[0], pol.get_line_color()[1], pol.get_line_color()[2]};
    painter.setPen(QPen(color_line, pol.get_line_width(), style_vector[pol.get_style_line()], Qt::RoundCap));
    painter.drawLine(pol.get_st_x(), pol.get_st_y(), pol.get_end_x(), pol.get_end_y());

    switch (pol.get_start_style_arrow()) {
        case 1:
            painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
        case 2:
            painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
        case 3:
            painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
        case 4:
            painter.drawEllipse(pol.get_st_x() - pol.get_line_width() / 2, pol.get_st_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
    }

    switch (pol.get_end_style_arrow()) {
        case 1:
            painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
        case 2:
            painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
        case 3:
            painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());
        case 4:
            painter.drawEllipse(pol.get_end_x() - pol.get_line_width() / 2, pol.get_end_y() - pol.get_line_width() / 2,
                                pol.get_line_width(), pol.get_line_width());

    }
}

void Scheme::draw_rect(FiguresClasses::Rectangle &rect, QPainter &painter) {
    //начинаем отрисовку прямоугольника
    painter.save();
    painter.translate(rect.get_center_x(), rect.get_center_y());
    painter.rotate((-1) * rect.get_angle());

    if (rect.get_show()) {
        if (rect.get_show_filling()) {
            QColor filling_color = {rect.get_filling_color()[0], rect.get_filling_color()[1],
                                    rect.get_filling_color()[2]};
            painter.setBrush(filling_color);
        }
        QColor color_rect = {rect.get_line_color()[0], rect.get_line_color()[1], rect.get_line_color()[2]};
        painter.setPen(QPen(color_rect, rect.get_line_width(), style_vector[rect.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(QRect((-1) * (rect.get_width() / 2), (-1) * (rect.get_height() / 2), rect.get_width(),
                               rect.get_height()));
    }
    painter.restore();
}


void Scheme::draw_ellipse(FiguresClasses::Ellipse &el, QPainter &painter) {
    //начинаем отрисовку эллипса
    painter.save();
    painter.translate(el.get_center_x(), el.get_center_y());
    painter.rotate((-1) * el.get_angle());
    if (el.get_show()) {
        QColor color_el = {el.get_line_color()[0], el.get_line_color()[1], el.get_line_color()[2]};
        if (el.get_show_filling()) {
            QColor filling_color = {el.get_filling_color()[0], el.get_filling_color()[1], el.get_filling_color()[2]};
            painter.setBrush(filling_color);
        }
        painter.setPen(QPen(color_el, el.get_line_width(), style_vector[el.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawEllipse(
                QRect((-1) * (el.get_width() / 2), (-1) * (el.get_height() / 2), el.get_width(), el.get_height()));
    }
    painter.restore();
}


void Scheme::draw_arc(FiguresClasses::Arc &arc, QPainter &painter) {
    //начинаем отрисовку дуги
    painter.save();
    painter.translate(arc.get_center_x(), arc.get_center_y());
    painter.rotate((-1) * arc.get_angle());
    if (arc.get_show()) {
        QColor color_arc = {arc.get_line_color()[0], arc.get_line_color()[1], arc.get_line_color()[2]};
        painter.setPen(QPen(color_arc, arc.get_line_width(), style_vector[arc.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        if (arc.get_show_filling()) {
            QColor filling_color = {arc.get_filling_color()[0], arc.get_filling_color()[1], arc.get_filling_color()[2]};
            painter.setBrush(filling_color);
            painter.drawPie(QRect((-1) * (arc.get_width() / 2), (-1) * (arc.get_height() / 2), arc.get_width(),
                                  arc.get_height()), ((360 - arc.get_start_angle()) % 360) * (-16),
                            ((360 - arc.get_end_angle()) % 360) * (-16));
        } else {
            painter.drawArc(QRect((-1) * (arc.get_width() / 2), (-1) * (arc.get_height() / 2), arc.get_width(),
                                  arc.get_height()), ((360 - arc.get_start_angle()) % 360) * (-16),
                            ((360 - arc.get_end_angle()) % 360) * (-16));
        }
    }
    painter.restore();
}

void Scheme::draw_polygon(FiguresClasses::Polygon &poly, QPainter &painter) {
    //начинаем отрисовку полигона
    painter.save();
    painter.translate(poly.get_center_x(), poly.get_center_y());
    painter.rotate((-1) * poly.get_angle());
    if (poly.get_show()) {
        if (poly.get_show_filling()) {
            QColor filling_color = {poly.get_filling_color()[0], poly.get_filling_color()[1],
                                    poly.get_filling_color()[2]};
            painter.setBrush(filling_color);
        }
        QColor color_poly = {poly.get_line_color()[0], poly.get_line_color()[1], poly.get_line_color()[2]};
        painter.setPen(QPen(color_poly, poly.get_line_width(), style_vector[poly.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        QPoint qpoints[poly.get_points().size()];
        for (int i = 0; i < poly.get_points().size(); i++) {
            qpoints[i] = QPoint(poly.get_points()[i][0] - poly.get_center_x(),
                                poly.get_points()[i][1] - poly.get_center_y());
        }
        if (poly.get_end_polygon()) {
            painter.drawPolygon(qpoints, poly.get_points().size());
        } else {
            painter.drawPolyline(qpoints, poly.get_points().size());
        }
    }
    painter.restore();
}

void Scheme::draw_crooked_line(FiguresClasses::CrookedLine &crook, QPainter &painter) {
    //начинаем отрисовку кривой
    painter.save();
    painter.translate(crook.get_center_x(), crook.get_center_y());
    painter.rotate((-1) * crook.get_angle());
    if (crook.get_show()) {
        if (crook.get_show_filling()) {
            QColor filling_color = {crook.get_filling_color()[0], crook.get_filling_color()[1],
                                    crook.get_filling_color()[2]};
            painter.setBrush(filling_color);
        }
        QColor color_crook = {crook.get_line_color()[0], crook.get_line_color()[1], crook.get_line_color()[2]};
        painter.setPen(
                QPen(color_crook, crook.get_line_width(), style_vector[crook.get_style_line()], Qt::RoundCap,
                     Qt::RoundJoin));
        QPoint qpoints[crook.get_points().size()];
        for (int i = 0; i < crook.get_points().size(); i++) {
            qpoints[i] = QPoint(crook.get_points()[i][0] - crook.get_center_x(),
                                crook.get_points()[i][1] - crook.get_center_y());
        }
        painter.drawPolyline(qpoints, crook.get_points().size());
    }
    painter.restore();
}

void Scheme::draw_text(FiguresClasses::Text &text, QPainter &painter) {
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if (text.get_auto_size_text()) {
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width() / 2 - 2,
                                 text.get_y() - text.get_line_width() / 2 - 2, pxwidth + text.get_line_width() + 5,
                                 pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1) * text.get_angle());
    if (text.get_show()) {
        if (text.get_show_filling()) {
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1],
                                    text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), style_vector[text.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                         text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                           text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[text.get_hAlignment()] |
                               v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_image(FiguresClasses::Image &image, QPainter &painter) {
    //начало отображения картинки
    painter.save();
    painter.translate(image.get_center_x(), image.get_center_y());
    painter.rotate((-1) * image.get_angle());
    if (image.get_show()) {
        QRect target(image.get_x() - image.get_center_x(), image.get_y() - image.get_center_y(), image.get_width(),
                     image.get_height());
        QRect source(0, 0, 0, 0);
        QPixmap pixmap(image.get_image_path().c_str());
        painter.drawPixmap(target, pixmap, source);
    }
    painter.restore();
}

void Scheme::draw_transition_point(FiguresClasses::TransitionPoint &tr_p, QPainter &painter) {
    //начало отображения точки перехода
    if (tr_p.get_show()) {
        if (tr_p.get_show_filling()) {
            QColor filling_color = {tr_p.get_filling_color()[0], tr_p.get_filling_color()[1],
                                    tr_p.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        painter.setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(QRect(tr_p.get_x(), tr_p.get_y(), tr_p.get_width(), tr_p.get_height()));
        painter.drawEllipse(QPoint(tr_p.get_center_x(), tr_p.get_center_y()), 3, 3);
    }
}

void Scheme::draw_transition_button(FiguresClasses::TransitionButton &tr_b, QPainter &painter) {
    //начало отображения кнопки перехода
    painter.save();
    QFont tr_b_font(tr_b.get_font_name().c_str(), tr_b.get_font_size());
    tr_b_font.setBold(tr_b.get_bold_font());
    tr_b_font.setItalic(tr_b.get_italic_font());
    tr_b_font.setUnderline(tr_b.get_underlined_font());
    tr_b_font.setStrikeOut(tr_b.get_crossed_font());
    if (tr_b.get_auto_size_text()) {
        QFontMetrics fm(tr_b_font);
        int pxwidth = fm.width(tr_b.get_text().c_str());
        int pxheight = fm.height();
        tr_b.change_center_cords(tr_b.get_x() - 4, tr_b.get_y() - 4, pxwidth + 7, pxheight + 7);
    }
    painter.translate(tr_b.get_center_x(), tr_b.get_center_y());
    painter.rotate((-1) * tr_b.get_angle());
    if (tr_b.get_show()) {
        if (tr_b.get_show_filling()) {
            QColor filling_color = {tr_b.get_filling_color()[0], tr_b.get_filling_color()[1],
                                    tr_b.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect(0, 0, 0);
        painter.setPen(QPen(color_rect, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(tr_b.get_x() - tr_b.get_center_x(), tr_b.get_y() - tr_b.get_center_y(), tr_b.get_width(),
                         tr_b.get_height());
        QRect rect = QRect(tr_b.get_x() - tr_b.get_center_x(), tr_b.get_y() - tr_b.get_center_y(), tr_b.get_width(),
                           tr_b.get_height());
        QColor font_color = {tr_b.get_font_color()[0], tr_b.get_font_color()[1], tr_b.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(tr_b_font);
        painter.drawText(rect, h_alignment_vector[tr_b.get_hAlignment()] |
                               v_alignment_vector[tr_b.get_vAlignment()], tr_b.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_set(QPainter &painter) {
    QColor color_set = {200, 200, 200};
    painter.setPen(QPen(color_set, 1, Qt::DashLine, Qt::RoundCap));
    for (int i = 0; i < actual_params.width; i += 10) {
        painter.drawLine(i, 0, i, actual_params.height);
    }
    for (int i = 0; i < actual_params.height; i += 10) {
        painter.drawLine(0, i, actual_params.width, i);
    }
}

void Scheme::draw_telecontrol(FiguresClasses::Telecontrol &text, QPainter &painter) {
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if (text.get_auto_size_text()) {
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width() / 2 - 2,
                                 text.get_y() - text.get_line_width() / 2 - 2, pxwidth + text.get_line_width() + 5,
                                 pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1) * text.get_angle());
    if (text.get_show()) {
        if (text.get_show_filling()) {
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1],
                                    text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), style_vector[text.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                         text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                           text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[text.get_hAlignment()] |
                               v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_telemeasure(FiguresClasses::Telemeasure &text, QPainter &painter) {
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if (text.get_auto_size_text()) {
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width() / 2 - 2,
                                 text.get_y() - text.get_line_width() / 2 - 2, pxwidth + text.get_line_width() + 5,
                                 pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1) * text.get_angle());
    if (text.get_show()) {
        if (text.get_show_filling()) {
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1],
                                    text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), style_vector[text.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                         text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                           text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[text.get_hAlignment()] |
                               v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_telesignalisation(FiguresClasses::Telesignalisation &text, QPainter &painter) {
    //начало отрисовки текста
    painter.save();
    QFont text_font(text.get_font_name().c_str(), text.get_font_size());
    text_font.setBold(text.get_bold_font());
    text_font.setItalic(text.get_italic_font());
    text_font.setUnderline(text.get_underlined_font());
    text_font.setStrikeOut(text.get_crossed_font());
    if (text.get_auto_size_text()) {
        QFontMetrics fm(text_font);
        int pxwidth = fm.width(text.get_text().c_str());
        int pxheight = fm.height();
        text.change_center_cords(text.get_x() - text.get_line_width() / 2 - 2,
                                 text.get_y() - text.get_line_width() / 2 - 2, pxwidth + text.get_line_width() + 5,
                                 pxheight + text.get_line_width() + 5);
    }
    painter.translate(text.get_center_x(), text.get_center_y());
    painter.rotate((-1) * text.get_angle());
    if (text.get_show()) {
        if (text.get_show_filling()) {
            QColor filling_color = {text.get_filling_color()[0], text.get_filling_color()[1],
                                    text.get_filling_color()[2]};
            painter.setPen(filling_color);
            painter.setBrush(filling_color);
        }
        QColor color_rect = {text.get_line_color()[0], text.get_line_color()[1], text.get_line_color()[2]};
        painter.setPen(QPen(color_rect, text.get_line_width(), style_vector[text.get_style_line()], Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                         text.get_height());
        QRect rect = QRect(text.get_x() - text.get_center_x(), text.get_y() - text.get_center_y(), text.get_width(),
                           text.get_height());
        QColor font_color = {text.get_font_color()[0], text.get_font_color()[1], text.get_font_color()[2]};
        painter.setPen(font_color);
        painter.setFont(text_font);
        painter.drawText(rect, h_alignment_vector[text.get_hAlignment()] |
                               v_alignment_vector[text.get_vAlignment()], text.get_text().c_str());
    }
    painter.restore();
}

void Scheme::draw_scheme(QPainter &painter) {
    draw_set(painter);
    for (int i = 0; i < actual_params.line_vector.size(); i++) {
        draw_line(actual_params.line_vector[i], painter);
    }
    for (int i = 0; i < actual_params.rectangle_vector.size(); i++) {
        draw_rect(actual_params.rectangle_vector[i], painter);
    }
    for (int i = 0; i < actual_params.ellipse_vector.size(); i++) {
        draw_ellipse(actual_params.ellipse_vector[i], painter);
    }
    for (int i = 0; i < actual_params.arc_vector.size(); i++) {
        draw_arc(actual_params.arc_vector[i], painter);
    }
    for (int i = 0; i < actual_params.line_vector.size(); i++) {
        draw_line(actual_params.line_vector[i], painter);
    }
    for (int i = 0; i < actual_params.polygon_vector.size(); i++) {
        draw_polygon(actual_params.polygon_vector[i], painter);
    }
    for (int i = 0; i < actual_params.crooked_line_vector.size(); i++) {
        draw_crooked_line(actual_params.crooked_line_vector[i], painter);
    }
    for (int i = 0; i < actual_params.text_vector.size(); i++) {
        draw_text(actual_params.text_vector[i], painter);
    }
    for (int i = 0; i < actual_params.image_vector.size(); i++) {
        draw_image(actual_params.image_vector[i], painter);
    }
    for (int i = 0; i < actual_params.tr_p_vector.size(); i++) {
        draw_transition_point(actual_params.tr_p_vector[i], painter);
    }
    for (int i = 0; i < actual_params.tr_b_vector.size(); i++) {
        draw_transition_button(actual_params.tr_b_vector[i], painter);
    }
    for (int i = 0; i < actual_params.telecontrol_vector.size(); i++) {
        draw_telecontrol(actual_params.telecontrol_vector[i], painter);
    }
    for (int i = 0; i < actual_params.telemeasure_vector.size(); i++) {
        draw_telemeasure(actual_params.telemeasure_vector[i], painter);
    }
    for (int i = 0; i < actual_params.telesignalisation_vector.size(); i++) {
        draw_telesignalisation(actual_params.telesignalisation_vector[i], painter);
    }
}

void Scheme::add_object(FiguresClasses::Line &add_line) {
    actual_params.line_vector.push_back(add_line);
}

void Scheme::add_object(FiguresClasses::Rectangle &add_rect) {
    actual_params.rectangle_vector.push_back(add_rect);
}

void Scheme::add_object(FiguresClasses::Ellipse &add_el) {
    actual_params.ellipse_vector.push_back(add_el);
}

void Scheme::add_object(FiguresClasses::Arc &add_arc) {
    actual_params.arc_vector.push_back(add_arc);
}

void Scheme::add_object(FiguresClasses::Polygon &add_poly) {
    actual_params.polygon_vector.push_back(add_poly);
}

void Scheme::add_object(FiguresClasses::CrookedLine &add_crook) {
    actual_params.crooked_line_vector.push_back(add_crook);
}

void Scheme::add_object(FiguresClasses::Text &add_text) {
    actual_params.text_vector.push_back(add_text);
}

void Scheme::add_object(FiguresClasses::Image &add_image) {
    actual_params.image_vector.push_back(add_image);
}

void Scheme::add_object(FiguresClasses::TransitionPoint &add_tr_p) {
    actual_params.tr_p_vector.push_back(add_tr_p);
}

void Scheme::add_object(FiguresClasses::TransitionButton &add_tr_b) {
    actual_params.tr_b_vector.push_back(add_tr_b);
}

void Scheme::add_object(FiguresClasses::Telecontrol &add_telec) {
    actual_params.telecontrol_vector.push_back(add_telec);
}

void Scheme::add_object(FiguresClasses::Telemeasure &add_telem) {
    actual_params.telemeasure_vector.push_back(add_telem);
}

void Scheme::add_object(FiguresClasses::Telesignalisation &add_teles) {
    actual_params.telesignalisation_vector.push_back(add_teles);
}






