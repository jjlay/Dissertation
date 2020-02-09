
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

#include "parseCommandLine.h"
#include "ReturnValues.h"
#include "MonteCarlo.h"


//
// Standard includes
//

#include <iostream>


//
// Function: main()
//
// Parameters:
//    argc - Number of commandline arguments
//    argv - Array of commandline arguments
//
// Returns:
//    Completion status (see ReturnValues.h)
//

int main(int argc, char* argv[]) {

    // 
    // Simulation Parameters
    //

    double S0 = 0.0, v0 = 0.0, r0 = 0.0, T = 0.0, K = 0.0, 
        Kv = 0.0, Kr = 0.0, sigmav = 0.0, sigmar = 0.0,
        vbar = 0.0, rbar = 0.0, actual = 0.0;
    unsigned int steps = 0, sims = 0;

    //
    // Process commandline parameters
    //

    auto parameters = parseCommandLine(argc, argv);

    for (auto p : parameters) {
        auto key = p.first;
        auto value = p.second;

        std::cout << "Key: " << key << " :: " << "Value: " << value << std::endl;

        // Initial asset price
        if (key == "S0")
            S0 = std::stod(value);

        // Strike price
        if (key == "K")
            K = std::stod(value);

        // Mean reversion of volatility
        if (key == "Kv")
            Kv = std::stod(value);

        // Mean reversion of interest rate
        if (key == "Kr")
            Kr = std::stod(value);

        if (key == "rbar")
            rbar = std::stod(value);

        if (key == "vbar")
            vbar = std::stod(value);

        // Initial interest rate
        if (key == "r0")
            r0 = std::stod(value);

        // Initial volatility
        if (key == "v0")
            v0 = std::stod(value);

        // Volatility of volatility
        if (key == "sigmav")
            sigmav = std::stod(value);

        // Volatility of interest rate
        if (key == "sigmar")
            sigmar = std::stod(value);

        // Time to expiry
        if (key == "T")
            T = std::stod(value);

        // Number of Monte Carlo steps
        if (key == "steps")
            steps = std::stoi(value);

        // Number of simulations
        if (key == "sims")
            sims = std::stoi(value);

        // Number of simulations
        if (key == "actual")
            actual = std::stod(value);
    }


    std::cout << std::endl << "======================" << std::endl
        << "Simulation Parameters" << std::endl
        << "======================" << std::endl
        << "S0 = " << S0 << std::endl
        << "r0 = " << r0 << std::endl
        << "v0 = " << v0 << std::endl
        << "T = " << T << std::endl << std::endl
        << "sims = " << sims << std::endl
        << "steps = " << steps << std::endl << std::endl
        << "Closed form solution = " << actual << std::endl;


    //
    // Perform simulation
    //

    auto monteCarloResult = MonteCarlo(S0, v0, r0, T, K, Kv, Kr, sigmav, sigmar, vbar, rbar, steps, sims, actual);

    std::cout << std::endl << "======================" << std::endl
        << "Simulation Results" << std::endl
        << "======================" << std::endl
        << "Mean = " << std::get<_Tuple_Mean_>(monteCarloResult) << std::endl
        << "Variance = " << std::get<_Tuple_Variance_>(monteCarloResult) << std::endl
        << "Samples = " << std::get<_Tuple_Samples_>(monteCarloResult) << std::endl << std::endl;

    if (actual != 0.0) {
        std::cout << "Error of the mean = " << std::get<_Tuple_Samples_>(monteCarloResult) - actual << std::endl
            << "Mean of the error = " << std::get<_Tuple_MeanError_>(monteCarloResult) << std::endl;
    }


    //
    // Wrap up
    //

    return _OKAY_;
}

