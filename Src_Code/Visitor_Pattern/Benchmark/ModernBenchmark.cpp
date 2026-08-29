#include "BenchmarkSupport.h"

#include <algorithm>
#include <random>
#include <variant>
#include <vector>

class Circle {
public:
    explicit Circle(float radius) : radius_(radius) {}
    double area() const { return 3.1415926535 * radius_ * radius_; }

private:
    float radius_;
};

class Rectangle {
public:
    Rectangle(float width, float height) : width_(width), height_(height) {}
    double area() const { return width_ * height_; }

private:
    float width_;
    float height_;
};

using Shape = std::variant<Circle, Rectangle>;

class AreaVisitor {
public:
    void operator()(const Circle& circle) { total_area += circle.area(); }
    void operator()(const Rectangle& rectangle) { total_area += rectangle.area(); }
    double total_area = 0.0;
};

int main(int argc, char* argv[]) {
    try {
        const benchmark::Config config = benchmark::parse_config(argc, argv);
        std::vector<Shape> shapes;
        shapes.reserve(config.object_count);
        for (std::size_t index = 0; index < config.object_count; ++index) {
            if (index % 2 == 0) {
                shapes.emplace_back(Circle{2.0f});
            } else {
                shapes.emplace_back(Rectangle{3.0f, 4.0f});
            }
        }
        std::mt19937 random(config.seed);
        std::shuffle(shapes.begin(), shapes.end(), random);

        const auto result = benchmark::measure(config, [&shapes] {
            AreaVisitor visitor;
            for (const auto& shape : shapes) {
                std::visit(visitor, shape);
            }
            return visitor.total_area;
        });
        benchmark::print_result("Modern Visitor (std::variant)", config, result);
    } catch (const std::exception& error) {
        std::cerr << "Benchmark error: " << error.what() << '\n';
        return 1;
    }
}
