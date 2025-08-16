#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

// Experiment configuration
struct ExperimentConfig {
    int num_paths;
    int num_repeats; // optional for future
    std::string label;
};

// Rolling statistics for a timestep
struct RollingStats {
    double sum = 0.0;
    double sum_sq = 0.0;
    int count = 0;

    void add(double x) {
        sum += x;
        sum_sq += x*x;
        count++;
    }

    double mean() const {
        return (count == 0) ? 0.0 : sum / count;
    }

    double std_error() const {
        return (count <= 1) ? 0.0 : std::sqrt((sum_sq / count - mean()*mean()) / count);
    }
};

// Result of a single experiment
struct ExperimentResult {
    std::string label;
    std::vector<double> mean_paths;
    std::vector<double> std_error_paths;
};

class ExperimentRunner {
public:
    ExperimentRunner(double S0, double K, double r, double sigma, double T,
                     int N_steps, const std::vector<ExperimentConfig>& configs);

    ExperimentResult run_single_experiment(const ExperimentConfig& config);
    void run_experiments();

private:
    double S0_, K_, r_, sigma_, T_;
    int N_steps_;
    std::vector<ExperimentConfig> configs_;
};
