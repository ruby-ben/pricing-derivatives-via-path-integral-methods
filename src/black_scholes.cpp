#include <functional>
#include "../include/black_scholes.h"

std::function<double(double,double)> bs_drift(double r) {
    return [r](double S, double t) {
        return r * S;
    };
}

std::function<double(double,double)> bs_vol(double sigma) {
    return [sigma](double S, double t) {
        return sigma * S;
    };
}

ModelInfo get_model_info(double r, double sigma) {
    return ModelInfo{
        "BlackScholes",
        r,
        sigma
    };
}
