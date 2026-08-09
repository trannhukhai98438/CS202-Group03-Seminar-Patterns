#pragma once
#include "Shape.h"

class Circle : public Shape {
public:
    float radius_;
    Circle(float radius) : radius_(radius) {}
    ~Circle() = default;

    double area() const {
        return 3.1415926535 * radius_ * radius_;
    }

    void accept(Visitor& visitor) override;
};

class Rectangle : public Shape {
public:
    float width_, height_;
    Rectangle(float width, float height) : width_(width), height_(height) {}
    ~Rectangle() = default;

    double area() const {
        return width_ * height_;
    }

    void accept(Visitor& visitor) override;
};
