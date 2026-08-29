#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

namespace benchmark {

struct Config {
    std::size_t object_count = 10'000'000;
    int iterations = 20;
    std::uint32_t seed = std::random_device{}();
};

struct Result {
    double minimum_ms;
    double checksum;
};

inline Config parse_config(int argc, char* argv[]) {
    Config config;
    if (argc > 1) {
        config.object_count = std::stoull(argv[1]);
    }
    if (argc > 2) {
        config.iterations = std::stoi(argv[2]);
    }
    if (argc > 3) {
        config.seed = static_cast<std::uint32_t>(std::stoul(argv[3]));
    }
    if (config.object_count == 0 || config.iterations <= 0) {
        throw std::invalid_argument("object count and iterations must be positive");
    }
    return config;
}

template <typename Traversal>
Result measure(const Config& config, Traversal&& traverse) {
    double minimum_ms = std::numeric_limits<double>::max();
    double checksum = 0.0;

    for (int iteration = 0; iteration < config.iterations; ++iteration) {
        const auto start = std::chrono::steady_clock::now();
        const double current_checksum = traverse();
        const auto finish = std::chrono::steady_clock::now();

        const std::chrono::duration<double, std::milli> elapsed = finish - start;
        if (elapsed.count() < minimum_ms) {
            minimum_ms = elapsed.count();
        }
        if (iteration == 0) {
            checksum = current_checksum;
        } else if (current_checksum != checksum) {
            throw std::runtime_error("checksum changed between iterations");
        }
    }
    return {minimum_ms, checksum};
}

inline void print_result(const char* name, const Config& config, const Result& result) {
    std::cout << name << '\n'
              << "Objects: " << config.object_count << '\n'
              << "Measured iterations: " << config.iterations << '\n'
              << "Shuffle seed: " << config.seed << '\n'
              << "Minimum traversal time: " << result.minimum_ms << " ms\n"
              << "Checksum: " << result.checksum << '\n';
}

}  // namespace benchmark
