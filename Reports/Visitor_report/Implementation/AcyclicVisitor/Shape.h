#pragma once

class AbstractVisitor;

class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual void accept(AbstractVisitor& visitor) = 0;
};
