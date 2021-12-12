#include<iostream>
#include "Simulador.h"

int random_frame(ull number_of_frames) {
    return rand() % number_of_frames;
}
std::string Result::to_string() const {
    std::string result = "";
    result += "Result {";
    result += "\n  total_slots = " + std::to_string(total_slots);
    result += "\n  total_collisison_slots = " + std::to_string(total_collision_slots);
    result += "\n  total_empty_slots = " + std::to_string(total_empty_slots);
    result += "\n}";
    return result;
}
 Result Simulator::run(ull ntags) {
    ull nSuccess = 0;
    Result result{};
    while (true) {
        std::unordered_map<ull, ull> frames;
        for (int i = 0; i < ntags - nSuccess; i++) {
            int f = random_frame(current_frame);
            if (!frames.count(f)) {
                frames[f] = 1;
            } else {
                frames[f]++;
            }
        }
        ull success = 0, colisoes = 0;
        for (auto p : frames) {
            ull count = p.second;
            success += count == 1;
            colisoes += count > 1;
        }
        ull vazios = (current_frame - success - colisoes);
        result.total_collision_slots += colisoes;
        result.total_empty_slots += vazios;
        result.total_slots += current_frame;
        auto info = SlottedAlohaInfo(success, colisoes, vazios);
        ull next_frames = estimator.next_frames(info);
        history.push_back(info);
        if (info.colisoes == 0) {
            break;
        }
        nSuccess += success;
        current_frame = next_frames;
        frames.clear();
    }
     return result;
}
