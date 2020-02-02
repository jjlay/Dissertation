
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

double *triple(double* pData, int pLen, int cycle, double pAlpha, double pBeta, double pGamma) {

	auto forecasts = new double[12];

	auto X = new double[pLen];
	auto Yhat = new double[pLen];

	for (auto x = 1; x <= pLen; x++)
		X[x-1] = static_cast<double>(x);

	// Regression for all points used for initial trend and level
	auto regResult = regression(X, pData, 12);

	double trend = std::get<_Slope_>(regResult);
	double level = std::get<_Intercept_>(regResult);

	std::cout << "Initial trend = " << trend << ", initial level = " << level << std::endl;


	// Regression for all points used in seasonals
	regResult = regression(X, pData, pLen);

	std::cout << "Slope = " << std::get<_Slope_>(regResult)
		<< ", Intercept = " << std::get<_Intercept_>(regResult) << std::endl;

	for (auto i = 0; i < pLen; i++)
		Yhat[i] = X[i] * std::get<_Slope_>(regResult) + std::get<_Intercept_>(regResult);



	return forecasts;
}

