#include "Shapes.h"
#include "AbstractVisitor.h"

void Circle::accept(AbstractVisitor& visitor) {
    if (auto* cv = dynamic_cast<Visitor<Circle>*>(&visitor)) {
        cv->visit(*this);
    }
}

void Rectangle::accept(AbstractVisitor& visitor) {
    if (auto* cv = dynamic_cast<Visitor<Rectangle>*>(&visitor)) {
        cv->visit(*this);
    }
}
