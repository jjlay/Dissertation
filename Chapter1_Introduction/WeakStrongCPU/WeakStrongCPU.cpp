
/*
 * Weak Error and Strong Error Estimation of European Put
 * Euler-Muryama Method with Monte Carlo
 *
 * See also
 * Lay, H., Colgin, Z., Reshniak, V., Khaliq, A.Q.M. (2018).
 * "On the implementation of multilevel Monte Carlo simulation
 * of the stochastic volatility and interest rate model using
 * multi-GPU clusters." Monte Carlo Methods and Applications,
 * 24(4), pp. 309-321.
 *
 * JJ Lay
 * Middle Tennessee State University
 * October 2014
 *
 * DATE        AUTHOR  COMMENTS
 * ----------  ------  ---------------
 * 2017-11-01  JJL     Initial version
 *
 */

//
// Standard Includes
//

#include <iostream>
#include <math.h>
#include <random>


//
// Local Includes
//

#include "ReturnValues.h"


//
// Function: main()
//
// Parameters:
//
// Returns:
//

int main(int argc, char* argv[]) {

	// Random number

	std::default_random_engine generator;
	std::normal_distribution<double> normal(0, 1);


	// Monte Carlo Parameters

	const unsigned int numberSteps = 500;
	const unsigned int numberSamples = static_cast<unsigned int>(1E5);


	// Black-Scholes Parameters

	const double r = 0.04;
	const double T = 1.00;
	const double v = 0.10;
	const double S0 = 100.0;

	const double analytical = S0 * exp(r * T);

	double dt = T / static_cast<double>(numberSteps);
	double sqrtdt = sqrt(dt);

	double S = 0.0, dS = 0.0, dW = 0.0;

	// Error variables

	double sumS = 0.0, sumError = 0.0, sumS2 = 0.0;

	// Perform simulation

	for (auto sample = 0; sample < numberSamples; sample++) {

		S = S0;

		for (auto step = 0; step < numberSteps; step++) {
			dW = normal(generator) * dt;
			dS = r * S * dt + v * S * dW;

			S += dS;
		}

		sumS += S;
		sumS2 += S * S;
		sumError += abs(S - analytical);
	}

	// Calculate results

	double mean = sumS / static_cast<double>(numberSamples);
	double strongError = abs(mean - analytical);
	double weakError = sumError / static_cast<double>(numberSamples);

	// Display results

	std::cout << "E[S] = " << std::fixed << mean << std::endl
		<< "Analytical = " << std::fixed << analytical << std::endl
		<< "Strong error = " << std::scientific << strongError << std::endl
		<< "Weak error = " << std::scientific << weakError << std::endl << std::endl;

	return _OKAY_;
}
