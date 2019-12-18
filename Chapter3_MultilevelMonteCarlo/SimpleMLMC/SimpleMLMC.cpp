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

	unsigned int m = 0;

	//
	// Perform the simulation of each multilevel Monte Carlo level
	//

	for (auto level = initialLevel+1; level <= stopLevel; level++) {
		int numberStepsf = pow(2, level);
		double dtf = T / static_cast<double>(numberStepsf);
		double sqrtdtf = sqrt(dtf);

		int numberStepsc = pow(2, level - 1);
		double dtc = T / static_cast<double>(numberStepsc);
		double sqrtdtc = sqrt(dtc);


		//
		// Perform the simulations
		//

		for (auto sim = 0; sim < initialSimulations; sim++) {
			auto Sf = S0;
			auto Sc = S0;

			//
			// Step through time
			//

			for (auto step = 0; step < numberStepsf; step++) {
				auto dWf1 = normal(generator) * sqrtdtf;
				auto dWf2 = normal(generator) * sqrtdtf;
				auto dWc = dWf1 + dWf2;

				// Fine 
				auto dSf = r * Sf * dtf + sigma * Sf * dWf1;
				Sf += dSf;
				dSf = r * Sf * dtf + sigma * Sf * dWf2;
				Sf += dSf;

				// Coarse
				auto dSc = r * Sc * dtc + sigma * Sc * dWc;
				Sc += dSc;
			}

			results[m] += Sf - Sc;
		}

		results[m] = results[m] / static_cast<double>(samples[level]);
		variance[m] = 0.0;

		m++;
	}



	std::cout << "Simulation results:" << std::endl
		<< "Analytical solution: " << analytical << std::endl
		<< "Simulation results:" << std::endl;

	for (auto level = 0; level < numberLevels; level++) {
		std::cout << "   Level[" << initialLevel + level << "] = " << results[level] << std::endl;
	}

/*
		<< "Simulation: " << ES << std::endl
		<< "Variance: " << variance << std::endl << std::endl
		<< "Error: " << std::scientific << ES - analytical << std::endl;
*/

	return _OKAY_;
}

