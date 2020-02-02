
//
// STL includes
//

#include <tuple>


//
// Standard includes
//

#include <iostream>


//
// Local includes
//

#include "regression.h"
#include "common.h"


//
// Function: triple()
//

double *triple(double* pData, int pLen, double pAlpha, double pBeta, double pGamma) {

	auto forecasts = new double[12];

	auto X = new double[pLen];

	for (auto x = 1; x <= pLen; x++)
		X[x-1] = static_cast<double>(x);

	auto regResult = regression(X, pData, pLen);

	std::cout << "Slope = " << std::get<_Slope_>(regResult)
		<< ", Intercept = " << std::get<_Intercept_>(regResult) << std::endl;


	return forecasts;
}

