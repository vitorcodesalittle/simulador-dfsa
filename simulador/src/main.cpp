#include <iostream>

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
        cerr << "SHOUTE NOT IMPLEMENTED. CONTINUING" << endl;
        return NULL;
    } else if (estimatorName == "iv2") {
        cerr << "SHOUTE NOT IMPLEMENTED. CONTINUING" << endl;
        return NULL;
    }
}

int main(int argc, char **argv) {
    ExperimentConfig c = ExperimentConfig::parse(argc, argv);
    cout << c.to_string() << endl;
    for (int ntags = c.initial_tags;  ntags <= c.max_tags; ntags += c.tag_increment) {
        for (const string& estimatorName : c.estimators) {
            Estimator *e;
            e = create_estimator(estimatorName);
            if (e == NULL) continue;
            Simulator s = Simulator(c.initial_frame, *e);
            s.run(ntags);
            cout << "Estimador " << estimatorName << ' ' << "ntags " << ntags << endl;
            for (auto info : s.history) {
                cout << info.to_string() << endl;
            }
        }
    }
    return 0;
}
