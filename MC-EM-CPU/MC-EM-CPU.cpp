
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


//
// Local includes
//

#include "../Common/Parameters.h"
#include "../Common/ReturnValues.h"
#include "../Common/importParameters.h"
#include "../Common/Crash.h"
#include "../Common/createMatrix.h"

#include "Simulate-MC-EM-CPU.h"


//
// Function: main()
// 
// Parameters:
//    argc - 
//    argv -
//
// Returns:
//    Execution status (int)
//

int main(int argc, char *argv[])
{
	auto SimulationStart = std::chrono::system_clock::now();

	//
	// Parameters
	//

	auto parameters = importParameters();

	if (parameters.size() == 0)
		crash(__LINE__, __FILE__, __FUNCTION__, "No parameters to process");

	auto ImportedParameters = std::chrono::system_clock::now();

	//
	// Perform simulations
	//

	for (auto p = 0; p < parameters.size(); p++) {
		std::cout << "=== Parameter Set " << p << " ===" << std::endl;

		auto set = parameters[p];

		auto K = set[_K_];
		auto T = set[_T_];
		auto v = set[_v_];
		auto Kv = set[_Kv_];
		auto sigmav = set[_sigmav_];
		auto rho12 = set[_rho12_];
		auto closedForm = set[_ClosedForm_];
		double theta = 0.02;
		double rbar = 0.04;
		double Kr = 0.3;
		double sigmar = 0.1;
		double S0 = 100.0;
		double r0 = 0.04;
		double v0 = v;

		std::cout << "    K = " << std::fixed << std::setprecision(2) << K << std::endl
			<< "    S0 = " << std::fixed << std::setprecision(2) << S0 << std::endl
			<< "    r0 = " << std::fixed << std::setprecision(2) << r0 << std::endl
			<< "    v0 = " << std::fixed << std::setprecision(2) << v0 << std::endl
			<< "    T = " << std::fixed << std::setprecision(4) << T << std::endl
			<< "    v = " << std::fixed << std::setprecision(2) << v << std::endl
			<< "    theta = " << std::fixed << std::setprecision(2) << theta << std::endl
			<< "    Kv = " << std::fixed << std::setprecision(2) << Kv << std::endl
			<< "    Kr = " << std::fixed << std::setprecision(2) << Kr << std::endl
			<< "    rbar = " << std::fixed << std::setprecision(2) << rbar << std::endl
			<< "    sigmav = " << std::fixed << std::setprecision(2) << sigmav << std::endl
			<< "    sigmar = " << std::fixed << std::setprecision(2) << sigmar << std::endl
			<< "    rho12 = " << std::fixed << std::setprecision(4) << rho12 << std::endl
			<< "    closedForm = " << std::fixed << std::setprecision(4) << closedForm << std::endl << std::endl;

		auto correlationMatrix = createMatrix(rho12, 0.0, 0.0);

		std::cout << "Correlation Matrix:" << std::endl;

		for (auto r = 0; r < 3; r++) {
			std::cout << " : ";

			for (auto c = 0; c < 3; c++)
				std::cout << std::setw(7) << std::fixed << std::setprecision(2) << correlationMatrix[r][c] << " : ";

			std::cout << std::endl;
		}

		std::cout << std::endl;

		auto SimStart = std::chrono::system_clock::now();
		auto results = simulateMCEMCPU(S0, r0, v0, K, T, v, Kv, sigmav, theta,
			rbar, Kr, sigmar, closedForm, correlationMatrix);
		auto SimEnd = std::chrono::system_clock::now();

		std::cout << "Results:" << std::endl
			<< "   Mean: " << std::fixed << std::setprecision(4) << results[_RESULT_MEAN_] << std::endl
			<< "   Variance: " << std::fixed << std::setprecision(4) << results[_RESULT_VAR_] << std::endl
			<< "   N: " << std::fixed << std::setprecision(0) << results[_RESULT_N_] << std::endl
			<< "   Steps: " << std::fixed << std::setprecision(0) << results[_RESULT_STEPS_] << std::endl;
		
		std::chrono::duration<double> runtime = SimEnd - SimStart;
		
		std::cout << "   Runtime: " << runtime.count() << " seconds" << std::endl << std::endl;

		std::cout << "Error:" << std::endl
			<< "   Strong error: " << std::scientific << std::setprecision(2) << results[_ERROR_STRONG_] 
			<< " (" << std::fixed << 100.0 * results[_ERROR_STRONG_] / closedForm << "%)" << std::endl 
			<< "   Weak error: " << std::scientific << std::setprecision(2) << results[_ERROR_WEAK_] 
			<< " (" << std::fixed << 100.0 * results[_ERROR_WEAK_] / closedForm << "%)" << std::endl
			<< std::endl;

		std::cout << "=== Finished " << p << " ===" << std::endl << std::endl;
	}


	//
	// Wrap up
	//

	auto Finished = std::chrono::system_clock::now();

	return _OKAY_;
}


