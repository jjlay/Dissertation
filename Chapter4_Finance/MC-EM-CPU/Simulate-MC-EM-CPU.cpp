
/*
 * Single threaded CPU Based Monte Carlo Simulation of European Put
 * Euler-Muryama Method
 *
 * Implementation of
 * Alexey Medvedev, Olivier Scaillet "Pricing American options under
 * stochastic volatility and stochastic interest rates"
 * Journal of Financial Economics. 2010.
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
 * 2014-10-07  JJL     Initial version
 *
 * 2014-10-20  JJL     Stochastic volatility and
 *                     stochastic interest rate
 *
 * 2014-10-28  JJL     Added Multilevel Monte Carlo
 *
 */


 //
 // Local includes
 //

#include "../Common/Results.h"
#include "../Common/multiplyMatrixVector.h"
#include "../Common/Welford.h"


//
// STL includes
//

#include <array>


//
// Standard Includes
//

#include <random>
#include <iostream>


//
// Function: simulateMCEMCPU()
//
// Parameters:
//
// Returns:
//

std::array<double, _RESULT_WIDTH_> simulateMCEMCPU(double pS0, double pr0, double pv0, double pK, double pT, 
	double pv, double pKv, double psigmav, double ptheta, double prbar, double pKr,
	double psigmar, double pclosedForm, 
	std::array<std::array<double, 3>, 3> pcorrelationMatrix) {

	std::array<double, _RESULT_WIDTH_> results;

	results[_RESULT_MEAN_] = 0.0;
	results[_RESULT_VAR_] = 0.0;
	results[_RESULT_N_] = 0.0;
	results[_ERROR_WEAK_] = 0.0;
	results[_ERROR_STRONG_] = 0.0;

	const unsigned int numberSteps = 500;
	const unsigned int numberSims = static_cast<unsigned int>(1E4);

	auto dt = pT / static_cast<double>(numberSteps);
	auto sqrtdt = sqrt(dt);
	double S = 0.0, v = 0.0, r = 0.0, dS = 0.0, dr = 0.0, dv = 0.0;

	std::array<double, 3> normRand;

	std::default_random_engine generator;
	std::normal_distribution<double> normal(0, 1);

	// Welford variables

	double welMean = 0.0, welCount = 0.0, welM2 = 0.0;

	for (auto sim = 0; sim < numberSims; sim++) {
		S = pS0; 
		v = pv0; 
		r = pr0;

		for (auto step = 0; step < numberSteps; step++) {
			normRand[0] = normal(generator);
			normRand[1] = normal(generator);
			normRand[2] = normal(generator);

			auto dW = multiply(pcorrelationMatrix, normRand);

			dW[0] = dW[0] * sqrtdt;
			dW[1] = dW[1] * sqrtdt;
			dW[2] = dW[2] * sqrtdt;

			dS = r * S * dt + sqrt(v) * S * dW[0];
			dv = pKv * (ptheta - v) * dt + psigmav * sqrt(v) * dW[1];
			dr = pKr * (prbar - r) * dt + psigmar * sqrt(r) * dW[2];

			S += dS;
			v += dv;
			r += dr;

			S = (S < 0.0 ? 0.0 : S);
			v = (v < 0.0 ? 0.0 : v);
			r = (r < 0.0 ? 0.0 : r);
		}

		double price = exp(-r * pT) * ((pK - S) < 0 ? 0.0 : (pK - S));
		results[_RESULT_MEAN_] += price;
		results[_ERROR_WEAK_] += abs(price - pclosedForm);

		welford(&welCount, &welMean, &welM2, price);
	}

	results[_RESULT_N_] = static_cast<double>(numberSims);
	results[_RESULT_STEPS_] = static_cast<double>(numberSteps);
	results[_RESULT_MEAN_] = results[_RESULT_MEAN_] / results[_RESULT_N_];
	results[_RESULT_VAR_] = welfordVariance(&welCount, &welMean, &welM2);

	// Error estimation

	results[_ERROR_STRONG_] = abs(results[_RESULT_MEAN_] - pclosedForm);
	results[_ERROR_WEAK_] = results[_ERROR_WEAK_] / results[_RESULT_N_];

	return results;
}




