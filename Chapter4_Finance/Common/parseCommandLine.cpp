
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
 * 2019-12-15  JJL     Created ability to pass parameters via
 *                     the command line
 *
 */


//
// STL includes
//

#include <map>
#include <tuple>


//
// Standard includes
//

#include <string>


//
// Definitions
//

#define _VALUE_  1
#define _KEY_    0


//
// Prototypes
//

std::tuple<std::string, std::string> splitParam(char* arg);


//
// Function: parseCommandLine()
//
// Parameters:
//
// Returns:
//

std::map<std::string, std::string> parseCommandLine(int argc, char* argv[]) {

    std::string key = "", value = "";

    std::map<std::string, std::string> result;

    value = argv[0];
    key = "PROGRAM";

    result[key] = value;

    for (auto i = 1; i < argc; i++) {
        auto x = splitParam(argv[i]);

        key = std::get<_KEY_>(x);
        value = std::get<_VALUE_>(x);
        result[key] = value;
    }

    return result;
}


//
// Function: splitParam()
//
// Parameters:
//
// Returns:
//
// Description:
//    Parses a string in the form of:
//       -param=value
//

std::tuple<std::string, std::string> splitParam(char* arg) {

    std::tuple<std::string, std::string> result;

    std::get<_KEY_>(result) = "";
    std::get <_VALUE_>(result) = "";

    std::string key = "", value = "", work = "";
    work = arg;
    int flag = -1;

    for (auto i = 0; i < work.length(); i++) {
        if ((flag == -1) && (work.substr(i, 1) == "-")) {
            // Beginning of key
            flag = _KEY_;
            i++;
        }

        if ((flag == _KEY_) && (work.substr(i, 1) == "=")) {
            // Beginning of value
            flag = _VALUE_;
            i++;
        }

        if (flag == _KEY_)
            key += work.substr(i, 1);

        if (flag == _VALUE_)
            value += work.substr(i, 1);
    }

    std::get<_KEY_>(result) = key;
    std::get <_VALUE_>(result) = value;

    return result;
}