
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
#include <string>


//
// Local includes
//

#include "../Common/Parameters.h"
#include "../Common/ReturnValues.h"
#include "../Common/importRawData.h"
#include "../Common/parseRow.h"
#include "../Common/Crash.h"


//
// Function: importParameters()
//
// Paremeters:
//
// Returns:
//

std::vector<std::vector<double>> importParameters() {

	std::string filename = "../Common/parameters.csv";

	auto rawData = importRawData(filename);

	// Remove the header row
	rawData.erase(rawData.begin());

	std::vector<std::vector<double>> parameters;

	for (auto v : rawData) {
		auto parsedData = parseRow(v);

		std::vector<double> temp;

		for (auto w : parsedData) {

			// Is it a fraction?
			auto loc = w.find("/");

			if (loc == std::string::npos) {
				// Not a fraction
				double x = stod(w);
				temp.push_back(x);
			}
			else {
				// Must be a fraction
				auto numerator = w.substr(0, w.find("/") - 1);
				auto denominator = w.substr(w.find("/") + 1);
				double x = stod(numerator) / stod(denominator);
				temp.push_back(x);
			}
		}

		if (temp.size() == _Number_Of_Parameters_)
			parameters.push_back(temp);
		else
			crash(__LINE__, __FILE__, __FUNCTION__, "Incorrect number of parameters: " + v);
	}

	std::cout << "There were " << parameters.size() << " parameter sets" << std::endl;

	return parameters;
}

