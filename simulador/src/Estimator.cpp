#include <iostream>
#include <limits.h>
#include <bits/stdc++.h>
#include "Estimator.h"

// Não é usado
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

ull vogt(SlottedAlohaInfo &info, double s) {
	// TODO
	return -1;
}

double truncate(double num) {
	return trunc(num);
}

ull IV2Estimator::next_frames(SlottedAlohaInfo &info) {
		double sq2 = sqrt(2);
		double s = 1; // fator multiplicativo
		if (info.used_frame != info.colisoes) {
				return vogt(info, s);
		}
		double n = 2 * info.used_frame;
		double a0 = info.used_frame * pow((1 - 1/info.used_frame), n);
		double a1 = n * pow(1 - 1/info.used_frame, n-1);

		double delta = sq2 * sqrt(a0 * a0 + a1 * a1 + a0 * a1);
		delta = truncate(s * delta);
		double delta0 = delta + 1;

		while (delta < delta0) {
				n += 1;
				delta0 = delta;
				a0 =  info.used_frame * pow(1 - 1/info.used_frame, n);
				a1 =  n * pow(1 - 1/info.used_frame, n-1);
				delta = sq2 * sqrt(a0 * a0 + a1 * a1 + a0 * a1);
				delta = truncate(s * delta);
		}
		return n - 1;
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
