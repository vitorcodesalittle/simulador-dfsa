#include <string>
#include <algorithm>
#include "config.h"

using namespace std;

#define INITIAL_TAGS "--initial-tags"
#define INCREMENT_TAGS "--increment-tags"
#define MAX_TAGS "--max-tags"
#define INITIAL_FRAME "--initial-frame"
#define REPETITIONS "--repetitions"
#define NO_POWERS_2 "--no-po2"
#define ESTIMATORS "--estimators"
#define OUTPUT_PATH "--out"

void split(const string &str, char delim, vector<string> &out) {
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
string join(vector<string> &strs, const string &delim) {
    string s = "";
    for(int i = 0; i < strs.size(); i++) {
        s += strs[i];
        if (i < strs.size() - 1) {
            s += delim;
        }
    }
    return s;
}

ExperimentConfig ExperimentConfig::parse(int argc, char **argv) {
    std::vector<std::string> arguments(argv + 1, argv + argc);
    ExperimentConfig config;
    for (int i = 0; i < arguments.size(); i++) {
        const string &arg = arguments[i];
        string value;
        if (i < arguments.size() - 1)
            value = arguments[i + 1];
        if (arg == INITIAL_TAGS) {
            config.initial_tags = stoi(value);
        } else if (arg == INCREMENT_TAGS) {
            config.tag_increment = stoi(value);
        } else if (arg == MAX_TAGS) {
            config.max_tags = stoi(value);
        } else if (arg == INITIAL_FRAME) {
            config.initial_frame = stoi(value);
        } else if (arg == REPETITIONS) {
            config.repetitions = stoi(value);
        } else if (arg == NO_POWERS_2) {
            config.no_power_of_2 = true;
        } else if (arg == OUTPUT_PATH) {
            config.output_path = value;
        } else if (arg == ESTIMATORS) {
            vector<string> estimators;
            split(value, ',', estimators);
            config.estimators = estimators;
        }
    }
    return config;
}

std::string ExperimentConfig::to_string() {
    string result = "ExperimentalConfig {";
    result += "\n  initial_frame = " + std::to_string(this->initial_frame);
    result += "\n  estimators = " + join(this->estimators, ", ");
    result += "\n  initial_tags = " + std::to_string(this->initial_tags);
    result += "\n  max_tags " + std::to_string(this->max_tags);
    result += "\n  incremet-tags " + std::to_string(this->tag_increment);
    result += "\n  repetitions " + std::to_string(this->repetitions);
    result += "\n  no-power-of-2 = " + std::to_string(this->no_power_of_2);
    result += "\n  output_path = " + this->output_path;
    result += "\n}";
    return result;
}
