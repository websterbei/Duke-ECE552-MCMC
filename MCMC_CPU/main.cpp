#include <iostream>
#include <fstream>
#include "distribution_function.h"
#include "metropolis_hastings.h"

using namespace std;

int main(int argc, char* argv[]) {
    const int dimension = 2;
    const int num_samples = argc>1 ? atoi(argv[1]) : 100;
    double** samples = (double**)malloc(num_samples * sizeof(double*));
    for(int i=0; i<num_samples; i++) {
        samples[i] = (double*)malloc(dimension * sizeof(double));
    }
    metropolis_hastings(distribution_function, num_samples, dimension, samples);

    ofstream output_file;
    output_file.open("samples.csv");
    for(int i=0; i<num_samples; i++) {
        for(int j=0; j<dimension-1; j++) {
            output_file<<samples[i][j]<<",";
        }
        output_file<<samples[i][dimension]<<"\n";
    }
    output_file.close();
    return 0;
}