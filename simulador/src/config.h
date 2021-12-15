#include <vector>
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
    std::string output_path;
    std::vector<std::string> estimators;

    ExperimentConfig() {
        initial_frame = 64;
        repetitions = 5;
        max_tags = 1000;
        initial_tags = 100;
        tag_increment = 100;
        no_power_of_2 = false;
        output_path = "results";
        estimators = std::vector<std::string> {"lb", "shoute", "eom-lee", "iv2"};
    }

    std::string to_string();

    static ExperimentConfig parse(int argc, char **argv);
};



#endif //SIMULADOR_CONFIG_H
