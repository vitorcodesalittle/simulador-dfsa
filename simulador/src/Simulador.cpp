#include<chrono>
#include<iostream>
#include "Simulador.h"

int random_slot(ull frame_size) {
    return rand() % frame_size;
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
// see https://imgur.com/a/EcFLMCj
ull get_closest_po2(ull n) {
    if (n <= 5) return 4;
    ull next_power = 2;
    while (next_power < n) {
        next_power << 1;
    }
    ull last_power = next_power >> 1;
    if (next_power - n <= n - last_power) return next_power;
    return last_power;
}

 Result Simulator::run(ull ntags) {
    ull nSuccess = 0;
    Result result{};
    while (true) {
        std::unordered_map<ull, ull> slots_counter;
        for (int i = 0; i < ntags - nSuccess; i++) {
            int f = random_slot(current_frame);
            if (!slots_counter.count(f)) {
                slots_counter[f] = 1;
            } else {
                slots_counter[f]++;
            }
        }
        ull success = 0, colisoes = 0;
        for (auto p : slots_counter) {
            ull count = p.second;
            success += count == 1;
            colisoes += count > 1;
        }
        ull vazios = (current_frame - success - colisoes);
        auto info = SlottedAlohaInfo(success, colisoes, vazios, current_frame);
        history.push_back(info);
        auto t0 = std::chrono::high_resolution_clock::now();
        ull next_frames = estimator.next_frames(info);
        long long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - t0).count();
        result.total_collision_slots += colisoes;
        result.total_empty_slots += vazios;
        result.total_slots += current_frame;
        result.time += ns;
        if (info.colisoes == 0) {
            break;
        }
        nSuccess += success;
        if (use_power_of_2) {
            current_frame = get_closest_po2(next_frames);
        } else {
            current_frame = next_frames;
        }
        slots_counter.clear();
    }
     return result;
}
