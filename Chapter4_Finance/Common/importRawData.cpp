
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
// Local Includes
//

#include "../Common/Crash.h"
#include "../Common/Trim.h"


//
// Standard Includes
//

#include <string>
#include <fstream>
#include <iostream>


//
// STL Includes
//

#include <vector>


//
// Function: importRawData()
//
// Parameters:
//
// Returns:
//

std::vector<std::string> importRawData(std::string pFilename) {

	std::ifstream inFile(pFilename, std::ios::in);

	if (!inFile.is_open()) {
		crash(__LINE__, __FILE__, __FUNCTION__, "Unable to open " + pFilename);
	}

	std::vector<std::string> rawData;

	std::string line;

	while (std::getline(inFile, line)) {
		trim(line);

		if (line.size() > 0)
			rawData.push_back(line);
	}

	std::cout << "Imported " << rawData.size() << " rows from the file" << std::endl;

	return rawData;
}


