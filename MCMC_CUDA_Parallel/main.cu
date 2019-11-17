#include <iostream>
#include <fstream>
#include "metropolis_hastings.h"

using namespace std;

int main(int argc, char* argv[]) {
    const int dimension = 2;
    const int num_samples = argc>1 ? atoi(argv[1]) : 100;
    const int num_blocks = argc>3 ? atoi(argv[2]) : 1;
    const int num_threads = argc>3 ? atoi(argv[3]) : 1;
    // Memory allocation
    float** samples;
    cudaMallocManaged(&samples, num_samples*sizeof(float*));
    
    for(int i=0; i<num_samples; i++) {
        cudaMallocManaged(&samples[i], dimension*sizeof(float));
    }

    metropolis_hastings<<<num_blocks,num_threads>>>(num_samples, dimension, samples);
    cudaDeviceSynchronize();

    ofstream output_file;
    output_file.open("samples.csv");
    for(int i=0; i<num_samples; i++) {
        for(int j=0; j<dimension-1; j++) {
            output_file<<samples[i][j]<<",";
        }
        output_file<<samples[i][dimension-1]<<"\n";
    }
    output_file.close();
    return 0;
}