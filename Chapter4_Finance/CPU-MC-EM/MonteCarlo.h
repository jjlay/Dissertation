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

#pragma once

//
// STL includes
//

#include <tuple>


//
// Definitions
//

#define _Tuple_Mean_          0
#define _Tuple_Variance_      1
#define _Tuple_Samples_       2
#define _Tuple_WeakError_     3
#define _Tuple_StrongError_   4


//
// Function: MonteCarlo()
//

std::tuple<double, double, double, double, double>
	MonteCarlo(
    	double pS0, double pv0, double pr0, double pT, double pK,
    	double pKv, double pKr, double psigmav, double psigmar,
    	double pvbar, double prbar, unsigned int psteps, 
		unsigned int psims, double pactual
);

