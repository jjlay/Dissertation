
//
// Standard includes
//

#include <iostream>
#include <iomanip>
#include <string>


//
// Local includes
//

#include "ReturnValues.h"
#include "importPINS.h"
#include "forecast.h"


//
// Function: main()
//

int main(int argc, char* argv[]) {
	std::string file = "bcp.csv";

	auto pins = importPINS(file);

	std::cout << "There were " << pins.size() << " rows" << std::endl;

	double alpha = 0.1, beta = 0.1, gamma = 0.1;

	auto data = new double[24];

	for (auto i = 0; i < 24; i++) {
		auto s = pins[i][1];
		data[i] = std::stod(s);
	}

	auto forecasts = triple(data, 24, alpha, beta, gamma);

	return _OKAY_;
}

