#ifndef SIMULADOR_SIMULADOR_H
#define SIMULADOR_SIMULADOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Estimator.h"
using namespace std;

class Result {
public:
    double total_slots{};
    double total_empty_slots;
    double total_collision_slots;
    double time;
    Result() {
        total_collision_slots = 0;
        total_empty_slots = 0;
        total_collision_slots = 0;
        time = 0;
    }
    Result(double ts, double tes, double tcs, double tt): total_slots{ts}, total_empty_slots{tes}, total_collision_slots{tcs}, time{tt} {}
    string to_string() const;
    void operator += (Result &b) {
        total_slots += b.total_slots;
        total_empty_slots += b.total_empty_slots;
        total_collision_slots += b.total_collision_slots;
        time += b.time;
    };
    Result operator / (int k) const {
        return Result {total_slots / k, total_empty_slots / k, total_collision_slots / k, time / k};
    }
};

class Simulator {
public:
    bool use_power_of_2;
    ull initial_frame;
    Estimator &estimator;
    ull current_frame_size;
    std::vector<SlottedAlohaInfo> history;
    Simulator(ull ifs, Estimator &estimator, bool use_power_of_2 = false) : estimator(estimator), initial_frame(ifs), use_power_of_2(use_power_of_2) {
        history = std::vector<SlottedAlohaInfo>();
        current_frame_size = initial_frame;
    }
    ~Simulator() = default;
    Result run(ull ntags);
};



#endif //SIMULADOR_SIMULADOR_H
