
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



void welford(double *pCount, double *pMean, double *pM2, double pNewValue) {
	(*pCount)++;
	double delta = pNewValue - *pMean;
	*pMean += delta / *pCount;
	double delta2 = pNewValue - *pMean;
	*pM2 += delta * delta2;
}

double welfordVariance(double* pCount, double* pMean, double* pM2) {
	return *pM2 / (*pCount - 1);
}

