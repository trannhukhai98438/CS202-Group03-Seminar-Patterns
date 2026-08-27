#pragma once

class Circle;
class Rectangle;

class Visitor {
public:
    Visitor() = default;
    virtual ~Visitor() = default;
    
    // Using mutable references/pointers or 'mutable' variable in const method if we keep it const,
    // but the standard Visitor can just drop 'const' for modifying state in visitor.
    virtual void visit(Circle const& c) = 0;
    virtual void visit(Rectangle const& r) = 0;
};
