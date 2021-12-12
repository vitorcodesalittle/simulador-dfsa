
#include <bits/stdc++.h>
#include "Estimator.h"
//
// Created by vilma on 12/11/21.
//

ull min (ull a, ull b) { return (a < b) ? a : b; }

ull Estimator::next_frames(SlottedAlohaInfo &info) {
    return info.colisoes;
}
ull LowerBoundEstimator::next_frames(SlottedAlohaInfo &info) {
    return min(info.colisoes * 2, 256);
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
