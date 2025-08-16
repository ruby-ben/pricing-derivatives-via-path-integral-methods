#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include <functional>
#include <string>

struct ModelInfo {
    std::string model_name;
    double drift_param;
    double vol_param;
};

std::function<double(double,double)> bs_drift(double r);
std::function<double(double,double)> bs_vol(double sigma);
ModelInfo get_model_info(double r, double sigma);

#endif