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
// STL includes
//

#include <tuple>


//
// Local includes
//

#include "MonteCarlo.h"


//
// Standard includes
//

#include <iostream>
#include <iomanip>
#include <math.h>
#include <random>


//
// Function: MonteCarlo()
//
// Parameters:
//
// Returns:
//

std::tuple<double, double, double, double, double>
	MonteCarlo(
    	double pS0, double pv0, double pr0, double pT, double pK, 
    	double pKv, double pKr, double psigmav, double psigmar, 
    	double pvbar, double prbar, unsigned int psteps, 
		unsigned int psims, double pactual, double *prh0
    ) {

    // <Mean, Variance, Samples, WeakError, StrongError>
    std::tuple<double, double, double, double, double> result;

    std::get<_Tuple_Mean_>(result) = 0.0;
    std::get<_Tuple_Variance_>(result) = 0.0;
    std::get<_Tuple_Samples_>(result) = 0.0;
    std::get<_Tuple_WeakError_>(result) = 0.0;
    std::get<_Tuple_StrongError_>(result) = 0.0;
	
	//
	// Variables
	//

	double dt = pT / static_cast<double>(psteps);
	double sqrtdt = sqrt(dt);

	std::cout << "dt = " << dt << ", sqrtdt = " << sqrtdt << std::endl;
 
	double S = 0.0, v = 0.0, r = 0.0, dv = 0.0, dr = 0.0, dS = 0.0,
		sumS = 0.0, weakSumS = 0.0;
	
	auto dW = new double[3];

	// Random
	std::default_random_engine randGenerator;
	std::normal_distribution<double> randNorm(0.0, 1.0);
	

	//
	// Perform simulations
	//

	for (auto sim = 0; sim < psims; sim++) {
		S = pS0;
		v = pv0;
		r = pr0;

		for (auto step = 0; step < psteps; step++) {

			dS = 0.0;
			dr = 0.0;
			dv = 0.0;

			S += dS;
			v += dv;
			r += dr;

			S = (S < 0.0 ? 0.0 : S);
			r = (r < 0.0 ? 0.0 : r);
			v = (v < 0.0 ? 0.0 : v);
		}

		sumS += S;
		weakSumS += (S - pactual);
	}

	//
	// Results
	//

	sumS = sumS / static_cast<double>(psims);
	weakSumS = weakSumS / static_cast<double>(psims);


    std::get<_Tuple_Mean_>(result) = sumS;
    std::get<_Tuple_Variance_>(result) = 0.0;
    std::get<_Tuple_Samples_>(result) = 0.0;
    std::get<_Tuple_WeakError_>(result) = weakSumS;
    std::get<_Tuple_StrongError_>(result) = sumS - pactual;

    return result;
}

