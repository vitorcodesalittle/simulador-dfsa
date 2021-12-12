#include <iostream>

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
        cerr << "SHOUTE NOT IMPLEMENTED. CONTINUING" << endl;
        return NULL;
    } else if (estimatorName == "eom-lee") {
        cerr << "EOM-LEE NOT IMPLEMENTED. CONTINUING" << endl;
        return NULL;
    } else if (estimatorName == "iv2") {
        cerr << "IV2 NOT IMPLEMENTED. CONTINUING" << endl;
        return NULL;
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

int main(int argc, char **argv) {
    ExperimentConfig c = ExperimentConfig::parse(argc, argv);
    cout << c.to_string() << endl;
    map<pair<int, string>, Result> results;
    for (const string& estimatorName : c.estimators) {
        Estimator *e;
        e = create_estimator(estimatorName);
        if (e == nullptr) continue;
        for (int ntags = c.initial_tags;  ntags <= c.max_tags; ntags += c.tag_increment) {
            Result total{};
            for (int r = 0; r < c.repetitions; r++) {
                Simulator s = Simulator(c.initial_frame, *e);
                Result result = s.run(ntags);
                total += result;
            }
            total = total / c.repetitions;
            results[make_pair(ntags, estimatorName)] = total;
        }
    }
    string path = c.output_path;
    save_csv(path, results);

    return 0;
}