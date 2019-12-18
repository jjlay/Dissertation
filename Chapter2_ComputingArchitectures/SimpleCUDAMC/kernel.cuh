/*
 * Simple Monte Carlo
 * Single Threaded CPU Version
 *
 * JJ Lay
 * Middle Tennessee State University
 * October 2014
 *
 * DATE        AUTHOR  COMMENTS
 * ----------  ------  ---------------
 * 2014-10-07  JJL     Initial version
 *
 *
 */


#pragma once

 //
 // CUDA includes
 //

#include "cuda_runtime.h"
#include "device_launch_parameters.h"


//
// Function: kernel()
//
// Parameters:
//
// Returns:
//

__global__ void kernel(double r, double T, double sigma, double S0, double *mean, unsigned int *samples);

