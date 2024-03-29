#pragma once
#include <vector>
#include "Point.hpp"

class Polygon {
public:
    Polygon()=default;
    explicit Polygon(const Point& p);
    explicit Polygon(const std::vector<Point>& p_vec);

    Polygon& operator+=(const Point& point);
    Point operator[](int ind);

    std::vector<Point>& getPoints();
    [[nodiscard]] int size() const;
    [[maybe_unused]] void display() const;
    [[nodiscard]] double area() const;
private:
    std::vector<Point> points{};
};