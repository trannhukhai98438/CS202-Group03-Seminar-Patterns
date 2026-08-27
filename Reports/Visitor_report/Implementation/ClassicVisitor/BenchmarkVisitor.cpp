#include "BenchmarkVisitor.h"
#include "Shapes.h"

void BenchmarkVisitor::visit(Circle const& c) {
    totalArea += c.area();
}

void BenchmarkVisitor::visit(Rectangle const& r) {
    totalArea += r.area();
}
