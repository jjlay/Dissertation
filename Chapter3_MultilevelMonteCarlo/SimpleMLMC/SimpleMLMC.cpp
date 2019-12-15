/*
 * Simple Multilevel Monte Carlo
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
// Local includes
//

#include "ReturnValues.h"


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

	const int initialLevel = 0;
	const int numberLevels = 5;
	const int stopLevel = initialLevel + numberLevels - 1;
	const int initialSimulations = 10000;

	// Black-Scholes parameters

	const double T = 1.0;
	const double r = 0.03;
	const double sigma = 0.03;
	const double S0 = 100.0;

	double analytical = S0 * exp(r * T);

	auto samples = new unsigned int[numberLevels];
	auto results = new double[numberLevels];
	auto variance = new double[numberLevels];

	for (auto level = 0; level < numberLevels; level++) {
		samples[level] = initialSimulations;
		results[level] = 0.0;
		variance[level] = 0.0;
	}

	double sumS = 0.0;
	unsigned int m = 0;

	for (auto level = initialLevel; level <= stopLevel; level++) {
		int numberSteps = pow(2, level);

		double dt = T / static_cast<double>(numberSteps);
		double sqrtdt = sqrt(dt);

		for (auto sim = 0; sim < initialSimulations; sim++) {
			auto S = S0;

			for (auto step = 0; step < numberSteps; step++) {
				auto dW = normal(generator) * sqrtdt;
				auto dS = r * S * dt + sigma * S * dW;
				S += dS;
			}

			sumS += S;
		}

		results[m] = sumS / static_cast<double>(samples[level]);
		variance[m] = 0.0;

		m++;
	}


/*
	std::cout << "Simulation results:" << std::endl
		<< "Analytical solution: " << analytical << std::endl
		<< "Simulation: " << ES << std::endl
		<< "Variance: " << variance << std::endl << std::endl
		<< "Error: " << std::scientific << ES - analytical << std::endl;
*/

	return _OKAY_;
}

