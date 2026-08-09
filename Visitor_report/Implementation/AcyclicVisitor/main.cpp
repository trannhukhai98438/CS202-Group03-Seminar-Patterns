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
    
    std::cout << "AcyclicVisitor: Generating " << NUM_OBJECTS << " objects...\n";

    std::vector<Shape*> acyclicShapes;
    acyclicShapes.reserve(NUM_OBJECTS);
    
    for (int i = 0; i < NUM_OBJECTS / 2; ++i) {
        acyclicShapes.push_back(new Circle(2.0f));
        acyclicShapes.push_back(new Rectangle(3.0f, 4.0f));
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(acyclicShapes.begin(), acyclicShapes.end(), g);

    double min_duration = 1e9;
    double final_area = 0.0;

    std::cout << "Starting benchmark (20 iterations)...\n";
    for (int iter = 0; iter < ITERATIONS; ++iter) {
        BenchmarkVisitor acyclicVisitor;
        auto start = std::chrono::high_resolution_clock::now();
        
        for (auto* shape : acyclicShapes) {
            shape->accept(acyclicVisitor);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        
        if (duration.count() < min_duration) {
            min_duration = duration.count();
        }
        final_area = acyclicVisitor.totalArea; // prevent dead code
    }

    std::cout << "Acyclic Visitor minimum time: " << min_duration << " ms\n";
    std::cout << "Total Area [Anti-optimization]: " << final_area << "\n\n";

    for (auto* shape : acyclicShapes) {
        delete shape;
    }
    
    return 0;
}