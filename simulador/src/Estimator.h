#ifndef SIMULADOR_ESTIMATOR_H
#define SIMULADOR_ESTIMATOR_H

typedef unsigned long long ull;

class SlottedAlohaInfo {
public:
    ull used_frame;
    ull sucessos;
    ull colisoes;
    ull vazios;
    SlottedAlohaInfo(ull sucessos, ull colisoes, ull vazios, ull used_frame):
    sucessos {sucessos},
    colisoes { colisoes },
    vazios {vazios},
    used_frame(used_frame)
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

class ShoutEstimator: public Estimator {
    ull next_frames(SlottedAlohaInfo &info) override;
};

class EomLeeEstimator : public Estimator {
    ull next_frames(SlottedAlohaInfo &info) override;

};

class IV2Estimator : public Estimator {
public:
    ull initial_frame_size;
    ull next_frames(SlottedAlohaInfo &info) override;

    IV2Estimator(ull ifs): initial_frame_size{ifs} {};
};

#endif //SIMULADOR_ESTIMATOR_H

