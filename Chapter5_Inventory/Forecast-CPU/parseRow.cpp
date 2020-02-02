
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
 * 2018-05-05  JJL     Initial version of parsedRow
 *
 */

//
// Standard Includes
//

#include <string>


//
// STL Includes
//

#include <vector>


//
// Local Includes
//

#include "Trim.h"



//
// Function: parseRow()
//
// Parameters:
//
// Returns:
//

std::vector<std::string> parseRow(std::string pLine) {
	std::vector<std::string> parsedData;

	const char Quote = 34;
	const char Comma = 44;

	// cout << pLine << endl;

	int CurrentField = 0;
	int InQuotes = 0;

	std::string CurrentData;
	auto TempString = new char[pLine.length() + 2];

	for (auto i = 0; i < pLine.length() + 2; i++)
		TempString[i] = 0;

	// The following line uses the Windows safe version
#ifdef _WIN32
	strncpy_s(TempString, pLine.length() + 2, pLine.c_str(), pLine.length() + 2);
#endif

	// The following line is for Linux
#ifdef __linux__
//std::cout << "Linux strncpy" << std::endl;
	std::strncpy(TempString, pLine.c_str(), pLine.length() + 2);
#endif

	//std::cout << "TempString: " << TempString << std::endl;

	auto X = new char[3];
	X[0] = 0; X[1] = 0; X[2] = 0;

	for (auto CurrentChar = 0; CurrentChar < pLine.length(); CurrentChar++) {
		X[0] = TempString[CurrentChar];
		//std::cout << "Character: " << X[0] << std::endl;

		switch (X[0]) {
		case Quote:
			InQuotes = (InQuotes == 0 ? 1 : 0);
			//std::cout << "Quote " << InQuotes;
			break;

		case Comma:
			//std::cout << "Comma" << std::endl;
			if (!InQuotes) {
				// End of field
				trim(CurrentData);
				//std::cout << "Token: " << CurrentData << std::endl;
				parsedData.push_back(CurrentData);
				CurrentField++;
				CurrentData = "";
			}
			break;

		default:
			CurrentData.append(std::string(X));
			//std::cout << " Next" << std::endl;
		}
	}

	//std::cout << "Final token was " << CurrentData << std::endl;
	parsedData.push_back(CurrentData);

	return parsedData;
}