#include "Simulador.h"

int random_frame(ull number_of_frames) {
    return rand() % number_of_frames;
}
 void Simulator::run(int ntags) {
    int nSuccess = 0;
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
        ull success = 0, colisoes = 0, vazios = 0;
        for (auto p : frames) {
            ull count = p.second;
            success += count == 1;
            colisoes += count > 1;
            vazios += count == 0;
        }
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
}
