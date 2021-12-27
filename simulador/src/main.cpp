#include <iostream>
#include<chrono>
#include <map>
#include <fstream>
#include "config.h"
#include "Estimator.h"
#include "Simulador.h"

using namespace std;

Estimator* create_estimator(const string &estimatorName, const ExperimentConfig &c) {
    if (estimatorName == "lb") {
        return new LowerBoundEstimator();
    } else if (estimatorName == "shoute")  {
        return new ShoutEstimator();
    } else if (estimatorName == "eom-lee") {
        return new EomLeeEstimator();
    } else if (estimatorName == "iv2") {
        return new IV2Estimator(c.initial_frame);
    } else {
        std::cerr<<"Not implemented: " << estimatorName << std::endl;
        exit(1);
    }
}

std::string row_string(ull ntags, const string &estimator, Result r) {
    return to_string(ntags) + ',' + estimator + ',' + to_string(r.total_collision_slots) + ',' + to_string(r.total_empty_slots) + ',' + to_string(r.total_slots) + ',' + to_string(r.time);
}

void save_csv(const string &filepath, const map<pair<int, string>, Result> &results) {
    ofstream f;
    f.open(filepath + ".csv");

    f << "ntags,estimador,total_collisions_slots,total_empty_slots,total_slots,time\n";
    for (auto p : results) {
        auto ntags = p.first.first;
        string estimator = p.first.second;
        Result r = p.second;
        f << row_string(ntags, estimator, r) << '\n';
    }
    f.close();
}

// from https://stackoverflow.com/questions/31255486/c-how-do-i-convert-a-stdchronotime-point-to-long-and-back
long get_seed() {
    auto now =chrono::high_resolution_clock::now();
    chrono::time_point_cast<chrono::nanoseconds>(now);
    auto epoch = now.time_since_epoch();
    auto value = chrono::duration_cast<chrono::nanoseconds>(epoch);
    long duration = value.count();
    return duration;
}

int main(int argc, char **argv) {
    ExperimentConfig c = ExperimentConfig::parse(argc, argv);
    cout << c.to_string() << endl;
    map<pair<int, string>, Result> results;
    int t = c.estimators.size() * c.repetitions * (c.max_tags-c.initial_tags+ c.tag_increment - 1) / c.tag_increment, i = 0;
    // srand(get_seed());
    for (const string& estimatorName : c.estimators) {
        Estimator *e = create_estimator(estimatorName, c);
        for (int ntags = c.initial_tags;  ntags <= c.max_tags; ntags += c.tag_increment) {
            Result total{};
            Simulator(c.initial_frame, *e, !c.no_power_of_2).run(ntags); // warm
            Simulator(c.initial_frame, *e, !c.no_power_of_2).run(ntags); //  up
            for (int r = 0; r < c.repetitions; r++) {
                Simulator s = Simulator(c.initial_frame, *e, !c.no_power_of_2);
                srand(get_seed());
                Result result = s.run(ntags);
								// cout << "TOTAL BEFORE: " << total.to_string() << endl;
                total += result;
								// cout << "TOTAL AFTER: " << total.to_string() << endl;
                if (++i % 100 == 0){
                    cout.flush();
                    cout << '\r' <<  (double) i*100/t << " %" << " of the total simulations. Benchmarking " << estimatorName;
                }
            }
						// cout << "TOTAL BFORE: " << total.to_string() << endl;
            total = total / c.repetitions;
						// cout << "TOTAL AFTER: " << total.to_string() << endl;
            results[make_pair(ntags, estimatorName)] = total;
        }
    }
    string path = c.output_path;
    cout << endl <<  "Finished. Saving results at " << path + ".csv" << endl;
    save_csv(path, results);

    return 0;
}
