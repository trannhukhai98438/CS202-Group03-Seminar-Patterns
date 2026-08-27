#pragma once

class Visitor;

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual void accept(Visitor& visitor) = 0;
};
