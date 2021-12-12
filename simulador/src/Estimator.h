#ifndef SIMULADOR_ESTIMATOR_H
#define SIMULADOR_ESTIMATOR_H

typedef unsigned long long ull;

class SlottedAlohaInfo {
public:
    ull sucessos;
    ull colisoes;
    ull vazios;
    SlottedAlohaInfo(ull sucessos, ull colisoes, ull vazios):
    sucessos {sucessos},
    colisoes { colisoes },
    vazios {vazios}
    {}
    std::string to_string();

};

class Estimator {
public:
    virtual ull next_frames(SlottedAlohaInfo &info);
};

class LowerBoundEstimator: public Estimator {
    ull next_frames(SlottedAlohaInfo &info) override;
};

#endif //SIMULADOR_ESTIMATOR_H
