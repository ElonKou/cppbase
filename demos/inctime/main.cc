/*================================================================
*  Copyright (C)2023 All rights reserved.
*  FileName : main.cc
*  Author   : koudongliang
*  Email    : elonkou@ktime.cc
*  Date     : Mon Nov 11 18:48:19 2024
================================================================*/

#include "InstrumentorTimer.hh"

int Fibonacci(int x) {
    std::string name = std::string("Fibonacci ") + std::to_string(x);
    PROFILE_WITH_NAME(name.c_str());

    std::this_thread::sleep_for(std::chrono::microseconds(1)); // Compensate statistical temporal precision problem

    if (x < 3)
        return 1;
    int part1 = Fibonacci(x - 1);
    int part2 = Fibonacci(x - 2);
    return part1 + part2;
}

namespace MySpace {
class Some {
  public:
    Some()  = default;
    ~Some() = default;
    void Say() {
        PROFILE_SCOPE();
        std::string x = "";
        for (size_t i = 0; i < 1000; i++) {
            x = x + std::to_string(i);
        }
    }
    void Say(int y) {
        PROFILE_SCOPE();

        std::string z = "";
        for (size_t i = 0; i < 1000; i++) {
            z = z + std::to_string(i + y);
        }

        {
            PROFILE_WITH_NAME("Say 1");
            std::string x = "";
            for (size_t i = 0; i < 1000; i++) {
                x = x + std::to_string(i + y);
            }
        }

        {
            PROFILE_WITH_NAME("Say 2");
            std::string ret = "";
            for (size_t i = 0; i < 3000; i++) {
                ret = ret + std::to_string(i + y * 2);
            }
        }
    }
};
} // namespace MySpace

namespace Benchmark {

void RunBenchmarks() {
    PROFILE_SCOPE();

    std::cout << "Running Benchmarks..." << std::endl;
    std::thread t1([]() { Fibonacci(9); });
    std::thread t2([]() { Fibonacci(10); });

    MySpace::Some so;
    so.Say();
    so.Say(100);

    t1.join();
    t2.join();
}
} // namespace Benchmark

int main() {
    Instrumentor::BeginSession("Benchmark");
    Benchmark::RunBenchmarks();
    return 0;
}