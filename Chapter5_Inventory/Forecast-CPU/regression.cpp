
//
// STL includes
//

#include <tuple>


//
// Local includes
//

#include "common.h"


//
// Function: regression()
//

std::tuple<double, double> regression(double* X, double* Y, int pLen) {

	std::tuple<double, double> result;

	std::get<_Slope_>(result) = 0.0;
	std::get<_Intercept_>(result) = 0.0;


	double SumX = 0.0, SumY = 0.0, SumX2 = 0.0, SumXY = 0.0, SumY2 = 0.0;

	for (auto c = 0; c < pLen; c++) {
		SumX += X[c];
		SumY += Y[c];
		SumX2 += X[c] * X[c];
		SumY2 += Y[c] * Y[c];
		SumXY += X[c] * Y[c];
	}

	// Calculate the intercept
	double N = static_cast<double>(pLen);

	double Intercept = ((SumY * SumX2) - (SumX * SumXY)) /
		((N * SumX2) - (SumX * SumX));

	// And the slope
	double Slope = ((N * SumXY) - (SumX * SumY)) /
		((N * SumX2) - (SumX * SumX));


	std::get<_Slope_>(result) = Slope;
	std::get<_Intercept_>(result) = Intercept;


	return result;
}

