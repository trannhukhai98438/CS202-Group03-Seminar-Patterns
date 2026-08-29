#include "BenchmarkSupport.h"

#include <algorithm>
#include <memory>
#include <random>
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
    explicit Circle(float radius) : radius_(radius) {}
    double area() const { return 3.1415926535 * radius_ * radius_; }
    void accept(AbstractVisitor& visitor) const override {
        if (auto* target = dynamic_cast<Visitor<Circle>*>(&visitor)) {
            target->visit(*this);
        }
    }

private:
    float radius_;
};

class Rectangle final : public Shape {
public:
    Rectangle(float width, float height) : width_(width), height_(height) {}
    double area() const { return width_ * height_; }
    void accept(AbstractVisitor& visitor) const override {
        if (auto* target = dynamic_cast<Visitor<Rectangle>*>(&visitor)) {
            target->visit(*this);
        }
    }

private:
    float width_;
    float height_;
};

class AreaVisitor final : public AbstractVisitor,
                          public Visitor<Circle>,
                          public Visitor<Rectangle> {
public:
    void visit(const Circle& circle) override { total_area += circle.area(); }
    void visit(const Rectangle& rectangle) override { total_area += rectangle.area(); }
    double total_area = 0.0;
};

int main(int argc, char* argv[]) {
    try {
        const benchmark::Config config = benchmark::parse_config(argc, argv);
        std::vector<std::unique_ptr<Shape>> shapes;
        shapes.reserve(config.object_count);
        for (std::size_t index = 0; index < config.object_count; ++index) {
            if (index % 2 == 0) {
                shapes.push_back(std::make_unique<Circle>(2.0f));
            } else {
                shapes.push_back(std::make_unique<Rectangle>(3.0f, 4.0f));
            }
        }
        std::mt19937 random(config.seed);
        std::shuffle(shapes.begin(), shapes.end(), random);

        const auto result = benchmark::measure(config, [&shapes] {
            AreaVisitor visitor;
            for (const auto& shape : shapes) {
                shape->accept(visitor);
            }
            return visitor.total_area;
        });
        benchmark::print_result("Acyclic Visitor", config, result);
    } catch (const std::exception& error) {
        std::cerr << "Benchmark error: " << error.what() << '\n';
        return 1;
    }
}
