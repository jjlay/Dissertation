#pragma once

//
// STL includes
//

#include <tuple>


//
// Function: regression()
//

std::tuple<double, double> regression(double* X, double* Y, int pLen);

