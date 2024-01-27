#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <cmath>

using namespace std;

class Line { // пока что на вход подаются только начальные и конечные координаты
public:
    Line(tuple<int, int> start_cord, tuple<int, int> end_cord, tuple<int, int, int> line_color) {
        this->line_color = line_color;
        change_center_cords_and_k_b(start_cord, end_cord);
    }

    void change_center_cords_and_k_b(tuple<int, int> cords_start,
                                     tuple<int, int> cords_end) { //меняет координаты начала, конца, центра линии и находит k и b из формулы y = kx + b
        this->start_cords = cords_start;
        this->end_cords = cords_end;
        int x_cord = 0;
        int y_cord = 0;
        x_cord = floor(abs(get<0>(this->start_cords) - get<0>(this->end_cords)));
        y_cord = floor(abs(get<1>(this->start_cords) - get<1>(this->end_cords)));
        get<0>(this->center_cords) = x_cord;
        get<1>(this->center_cords) = y_cord; //конец замены координат центра
        // начинаем замену k и b
        this->k = ((double) (get<1>(this->start_cords) - get<1>(this->end_cords))) /
                  (get<0>(this->start_cords) - get<0>(this->end_cords));
        this->b = ((double) get<1>(this->start_cords)) - (double) (get<0>(this->start_cords) * (this->k));

    }

    bool is_mous_in_line(
            tuple<int, int> mouse_cords) { //возвращает true, если поступаемые координаты лежат на прямой, и false в обратном случае.
        int cord_y_in_point = floor(
                (this->k) * get<0>(mouse_cords) + this->b); //находит координату y на линии в точке x
        if (abs(cord_y_in_point - get<1>(mouse_cords)) <=
            ((this->line_width) * 2)) { //проверка, что координаты мыши сходятся с координатами точкина прямой
            if (get<0>(this->start_cords) >= get<0>(this->end_cords) &&
                get<1>(this->start_cords) >=
                get<1>(this->end_cords)) {   // четыре проверки для разных расположений начальной и конечной точек на то что координаты мыши находятся внутри отрезка
                if (get<0>(mouse_cords) > get<0>(this->start_cords) || get<0>(mouse_cords) < get<0>(this->end_cords) ||
                    get<1>(mouse_cords) > get<1>(this->start_cords) || get<1>(mouse_cords) < get<1>(this->end_cords)) {
                    return false;
                } else {
                    return true;
                }
            } else if (get<0>(this->start_cords) >= get<0>(this->end_cords) &&
                       get<1>(this->start_cords) <= get<1>(this->end_cords)) {
                if (get<0>(mouse_cords) > get<0>(this->start_cords) || get<0>(mouse_cords) < get<0>(this->end_cords) ||
                    get<1>(mouse_cords) < get<1>(this->start_cords) || get<1>(mouse_cords) > get<1>(this->end_cords)) {
                    return false;
                } else {
                    return true;
                }
            } else if (get<0>(this->start_cords) <= get<0>(this->end_cords) &&
                       get<1>(this->start_cords) >= get<1>(this->end_cords)) {
                if (get<0>(mouse_cords) < get<0>(this->start_cords) || get<0>(mouse_cords) > get<0>(this->end_cords) ||
                    get<1>(mouse_cords) > get<1>(this->start_cords) || get<1>(mouse_cords) < get<1>(this->end_cords)) {
                    return false;
                } else {
                    return true;
                }
            } else {
                if (get<0>(mouse_cords) < get<0>(this->start_cords) || get<0>(mouse_cords) > get<0>(this->end_cords) ||
                    get<1>(mouse_cords) < get<1>(this->start_cords) || get<1>(mouse_cords) > get<1>(this->end_cords)) {
                    return false;
                } else {
                    return true;
                }
            }
        } else {
            return false;
        }
    }

    double get_k() { //возвращает приватную переменную k
        return this->k;
    }

    double get_b() {  //возвращает приватную переменную b
        return this->b;
    }

    tuple<int, int> get_center_cords() {  //возвращает приватный кортеж center_cords
        return this->center_cords;
    }


    string text = "";
    string help_line = "";
    string font_name = "";
    bool show_help = false;
    bool show_line = true;
    int font_size = 14;
    int number_of_text = 0;
    int style_line = 0;
    int line_width = 2;
    int start_style_arrow = 0;
    int end_style_arrow = 0;
    tuple<int, int> start_cords;
    tuple<int, int> end_cords;
    tuple<int, int, int> line_color;
private:
    double k;
    double b;
    tuple<int, int> center_cords;

};


int main() {
    tuple<int, int> start_cords(4, 2);
    tuple<int, int> end_cords(180, 442);
    tuple<int, int, int> line_color(0, 0, 0);
    tuple <int, int> mouse_cords(4, 2);
    Line l1(start_cords, end_cords, line_color);
    cout << l1.get_k() << endl << l1.get_b() << endl << l1.is_mous_in_line(mouse_cords);

    return 0;
}

