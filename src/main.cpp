#include <iostream>
#include <functional>
#include "../include/path_integral_solver.h"
#include "../include/black_scholes.h"

int main(int argc, char* argv[]) {
    // Parameters
    double S0 = 100.0;
    double K = 100.0;
    double r = 0.05;
    double sigma = 0.2;
    double T = 1.0;
    int N_paths = 100000;
    int N_steps = 252;
    int paths_to_save = 10;
    
    bool save_to_csv = (argc < 2) || std::string(argv[1]) == "1";

    auto drift = bs_drift(r);
    auto vol = bs_vol(sigma);
    auto model_info = get_model_info(r, sigma);
    
    auto payoff = [K](double S_T) {
        return std::max(S_T - K, 0.0);
    };

    auto result = path_integral_price_with_paths(
        S0, K, r, T, N_paths, N_steps,
        drift, vol, payoff,
        model_info, paths_to_save, save_to_csv
    );

    std::cout << "European Call Option Price: " << result.price << std::endl;
    if (save_to_csv) {
        std::cout << "Paths saved with model parameters in ../data/" << std::endl;
    }

    return 0;
}
