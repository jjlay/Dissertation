

/*
 * Welford online variance calculator
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
 * October 2018
 *
 * DATE        AUTHOR  COMMENTS
 * ----------  ------  ---------------
 * 2018-12-16  JJL     Initial version
 *
 */


//
// Local includes
//

#include "../Common/Welford.h"
#include "../Common/ReturnValues.h"


//
// Standard includes
//

#include <random>
#include <math.h>
#include <iostream>
#include <iomanip>


//
// Function: main()
//
// Parameters:
//
// Returns:
//

int main(int argc, char* argv[]) {

	//
	// Values for checking the Welford algorithm
	//

	const double testMean = 0.0;
	const double testVariance = 10.0;
	const unsigned int testSamples = static_cast<unsigned int>(1E8);


	//
	// Required Welford temp variables
	//

	double count = 0.0, mean = 0.0, M2 = 0.0;

	//
	// Random number generator
	//

	std::default_random_engine generator;
	std::normal_distribution<double> normal_distribution(testMean, sqrt(testVariance));

	//
	// Perform test
	//

	for (auto sample = 0; sample < testSamples; sample++) {
		auto x = normal_distribution(generator);

		welford(&count, &mean, &M2, x);
	}

	auto var = welfordVariance(&count, &mean, &M2);

	std::cout << "Welford results" << std::endl
		<< "Test values:" << std::endl
		<< "mean = " << std::fixed << std::setprecision(4) << mean << std::endl
		<< "variance = " << std::fixed << std::setprecision(4) << testVariance << std::endl
		<< "samples = " << std::scientific << std::setprecision(1) << static_cast<double>(testSamples) << std::endl
		<< std::endl
		<< "Results:" << std::endl
		<< "mean = " << std::fixed << std::setprecision(4) << mean << std::endl
		<< "variance = " << std::fixed << std::setprecision(4) << var << std::endl
		<< std::endl
		<< "Error:" << std::endl
		<< "mean = " << std::scientific << std::setprecision(2) << mean - testMean << std::endl
		<< "variance = " << std::scientific << std::setprecision(2) << var - testVariance << std::endl
		<< std::endl;


	//
	// Wrap up
	//

	return _OKAY_;
}
