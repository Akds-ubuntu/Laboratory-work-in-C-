#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include "data/Point.hpp"
#include "data/Polygon.hpp"
#include "Geometry.h"
#include "Constants.h"

int main() {
    std::ifstream f("/Users/mand/CLionProjects/sandbox/test.txt");
    unsigned int num_polygons = 0;
    bool is_stopped = false;
    //std::cout << "Enter the number of polygons: ";
    //std::cin >> num_polygons;
    f >> num_polygons;
    std::vector<Polygon> polygons{};

    for (size_t i = 1; i <= num_polygons; ++i) {
        //std::cout << "Enter the number of points of polygon №" << i << ":" << '\n';
        unsigned int point_count = 0;
        //std::cin >> point_count;
        //std::cout << "Enter the coordinates of the points of polygon №" << i << '\n';
        f >> point_count;
        std::set<Point> unique_points{};

        for (size_t j = 0; j < point_count; ++j) {
            double x, y;
            //std::cin >> x >> y;
            f >> x >> y;
            Point point(x, y);
            unique_points.insert(point);
        }
        if (unique_points.size() >= MIN_POINT_AMOUNT) {
            Polygon new_polygon(Geometry::convexHull(unique_points));
            polygons.push_back(new_polygon);
        } else {
            is_stopped = true;
        }
        unique_points.clear();
    }
    f.close();
    if (is_stopped || num_polygons < 1) {
        std::cout << is_stopped;
        std::cout << "Total polygon area intersection: 0.0" << '\n';
    } else {
        Polygon clipped_polygon = Geometry::clipPolygons(polygons);
        double total_area = clipped_polygon.area();
        std::cout << "Total polygon area intersection: " << total_area << '\n';
        if (!clipped_polygon.getPoints().empty()) {
            clipped_polygon.display();
        }
    }
    polygons.clear();
    return 0;
}