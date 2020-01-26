/*
 * Welford online variance calculator
 *
 * See also
 *
 * Welford, B. P. (1962). "Note on a method for calculating
 * corrected sums of squares and products".
 * Technometrics. 4 (3), pp. 419–420.
 *
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

#include "Welford.h"


//
// Standard includes
//

#include <random>
#include <iostream>
#include <iomanip>


//
// Function: main()
//

int main(int argc, char* argv[]) {

	//////////////////////
	//
	// Welford parameters
	//

	//	void welford(double* pcount, double* pmean, double* pM2, double pNewValue);
	//	double welfordVariance(double* pCount, double* pMean, double* pM2);

	double count = 0.0, mean = 0.0, M2 = 0.0, x = 0.0;
	int samples = 1000000;

	auto storage = new double[samples];

	for (auto i = 0; i < samples; i++)
		storage[i] = 0.0;


	//////////////////////
	//
	// Random parameters
	//

	double randMean = 2.0, randStdDev = 3.0;
	std::default_random_engine generator;
	std::normal_distribution<double> normal(randMean, randStdDev);


	//////////////////////
	//
	// Collect the data
	//

	for (auto i = 0; i < samples; i++) {
		// Take our random number
		x = normal(generator);

		storage[i] = x;
		welford(&count, &mean, &M2, x);
	}

	//////////////////////
	//
	// Calculate the statistics with two passes
	//

	double pass2Mean = 0.0, pass2Variance = 0.0;

	// Mean

	for (auto i = 0; i < samples; i++) {
		pass2Mean += storage[i];
	}

	pass2Mean = pass2Mean / static_cast<double>(samples);

	// Variance

	for (auto i = 0; i < samples; i++) {
		pass2Variance += pow(storage[i] - pass2Mean, 2.0);
	}

	pass2Variance = pass2Variance / static_cast<double>(samples - 1);

	
	//////////////////////
	//
	// Calculate resulrs from Welford
	//

	auto wv = welfordVariance(&count, &mean, &M2);


	//////////////////////
	//
	// Results
	//

	std::cout << "Actual values:" << std::endl
		<< "   Mean = " << std::fixed << std::setprecision(5) << randMean << std::endl
		<< "   Std Dev = " << randStdDev << std::endl
		<< "   Number of Samples = " << samples << std::endl << std::endl

		<< "Two-pass estimation:" << std::endl
		<< "   Mean = " << std::fixed << std::setprecision(5) << pass2Mean
		<< ", Error = " << std::scientific << std::setprecision(3) << (pass2Mean - randMean) << std::endl
		<< "   Std Dev = " << std::fixed << std::setprecision(5) << sqrt(pass2Variance)
		<< ", Error = " << std::scientific << std::setprecision(3) << (sqrt(pass2Variance) - randStdDev)
		<< std::endl << std::endl

		<< "Welford estimation:" << std::endl
		<< "   Mean = " << std::fixed << std::setprecision(5) << mean
		<< ", Error = " << std::scientific << std::setprecision(3) << (mean - randMean) << std::endl
		<< "   Std Dev = " << std::fixed << std::setprecision(5) << sqrt(wv)
		<< ", Error = " << std::scientific << std::setprecision(3) << (sqrt(wv) - randStdDev)
		<< std::endl << std::endl;

	return 0;
}