#include "metropolis_hastings.h"

/*
    dimension: length of parameter vector to the distribution function
*/
void _generate_initial_state(double initial_state[], int dimension) {
    srand(time(NULL));
    double random_max = (double) RAND_MAX;
    for(int i=0; i<dimension; i++) {
        initial_state[i] = 2*double(rand())/random_max - 1.0; //generate a number in [-1, 1]
    }
}

//Box muller method for sampling from Gaussian
double rand_normal(double mean, double stddev)
{
    static double n2 = 0.0;
    static int n2_cached = 0;
    if (!n2_cached)
    {
        double x, y, r;
        do
        {
            x = 2.0*rand()/RAND_MAX - 1;
            y = 2.0*rand()/RAND_MAX - 1;

            r = x*x + y*y;
        }
        while (r == 0.0 || r > 1.0);
        {
            double d = sqrt(-2.0*log(r)/r);
            double n1 = x*d;
            n2 = y*d;
            double result = n1*stddev + mean;
            n2_cached = 1;
            return result;
        }
    }
    else
    {
        n2_cached = 0;
        return n2*stddev + mean;
    }
}

void _propose_next_state(double current_state[], double next_state[], int dimension) {
    double random_max = (double) RAND_MAX;
    for(int i=0; i<dimension; i++) {
        next_state[i] = current_state[i] + rand_normal(0.0, 1.0); //random walk based on unit Gaussian output
    }
}

/*
    p: the distribution function
    num_samples: total number of samples to be generated
    dimension: length of parameter vector to the distribution function
*/
void metropolis_hastings(std::function<double (double[])> p, int num_samples, int dimension, double** samples) {
    double* current_state = (double*)malloc(dimension * sizeof(double));
    _generate_initial_state(current_state, dimension);
    for(int i=0; i<num_samples;) {
        double next_state[dimension];
        _propose_next_state(current_state, samples[i], dimension);
        current_state = samples[i];
        i++;
    }
}