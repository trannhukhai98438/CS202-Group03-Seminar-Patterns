#pragma once
#include "AbstractVisitor.h"
#include "Shapes.h"

class BenchmarkVisitor : public AbstractVisitor, public Visitor<Circle>, public Visitor<Rectangle> {
public:
    double totalArea = 0.0;

    BenchmarkVisitor() = default;
    
    void visit(Circle const& c) override;
    void visit(Rectangle const& r) override;
};
