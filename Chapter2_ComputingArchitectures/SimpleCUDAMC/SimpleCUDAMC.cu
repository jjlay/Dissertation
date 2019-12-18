/*
 * Simple Monte Carlo
 * Single Threaded CPU Version
 *
 * JJ Lay
 * Middle Tennessee State University
 * October 2014
 *
 * DATE        AUTHOR  COMMENTS
 * ----------  ------  ---------------
 * 2014-10-07  JJL     Initial version
 *
 *
 */


//
// CUDA includes
//

#include "cuda_runtime.h"
#include "device_launch_parameters.h"


//
// Local includes
//

#include "ReturnValues.h"
#include "kernel.cuh"


//
// Standard includes
//

#include <iostream>
#include <random>


//
// Function: main()
//
// Parameters:
//    argc - Number of command line parameters
//    argv[] - Command line parameters
//
// Returns:
//    Completion status
//

int main(int argc, char* argv[]) {

	// Random number

	std::default_random_engine generator;
	std::normal_distribution<double> normal(0, 1);


	// Monte Carlo Parameters

	const int numberSteps = 1000;
	const int numberSimulations = 10000;

	// Black-Scholes parameters

	const double T = 1.0;
	const double r = 0.03;
	const double sigma = 0.03;
	const double S0 = 100.0;

	double dt = T / static_cast<double>(numberSteps);
	double sqrtdt = sqrt(dt);

	double analytical = S0 * exp(r * T);

	double sumS = 0.0;

	for (auto sim = 0; sim < numberSimulations; sim++) {
		auto S = S0;

		for (auto step = 0; step < numberSteps; step++) {
			auto dW = normal(generator) * sqrtdt;
			auto dS = r * S * dt + sigma * S * dW;
			S += dS;
		}

		sumS += S;
	}

	auto ES = sumS / static_cast<double>(numberSimulations);
	double variance = 0.0;

	std::cout << "Simulation results:" << std::endl
		<< "Analytical solution: " << analytical << std::endl
		<< "Simulation: " << ES << std::endl
		<< "Variance: " << variance << std::endl << std::endl
		<< "Error: " << std::scientific << ES - analytical << std::endl;

	return _OKAY_;
}
