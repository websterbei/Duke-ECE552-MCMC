#include <functional>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void metropolis_hastings(std::function<double (double[])> p, int num_samples, int dimension, double** samples);