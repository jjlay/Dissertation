//
// Simple Monte-Carlo Example
//
// JJ Lay
// 

//
// Standard Includes
//

#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>


//
// Return Values
//

#define _OKAY_  0


//
// Function: main()
//

int main(int argc, char *argv[]) {

	//
	// Setup random number generator
	//

	std::default_random_engine generator;
	std::normal_distribution<double> normal(0.0, 1.0);


	//
	// Black-Scholes parameters
	//
	
	double S0 = 100.0;  // Initial asset price
	double v = 0.1;     // Volatility
	double r = 0.4;     // Interest rate
	double T = 1.0;     // Time to expiry

	//
	// Simulation parameters
	//

	int steps = 200;
	int iterations = 1E4;

	double dt = T / static_cast<double>(steps);
	double sqrtdt = sqrt(dt);

	//
	// Perform the simulation
	//
	
	double sum = 0.0;

	for (auto i = 0; i < iterations; i++) {
		double S = S0;

		for (auto s = 0; s < steps; s++) {
			auto dW = sqrtdt * normal(generator);

			auto dS = S * r * dt + v * S * dW;
			S += dS;
		}

		sum += S;
	}

	auto mean = sum / static_cast<double>(iterations);
	auto analytical = S0 * exp(r * T);

	auto AbsErr = fabs(mean - analytical);
	auto mape = 100.00 * fabs(mean - analytical) / analytical;

	std::cout << "Steps = " << std::fixed << steps << ", "
		<< "Iterations = " << iterations << ", "
		 << "S = " << std::fixed << std::setprecision(2) 
			<< mean << ", "
		<< "Analytical = " << std::fixed << std::setprecision(2) 
			<< analytical << ", "
		<< "Abs Error = " << std::scientific << std::setprecision(3) 
			<< AbsErr << ", "
		<< "MAPE = " << std::fixed << std::setprecision(2) 
			<< mape << "%" << std::endl;



	return _OKAY_;
}

