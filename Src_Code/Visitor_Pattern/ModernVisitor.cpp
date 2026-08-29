#include <iostream>
#include <ostream>
#include <variant>
#include <vector>

class Circle {
public:
    explicit Circle(double radius) : radius_(radius) {}
    double radius() const { return radius_; }

private:
    double radius_;
};

class Rectangle {
public:
    Rectangle(double width, double height)
        : width_(width), height_(height) {}
    double width() const { return width_; }
    double height() const { return height_; }

private:
    double width_;
    double height_;
};

using Shape = std::variant<Circle, Rectangle>;

class SaveVisitor {
public:
    explicit SaveVisitor(std::ostream& output) : output_(output) {}

    void operator()(const Circle& circle) const {
        output_ << "<circle radius=\"" << circle.radius() << "\"/>\n";
    }

    void operator()(const Rectangle& rectangle) const {
        output_ << "<rectangle width=\"" << rectangle.width()
                << "\" height=\"" << rectangle.height() << "\"/>\n";
    }

private:
    std::ostream& output_;
};

int main() {
    const std::vector<Shape> shapes{Circle{5.0}, Rectangle{4.0, 6.0}};
    SaveVisitor save(std::cout);
    for (const auto& shape : shapes) {
        std::visit(save, shape);
    }
}
