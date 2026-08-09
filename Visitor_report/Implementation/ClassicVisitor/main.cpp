#include "Shapes.h"
#include "BenchmarkVisitor.h"
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>

int main() {
    constexpr int NUM_OBJECTS = 10'000'000;
    constexpr int ITERATIONS = 20;
    
    std::cout << "ClassicVisitor: Generating " << NUM_OBJECTS << " objects...\n";

    std::vector<Shape*> classicShapes;
    classicShapes.reserve(NUM_OBJECTS);
    
    for (int i = 0; i < NUM_OBJECTS / 2; ++i) {
        classicShapes.push_back(new Circle(2.0f));
        classicShapes.push_back(new Rectangle(3.0f, 4.0f));
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(classicShapes.begin(), classicShapes.end(), g);

    double min_duration = 1e9;
    double final_area = 0.0;

    std::cout << "Starting benchmark (20 iterations)...\n";
    for (int iter = 0; iter < ITERATIONS; ++iter) {
        BenchmarkVisitor classicVisitor;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (auto* shape : classicShapes) {
            shape->accept(classicVisitor);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        
        if (duration.count() < min_duration) {
            min_duration = duration.count();
        }
        final_area = classicVisitor.totalArea; // prevent dead code
    }

    std::cout << "Classic Visitor minimum time: " << min_duration << " ms\n";
    std::cout << "Total Area [Anti-optimization]: " << final_area << "\n\n";

    for (auto* shape : classicShapes) {
        delete shape;
    }
    
    return 0;
}