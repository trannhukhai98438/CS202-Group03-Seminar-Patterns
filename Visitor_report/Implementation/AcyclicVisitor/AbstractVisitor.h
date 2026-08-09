#pragma once

class AbstractVisitor {
protected:
    AbstractVisitor() = default;
public:
    virtual ~AbstractVisitor() = default;
};

template <class T>
class Visitor {
public:
    Visitor() = default;
    virtual ~Visitor() = default;
    virtual void visit(T const& obj) = 0;
};