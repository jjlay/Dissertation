//
// Weak vs Strong Error
//
// JJ Lay
// January 2018
//

// Sources:
// https://docs.nvidia.com/cuda/curand/device-api-overview.html

//
// CUDA Includes
//

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <curand.h>
#include <curand_kernel.h>

//
// Standard Includes
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

//
// Definitions
//

#define _OKAY_   0
#define _CRASH_  1


//
// Prototypes
//

__global__ void WeakStrong(double *pSum, double *pSum2, double *pSamples,
	double *pError, double *pVariance,
	double pS0, double pK, double pr, double pv, double pT, double pActual,
	unsigned int pSims, unsigned int pSteps, double pEpsilon,
	curandState *pStates);

void Crash(std::string pFile, int pLine, cudaError_t pCUDAError, std::string pMessage);

//
// Function: main()
//

int main(int argc, char *argv[])
{
	//
	// Monte Carlo Controls
	//

	unsigned int TotalSimsDesired = 1E8;

	double Epsilon = 1E-3;
	unsigned int Steps = 1000;
	int Threads = 100;
	unsigned int Samples = 1 + TotalSimsDesired / Threads;

	//
	// Finance Parameters
	//

	double K = 110.0;   // Strike price
	double S0 = 100.0;  // Initial asset price
	double r = 0.05;    // Interest rate
	double v = 0.5;     // Volatility
	double T = 1.0;     // Time to expiry						
	double Actual = S0 * exp(r * T);  // Per Mathematica's FinancialDerivative function

	//
	// Results
	//

	double Result = 0.0;
	double Error = 0.0;
	double ErrorPercent = 0.0;
	double Variance = 0.0;

	//
	// CUDA Storage
	//

	double *dev_Variance, *host_Variance,
		*dev_Sum, *host_Sum,
		*dev_Sum2, *host_Sum2,
		*dev_Samples, *host_Samples,
		*dev_Error, *host_Error;

	//
	// CUDA Setup
	//

	cudaError_t cudaStatus;

	// Choose which GPU to run on, change this on a multi-GPU system.
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "cudaSetDevice failed");
	}

	cudaStatus = cudaDeviceReset();
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "cudaDeviceReset failed");
	}


	//
	// CUDA Memory Allocation
	//

	cudaStatus = cudaMalloc((void**)&dev_Samples, Threads * sizeof(double));
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "dev_Samples cudaMalloc failed!");
	}

	cudaStatus = cudaMalloc((void**)&dev_Variance, Threads * sizeof(double));
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "dev_Variance cudaMalloc failed!");
	}

	cudaStatus = cudaMalloc((void**)&dev_Error, Threads * sizeof(double));
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "dev_Error cudaMalloc failed!");
	}

	cudaStatus = cudaMalloc((void**)&dev_Sum, Threads * sizeof(double));
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "dev_Sum cudaMalloc failed!");
	}

	cudaStatus = cudaMalloc((void**)&dev_Sum2, Threads * sizeof(double));
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "dev_Sum2 cudaMalloc failed!");
	}

	//
	// Local Memory Allocation
	//

	host_Sum = (double *)malloc(Threads * sizeof(double));
	host_Sum2 = (double *)malloc(Threads * sizeof(double));
	host_Error = (double *)malloc(Threads * sizeof(double));
	host_Variance = (double *)malloc(Threads * sizeof(double));
	host_Samples = (double *)malloc(Threads * sizeof(double));

	//
	// Random Number Generator
	//

	curandState *dev_States;
	cudaStatus = cudaMalloc((void**)&dev_States, Threads * sizeof(curandState));
	if (cudaStatus != cudaSuccess) {
		Crash(__FILE__, __LINE__, cudaStatus, "dev_States cudaMalloc failed!");
	}

	//
	// Log File Initialization
	//

	std::ofstream LogFile("Results.csv", std::ios::app);

	//
	// Run the simulation with smaller and smaller step sizes
	//

	for (auto NumSteps = 1; NumSteps < 1000; NumSteps++) {
		//
		// Kernel Launch
		//

		WeakStrong << <1, Threads >> > (dev_Sum, dev_Sum2, dev_Samples, dev_Error, dev_Variance,
			S0, K, r, v, T, Actual, Samples, NumSteps, Epsilon, dev_States);


		// Check for any errors launching the kernel
		cudaStatus = cudaGetLastError();
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "Kernel launch failed!");
		}

		// cudaDeviceSynchronize waits for the kernel to finish, and returns
		// any errors encountered during the launch.
		cudaStatus = cudaDeviceSynchronize();
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "cudaDeviceSynchronize failed!");
		}


		//
		// Retrieve Results
		//

		// Copy output vector from GPU buffer to host memory.
		cudaStatus = cudaMemcpy(host_Error, dev_Error, Threads * sizeof(double), cudaMemcpyDeviceToHost);
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "dev_Error Memcpy failed!");
		}

		cudaStatus = cudaMemcpy(host_Variance, dev_Variance, Threads * sizeof(double), cudaMemcpyDeviceToHost);
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "dev_Variance Memcpy failed!");
		}

		cudaStatus = cudaMemcpy(host_Sum, dev_Sum, Threads * sizeof(double), cudaMemcpyDeviceToHost);
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "dev_Sum Memcpy failed!");
		}

		cudaStatus = cudaMemcpy(host_Sum2, dev_Sum2, Threads * sizeof(double), cudaMemcpyDeviceToHost);
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "dev_Sum2 Memcpy failed!");
		}

		cudaStatus = cudaMemcpy(host_Samples, dev_Samples, Threads * sizeof(double), cudaMemcpyDeviceToHost);
		if (cudaStatus != cudaSuccess) {
			Crash(__FILE__, __LINE__, cudaStatus, "dev_Samples Memcpy failed!");
		}


		//
		// Export Results
		//


		double FinalSum = 0.0;
		double FinalSamples = 0.0;
		double FinalSum2 = 0.0;
		double FinalSumError = 0.0;
		double FinalStdDev = 0.0;

		for (auto i = 0; i < Threads; i++) {
			FinalSum += host_Sum[i];
			FinalSamples += host_Samples[i];
			FinalSum2 += host_Sum2[i];
			FinalSumError += host_Error[i];
			FinalStdDev += host_Variance[i];
		}

		double FinalMean = FinalSum / FinalSamples;
		double FinalError = FinalMean - Actual;
		double FinalVariance = (FinalSum2 / FinalSamples) - (FinalMean * FinalMean);
		double FinalSumErrorMean = FinalSumError / FinalSamples;
		FinalStdDev = sqrt(FinalStdDev / FinalSamples);

		double dt = T / static_cast<double>(NumSteps);


		std::cout << "Analytical: " << Actual << ", "
			<< "Final Mean: " << FinalMean << ", "
			<< "Final Weak Error: " << std::fixed << std::setprecision(6) << FinalError << ", "
			<< "Final Strong Error: " << FinalSumErrorMean << ", "
			<< "dt: " << dt << ", "
			<< "StdDev: " << FinalStdDev << std::endl;

		LogFile << "Analytical: " << Actual << ", "
			<< "Final Mean: " << FinalMean << ", "
			<< "Final Weak Error: " << std::fixed << std::setprecision(6) << FinalError << ", "
			<< "Final Strong Error: " << FinalSumErrorMean << ", "
			<< "dt: " << dt << ", "
			<< "StdDev: " << FinalStdDev << std::endl;

		LogFile.flush();
	}

	LogFile.close();

	//
	// Memory Cleanup
	//

	free(host_Sum);
	free(host_Sum2);
	free(host_Error);
	free(host_Variance);
	free(host_Samples);

	cudaFree(dev_Sum);
	cudaFree(dev_Sum2);
	cudaFree(dev_Error);
	cudaFree(dev_Variance);
	cudaFree(dev_Samples);


	//
	// Wrap Up
	//

	return _OKAY_;
}


//
// Kernel: WeakStrong
//

__global__ void WeakStrong(double *pSum, double *pSum2, double *pSamples, 
	double *pError, double *pVariance,
	double pS0, double pK, double pr, double pv, double pT, double pActual,
	unsigned int pSims, unsigned int pSteps, double pEpsilon,
	curandState *pStates)
{
	int idx = threadIdx.x;

	curand_init(31415, idx, 0, &pStates[idx]);

	double dt = pT / static_cast<double>(pSteps);
	double Sqrtdt = sqrt(dt);

	//
	// Aggregate Variables
	//

	double Sum = 0.0;
	double Sum2 = 0.0;
	double SumError = 0.0;
	double Variance = 0.0;

	//
	// Perform Simulation
	//

	// We use Welford's Algorithm to estimate variance

	// variance(samples) :
	// 	M: = 0
	// 	S : = 0
	// 	for k from 1 to N :	
	// 		x: = samples[k]
	// 		oldM : = M
	// 		M : = M + (x - M) / k
	// 		S : = S + (x - M)*(x - oldM)
	// return S / (N - 1)

	double WM = 0.0, WS = 0.0, WX = 0.0, WMOld = 0.0;  

	for (unsigned int i = 0; i < pSims; i++) {
		double Result = 0.0;
		double S = pS0;

		for (unsigned int s = 0; s < pSteps; s++) {
			double dW = Sqrtdt * curand_normal(&pStates[idx]);
			double dS = (pr * S * dt) + (pv * S * dW);
			S += dS;
		}

		WX = S;
		WMOld = WM;
		WM = WM + (WX - WM) / static_cast<double>(i + 1);
		WS = WS + (WX - WM) * (WX - WMOld);

		Sum += S;
		Sum2 += S * S;
		SumError += abs(S - pActual);
	}	

	pSum[idx] = Sum;
	pSum2[idx] = Sum2;
	pVariance[idx] = WS / static_cast<double>(pSims - 1);
	pError[idx] = SumError;
	pSamples[idx] = static_cast<double>(pSims);
}



void Crash(std::string pFile, int pLine, cudaError_t pCUDAError, std::string pMessage) {

	std::cerr << "Crash in file " << pFile << std::endl
		<< "Line: " << pLine << std::endl;

	if (pCUDAError != NULL) {
		std::cerr << "CUDA Error: " << pCUDAError << " :: " << cudaGetErrorString(pCUDAError) << std::endl;
	}

	exit(_CRASH_);
}
