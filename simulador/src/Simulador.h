#ifndef SIMULADOR_SIMULADOR_H
#define SIMULADOR_SIMULADOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Estimator.h"
using namespace std;

class Result {
public:
    static string to_string() {
        return "";
    }
};

class Simulator {
public:
    ull initial_frame;
    Estimator &estimator;
    ull current_frame;
    std::vector<SlottedAlohaInfo> history;
    Simulator(int ifs, Estimator &estimator) : estimator(estimator), initial_frame(ifs) {
        history = std::vector<SlottedAlohaInfo>();
        current_frame = initial_frame;
    }

    void run(int ntags);
};



#endif //SIMULADOR_SIMULADOR_H
