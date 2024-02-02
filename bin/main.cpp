#include <iostream>

#include "..//lib//FiguresClasses.h"

int main() {

    FiguresClasses::Polygon pol({{1, 2},
                 {2, 3},
                 {5, 0}}, true);

    std::cout << pol.get_x() << " " << pol.get_y() << '\n'
              << pol.get_width() << " " << pol.get_height() << '\n'
              << pol.get_end_polygon() << '\n'
              << pol.get_type_object();


    return 0;
}