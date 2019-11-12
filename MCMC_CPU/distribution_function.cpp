#include "distribution_function.h"

double distribution_function(double x[]) {
    double exponent = -((x[0]-ux) * (x[0]-ux))/(2*sx*sx) - ((x[1]-uy) * (x[1]-uy))/(2*sy*sy);
    double probability = exp(exponent);
    return probability;
}