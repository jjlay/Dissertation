
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
// STL Includes
//

#include <array>


//
// Function: createMatrix()
//
// Parameters:
//
// Returns:
//

std::array<std::array<double, 3>, 3> createMatrix(double pRho12, double pRho13, double pRho23) {

	std::array<std::array<double, 3>, 3> correlationMatrix;

	for (auto i = 0; i < 3; i++)
		correlationMatrix[i][i] = 1.0;

	correlationMatrix[0][1] = pRho12;
	correlationMatrix[1][0] = pRho12;
	correlationMatrix[0][2] = pRho13;
	correlationMatrix[2][0] = pRho13;
	correlationMatrix[1][2] = pRho23;
	correlationMatrix[2][1] = pRho23;

	return correlationMatrix;
}

