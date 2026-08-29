#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

class AbstractVisitor {
public:
    virtual ~AbstractVisitor() = default;
};

template <typename Element>
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const Element& element) = 0;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(AbstractVisitor& visitor) const = 0;
};

class Circle final : public Shape {
public:
    explicit Circle(double radius) : radius_(radius) {}
    double radius() const { return radius_; }

    void accept(AbstractVisitor& visitor) const override {
        if (auto* target = dynamic_cast<Visitor<Circle>*>(&visitor)) {
            target->visit(*this);
        }
    }

private:
    double radius_;
};

class Rectangle final : public Shape {
public:
    Rectangle(double width, double height)
        : width_(width), height_(height) {}
    double width() const { return width_; }
    double height() const { return height_; }

    void accept(AbstractVisitor& visitor) const override {
        if (auto* target = dynamic_cast<Visitor<Rectangle>*>(&visitor)) {
            target->visit(*this);
        }
    }

private:
    double width_;
    double height_;
};

class SaveVisitor final : public AbstractVisitor,
                          public Visitor<Circle>,
                          public Visitor<Rectangle> {
public:
    explicit SaveVisitor(std::ostream& output) : output_(output) {}

    void visit(const Circle& circle) override {
        output_ << "<circle radius=\"" << circle.radius() << "\"/>\n";
    }

    void visit(const Rectangle& rectangle) override {
        output_ << "<rectangle width=\"" << rectangle.width()
                << "\" height=\"" << rectangle.height() << "\"/>\n";
    }

private:
    std::ostream& output_;
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));

    SaveVisitor save(std::cout);
    for (const auto& shape : shapes) {
        shape->accept(save);
    }
}
