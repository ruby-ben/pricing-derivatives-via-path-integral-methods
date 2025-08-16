#include "../include/experiment_runner.h"
#include "../include/path_integral_solver.h"

ExperimentRunner::ExperimentRunner(double S0, double K, double r, double sigma, double T,
                                   int N_steps, const std::vector<ExperimentConfig>& configs)
    : S0_(S0), K_(K), r_(r), sigma_(sigma), T_(T), N_steps_(N_steps), configs_(configs) {}

ExperimentResult ExperimentRunner::run_single_experiment(const ExperimentConfig& config) {
    ExperimentResult result;
    result.label = config.label;

    std::vector<RollingStats> rolling(N_steps_ + 1);

    for(int p = 0; p < config.num_paths; ++p) {
        std::vector<double> path = PathIntegralSolver::simulate_path(S0_, r_, sigma_, T_, N_steps_);
        for(int t = 0; t <= N_steps_; ++t) {
            rolling[t].add(path[t]);
        }
    }

    result.mean_paths.resize(N_steps_ + 1);
    result.std_error_paths.resize(N_steps_ + 1);
    for(int t = 0; t <= N_steps_; ++t) {
        result.mean_paths[t] = rolling[t].mean();
        result.std_error_paths[t] = rolling[t].std_error();
    }

    return result;
}

void ExperimentRunner::run_experiments() {
    for(const auto& config : configs_) {
        std::cout << "Running experiment: " << config.label
                  << " with " << config.num_paths << " paths\n";

        ExperimentResult res = run_single_experiment(config);

        std::cout << "Final mean: " << res.mean_paths.back()
                  << ", Std error: " << res.std_error_paths.back() << "\n";
    }
}
