#include <iostream>
#include <limits.h>
#include <bits/stdc++.h>
#include "Estimator.h"

ull min (ull a, ull b) { return (a < b) ? a : b; }

ull Estimator::next_frames(SlottedAlohaInfo &info) {
    return info.colisoes;
}
ull LowerBoundEstimator::next_frames(SlottedAlohaInfo &info) {
    return info.colisoes * 2;
}

ull ShoutEstimator::next_frames(SlottedAlohaInfo &info) {
    return static_cast<ull>(ceil(2.39 * info.colisoes));
}

double abs(double k) {
    if (k < 0) return - k;
    return k;
}

ull EomLeeEstimator::next_frames(SlottedAlohaInfo &info) {
    double threshold = 5e-5;
    double L = static_cast<double>(info.used_frame);
    double gamma_k, gamma = 2, beta = std::numeric_limits<double>::max();
    do {
        gamma_k = gamma;
        beta = L / ((gamma_k * info.colisoes) + info.sucessos);
        gamma = (1 - exp(-1.0/beta)) / (beta * (1 - (1 + 1.0/beta) * exp(-1.0/beta)) + 5e-10);
    } while (abs(gamma - gamma_k) > threshold);
    return static_cast<ull>(ceil(gamma * info.colisoes));
}

std::string SlottedAlohaInfo::to_string() {
    std::string result = "";
    result += "Info {";
    result += "\n  sucessos = " + std::to_string(sucessos);
    result += "\n  colisoes = " + std::to_string(colisoes);
    result += "\n  vazios = " + std::to_string(vazios);
    result += "\n}";
    return result;
}
