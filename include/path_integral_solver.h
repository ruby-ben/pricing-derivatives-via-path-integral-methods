#ifndef PATH_INTEGRAL_SOLVER_H
#define PATH_INTEGRAL_SOLVER_H

#include <functional>
#include <vector>
#include <string>
#include "black_scholes.h"

// Struct to hold simulation results
struct SimulationResult {
    double price;
    std::vector<std::vector<double>> paths;
    std::vector<double> timestamps;
};

// Original function declaration (keep this for backward compatibility)
double path_integral_price(
    double S0,
    double r,
    double T,
    int N_paths,
    int N_steps,
    std::function<double(double,double)> drift,
    std::function<double(double,double)> vol,
    std::function<double(double)> payoff
);

// New function that returns paths and optionally saves to CSV
SimulationResult path_integral_price_with_paths(
    double S0,
    double K,
    double r,
    double T,
    int N_paths,
    int N_steps,
    std::function<double(double,double)> drift,
    std::function<double(double,double)> vol,
    std::function<double(double)> payoff,
    const ModelInfo& model_info,
    int paths_to_save = 10,
    bool save_to_csv = false
);

std::string generate_filename(
    const ModelInfo& model,
    double S0,
    double K,
    double T,
    int N_steps,
    int N_paths
);

#endif