#include <iostream>
#include <variant>
#include <vector>

class Circle {
public:
    explicit Circle(double radius) : radius_(radius) {}

    double area() const { return 3.1415926535 * radius_ * radius_; }

private:
    double radius_;
};

class Rectangle {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    double area() const { return width_ * height_; }

private:
    double width_;
    double height_;
};

using Shape = std::variant<Circle, Rectangle>;

struct AreaVisitor {
    void operator()(const Circle& circle) { total_area += circle.area(); }
    void operator()(const Rectangle& rectangle) { total_area += rectangle.area(); }

    double total_area = 0.0;
};

int main() {
    std::vector<Shape> shapes;
    shapes.emplace_back(Circle(2.0));
    shapes.emplace_back(Rectangle(3.0, 4.0));

    AreaVisitor visitor;
    for (const auto& shape : shapes) {
        std::visit(visitor, shape);
    }

    std::cout << "Modern Visitor\n";
    std::cout << "Total area: " << visitor.total_area << '\n';
    return 0;
}
