#include <iostream>
#include<chrono>
#include <map>
#include <fstream>
#include "config.h"
#include "Estimator.h"
#include "Simulador.h"

using namespace std;

Estimator* create_estimator(const string &estimatorName) {
    if (estimatorName == "lb") {
        return new LowerBoundEstimator();
    } else if (estimatorName == "shoute")  {
        return new ShoutEstimator();
    } else if (estimatorName == "eom-lee") {
        return new EomLeeEstimator();
    } else if (estimatorName == "iv2") {
        return new IV2Estimator();
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
        // srand(time(NULL));
    cout << c.to_string() << endl;
    map<pair<int, string>, Result> results;
    int t = c.estimators.size() * c.repetitions * (c.max_tags-c.initial_tags+ c.tag_increment - 1) / c.tag_increment, i = 0;
    for (const string& estimatorName : c.estimators) {
        Estimator *e;
        e = create_estimator(estimatorName);
        if (e == nullptr) continue;
        for (int ntags = c.initial_tags;  ntags <= c.max_tags; ntags += c.tag_increment) {
            Result total{};
            long last = get_seed();
            for (int r = 0; r < c.repetitions; r++) {
                Simulator s = Simulator(c.initial_frame, *e, !c.no_power_of_2);
                srand(last);
                Result result = s.run(ntags);
                auto new_seed = get_seed();
                if (new_seed == last) {
                    cerr << "SAME SEED AGAIN\n";
                    return 1;
                } else last = new_seed;

                total += result;
                if (i % 100 == 0){
                    cout.flush();
                    cout << '\r' << "Progresso:" <<  (double) i*100/t << " %";
                }
                i++;
            }
            total = total / c.repetitions;
            results[make_pair(ntags, estimatorName)] = total;
        }
    }
    string path = c.output_path;
    cout << endl <<  "Finished. Saving results at " << path + ".csv" << endl;
    save_csv(path, results);

    return 0;
}
