#include "utils.h"

double MSV(std::vector<double> data) {
    double res = 0;
    for (double value : data) {
        res += value * value;
    }
    res /= data.size();
    return std::sqrt(res);
}
