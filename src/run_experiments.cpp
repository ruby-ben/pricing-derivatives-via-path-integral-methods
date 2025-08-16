#include <iostream>
#include <vector>
#include "../include/experiment_runner.h"

int main() {
    double S0 = 100.0;
    double K = 100.0;
    double r = 0.05;
    double sigma = 0.2;
    double T = 1.0;
    int N_steps = 252;

    std::vector<ExperimentConfig> configs = {
        {10, 3, "small"},
        {1000, 3, "medium"},
        {100000, 3, "large"}
    };

    ExperimentRunner runner(S0, K, r, sigma, T, N_steps, configs);
    runner.run_experiments();

    std::cout << "Experiments completed.\n";
    return 0;
}
