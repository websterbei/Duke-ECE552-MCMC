#include <iostream>
#include "distribution_function.h"
#include "metropolis_hastings.h"

using namespace std;

int main() {
    const int dimension = 2;
    const int num_samples = 20;
    double** samples = (double**)malloc(num_samples * sizeof(double*));
    for(int i=0; i<num_samples; i++) {
        samples[i] = (double*)malloc(dimension * sizeof(double));
    }
    metropolis_hastings(distribution_function, num_samples, dimension, samples);
    for(int i=0; i<num_samples; i++) {
        cout<<samples[i][0]<<" "<<samples[i][1]<<endl;
    }
    return 0;
}