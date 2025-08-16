#include <functional>
#include <random>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include "../include/path_integral_solver.h"

double path_integral_price(
    double S0,
    double r, 
    double T, 
    int N_paths,
    int N_steps,
    std::function<double(double,double)> drift,
    std::function<double(double,double)> vol,
    std::function<double(double)> payoff
) {
    // std::mt19937_64 rng(42); // deterministic seed
    std::mt19937_64 rng(std::random_device{}());
    std::normal_distribution<> norm(0.0, 1.0);

    double dt = T / N_steps;
    double payoff_sum = 0.0;

    for (int i = 0; i < N_paths; ++i) {
        double S = S0;
        for (int step = 0; step < N_steps; ++step) {
            double dW = std::sqrt(dt) * norm(rng);
            S += drift(S, step*dt) * dt + vol(S, step*dt) * dW;
        }
        payoff_sum += payoff(S);
    }

    return std::exp(-r * T) * (payoff_sum / N_paths);
}

std::string generate_filename(
    const ModelInfo& model,
    double S0,
    double K,
    double T,
    int N_steps,
    int N_paths
) {
    std::stringstream ss;
    ss << "../data/"
       << model.model_name << "_"
       << "S" << S0 << "_"
       << "K" << K << "_"
       << "r" << model.drift_param << "_"
       << "sigma" << model.vol_param << "_"
       << "T" << T << "_"
       << "steps" << N_steps << "_"
       << "paths" << N_paths
       << ".csv";
    return ss.str();
}

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
    int paths_to_save,
    bool save_to_csv
) {
    // std::mt19937_64 rng(42);
    std::mt19937_64 rng(std::random_device{}());
    std::normal_distribution<> norm(0.0, 1.0);

    double dt = T / N_steps;
    double payoff_sum = 0.0;

    // Initialize vectors to store paths and timestamps
    std::vector<std::vector<double>> saved_paths(paths_to_save, std::vector<double>(N_steps + 1));
    std::vector<double> avg_path(N_steps + 1, 0.0);
    std::vector<double> timestamps(N_steps + 1);

    // Generate timestamps
    for (int i = 0; i <= N_steps; ++i) {
        timestamps[i] = i * dt;
    }

    for (int i = 0; i < N_paths; ++i) {
        double S = S0;
        
        // Store initial values
        if (i < paths_to_save) {
            saved_paths[i][0] = S0;
        }
        avg_path[0] += S0;

        for (int step = 0; step < N_steps; ++step) {
            double dW = std::sqrt(dt) * norm(rng);
            S += drift(S, step*dt) * dt + vol(S, step*dt) * dW;
            
            if (i < paths_to_save) {
                saved_paths[i][step + 1] = S;
            }
            avg_path[step + 1] += S;
        }
        payoff_sum += payoff(S);
    }

    // Calculate average path
    for (auto& val : avg_path) {
        val /= N_paths;
    }
    saved_paths.push_back(avg_path);

    // Save to CSV if requested
    if (save_to_csv) {
        std::filesystem::create_directories("../data");
        
        std::string filename = generate_filename(
            model_info, S0, K, T, N_steps, N_paths
        );
        
        std::ofstream file(filename);
        file << std::setprecision(6) << std::fixed;

        // Write header
        file << "time";
        for (int i = 0; i < paths_to_save; ++i) {
            file << ",path_" << i;
        }
        file << ",average_path\n";

        // Write data
        for (size_t i = 0; i <= N_steps; ++i) {
            file << timestamps[i];
            for (const auto& path : saved_paths) {
                file << "," << path[i];
            }
            file << "\n";
        }
    }

    return {
        std::exp(-r * T) * (payoff_sum / N_paths),
        saved_paths,
        timestamps
    };
}
