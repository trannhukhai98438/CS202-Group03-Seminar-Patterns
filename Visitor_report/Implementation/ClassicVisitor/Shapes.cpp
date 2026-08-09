#include "Shapes.h"
#include "Visitor.h"

void Circle::accept(Visitor& visitor) {
    visitor.visit(*this);
}

void Rectangle::accept(Visitor& visitor) {
    visitor.visit(*this);
}
