
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
 // Standard Includes
 //

#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>

//
// STL Includes
//

#include <vector>


//
// Local includes
//

#include "../Common/Parameters.h"
#include "../Common/ReturnValues.h"
#include "../Common/importParameters.h"


//
// Function: main()
// 
// Parameters:
//    argc - 
//    argv -
//
// Returns:
//    Execution status (int)
//

int main(int argc, char *argv[])
{
	auto SimulationStart = std::chrono::system_clock::now();

	//
	// Parameters
	//

	auto parameters = importParameters();

	return _OKAY_;
}


