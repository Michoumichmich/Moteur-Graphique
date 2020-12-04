#include <chrono>
#include <iostream>
#include <utility>

#include "Chrono.h"

Chrono::Chrono() {
    start = std::chrono::high_resolution_clock::now();
}

Chrono::~Chrono() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    if (!caller.empty()) {
        std::cerr << "time in " << caller << " : " << duration.count() / 1000000.0 << "s" << std::endl;
    } else {
        std::cerr << "time " << duration.count() / 1000000.0 << "s" << std::endl;
    }

}

Chrono::Chrono(std::string caller_name) : Chrono() {
    caller = std::move(caller_name);
}
