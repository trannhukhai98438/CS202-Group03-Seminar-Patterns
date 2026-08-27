#pragma once
#include "Visitor.h"

class BenchmarkVisitor : public Visitor {
public:
    double totalArea = 0.0;

    BenchmarkVisitor() = default;
    ~BenchmarkVisitor() = default;

    void visit(Circle const& c) override;
    void visit(Rectangle const& r) override;
};
