#pragma once
#include "Shapes.h"
#include <variant>

using Shape = std::variant<Circle, Rectangle>;

struct BenchmarkVisitor {
    double totalArea = 0.0;

    void operator()(Circle const& c) {
        totalArea += c.area();
    }
    
    void operator()(Rectangle const& r) {
        totalArea += r.area();
    }
};
