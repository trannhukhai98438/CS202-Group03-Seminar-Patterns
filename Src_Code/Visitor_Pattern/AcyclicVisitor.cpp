#include <iostream>
#include <memory>
#include <vector>

class Circle;
class Rectangle;

class AbstractVisitor {
public:
    virtual ~AbstractVisitor() = default;
};

template <typename ShapeType>
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const ShapeType& shape) = 0;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(AbstractVisitor& visitor) const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}

    double area() const { return 3.1415926535 * radius_ * radius_; }
    void accept(AbstractVisitor& visitor) const override {
        if (auto* circle_visitor = dynamic_cast<Visitor<Circle>*>(&visitor)) {
            circle_visitor->visit(*this);
        }
    }

private:
    double radius_;
};

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height) : width_(width), height_(height) {}

    double area() const { return width_ * height_; }
    void accept(AbstractVisitor& visitor) const override {
        if (auto* rectangle_visitor = dynamic_cast<Visitor<Rectangle>*>(&visitor)) {
            rectangle_visitor->visit(*this);
        }
    }

private:
    double width_;
    double height_;
};

class AreaVisitor final : public AbstractVisitor,
                          public Visitor<Circle>,
                          public Visitor<Rectangle> {
public:
    void visit(const Circle& circle) override { total_area += circle.area(); }
    void visit(const Rectangle& rectangle) override { total_area += rectangle.area(); }

    double total_area = 0.0;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

    AreaVisitor visitor;
    for (const auto& shape : shapes) {
        shape->accept(visitor);
    }

    std::cout << "Acyclic Visitor\n";
    std::cout << "Total area: " << visitor.total_area << '\n';
    return 0;
}
