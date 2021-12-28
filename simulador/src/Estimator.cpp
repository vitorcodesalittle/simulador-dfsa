#include <iostream>
#include <limits.h>
#include <bits/stdc++.h>
#include "Estimator.h"
#include "Vec3.h"

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


ull EomLeeEstimator::next_frames(SlottedAlohaInfo &info) {
    double threshold = 1e-3;
    double L = static_cast<double>(info.used_frame);
    double gamma_k, gamma = 2, beta = std::numeric_limits<double>::max();
    do {
        gamma_k = gamma;
        beta = L / ((gamma_k * info.colisoes) + info.sucessos);
        gamma = (1 - exp(-1.0/beta)) / (beta * (1 - (1 + 1.0/beta) * exp(-1.0/beta)));
    } while (abs(gamma - gamma_k) > threshold);
    return static_cast<ull>(ceil(gamma * info.colisoes));
}

ull IV2Estimator::combinations(ull n, ull k) {
	if (k > n) return 0;
	if (k * 2 > n) k = n-k;
	if (k == 0) return 1;
	int result = n;
	for( int i = 2; i <= k; ++i ) {
		result *= (n-i+1);
		result /= i;
	}
	return result;
}

ull IV2Estimator::estimate(ull L, ull r, ull n) {
    return L * combinations(n, r) * pow(1.0/L, r) * pow(1 - 1.0/L, n-r);
}

double IV2Estimator::calc_epsilon(SlottedAlohaInfo &info, ull n) {
    ull a0 = estimate(info.used_frame, 0, n); // estimativa vazios
    ull a1 = estimate(info.used_frame, 1, n); // estimativa sucessos
    ull arest = 0; // estimativas colisões acumulada
    for (int r = 2; r <= n; r++) {
        arest += estimate(info.used_frame, r, n);
    }
    return (Vec3{a0, a1, arest} - Vec3{info.vazios, info.sucessos, info.colisoes}).len();
}

ull IV2Estimator::next_frames_vogt(SlottedAlohaInfo &info) {
    double high = 3e3, low = 2;
    while (high - low > 1) {
        double nhigh = calc_epsilon(info , high);
        double nlow = calc_epsilon(info, low);
        double m = (high - low) / 2;
        if (nhigh < nlow) low = low + m;
        else high = high - m;
    }
    return static_cast<ull>(ceil(low));
}

ull IV2Estimator::next_frames(SlottedAlohaInfo &info) {
    if (info.used_frame != info.colisoes) {
        return next_frames_vogt(info);
    }
    double s;
    if (initial_frame_size <= 64) s = 100;
    else s = 10000;
    double n;
    if (s == 100) n = 6.851851850 * (info.used_frame - 1) +  2;
    else if (s == 1000) n = 9.497497500 * (info.used_frame-1) + 2;
    else if (s == 10000) n = 12.047047047 * (info.used_frame-1) + 2;
    return static_cast<ull>(ceil(n));
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
