
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
// STL include
//

#include <array>


//
// Function: multiply()
//
// Parameters:
//
//
// Returns:
//
//
// Comments:
//    This could be replaced by functions from BLAS.
//

std::array<double, 3> multiply(std::array<std::array<double, 3>, 3> pmatrix, std::array<double, 3> pvector) {

	std::array<double, 3> result;

	for (auto r = 0; r < 3; r++) {
		result[r] = 0.0;

		for (auto c = 0; c < 3; c++)
			result[r] += pmatrix[r][c] * pvector[c];
	}

	return result;
}

