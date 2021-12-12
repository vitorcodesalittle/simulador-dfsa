#include <vector>
//
// Created by vilma on 12/11/21.
//

#ifndef SIMULADOR_CONFIG_H
#define SIMULADOR_CONFIG_H

typedef unsigned long long ull;

class ExperimentConfig {
public:
    int initial_tags;
    int tag_increment;
    int max_tags;
    int repetitions;
    ull initial_frame;
    bool no_power_of_2;
    std::vector<std::string> estimators;

    std::string to_string();

    static ExperimentConfig parse(int argc, char **argv);
};



#endif //SIMULADOR_CONFIG_H
