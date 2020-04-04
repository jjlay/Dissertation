#include <iostream>
#include <iomanip>
#include <random>

int main(int argc, char *argv[]) {

	std::default_random_engine  gen;
	std::normal_distribution<double> dist(0.0, 1.0);


	for (unsigned int steps = 2; steps < 10000; steps = steps * 2) {
		const int metasamples = 1000;

		const unsigned int samples = 1000;
		const double T = 1.0;
		const double X0 = 100.0;
		const double r = 0.05;
		const double volatility = 0.03;
		
		double dt = T / static_cast<double>(steps);
		double sqrtdt = sqrt(dt);

		auto dataEM = new double[samples];
		auto metameanEM = new double[metasamples];
		auto metastdevEM = new double[metasamples];

		auto dataMilstein = new double[samples];
		auto metameanMilstein = new double[metasamples];
		auto metastdevMilstein = new double[metasamples];

		double XEM = 0.0, XMilstein = 0.0, dx = 0.0, dW = 0.0;

		for (auto m = 0; m < metasamples; m++) {
			//
			// Perform simulation
			//
		
			for (auto i = 0; i < samples; i++) {
				XEM = X0;
				XMilstein = X0;

				for (auto j = 0; j < steps; j++) {
					// Use the same random values for both the Milstein and Euler-Maruyama
					dW = dist(gen) * sqrtdt;

					// Euler-Maruyama
					dx = (r * XEM * dt) + (volatility * XEM * dW);
					XEM += dx;

					// Milstein
					dx = (r * XMilstein * dt) + (volatility * XMilstein * dW) + (0.5 * (volatility * XMilstein) * (volatility) * (dW * dW - dt));
					XMilstein += dx;
				}
	
				dataEM[i] = XEM;
				dataMilstein[i] = XMilstein;
			}

			//
			// Calculate statistics
			//
	
			double meanEM = 0.0, meanMilstein = 0.0;
	
			for (auto i = 0; i < samples; i++) {
				meanEM += dataEM[i];
				meanMilstein += dataMilstein[i];
			}
	
			meanEM = meanEM / static_cast<double>(samples);
			meanMilstein = meanMilstein / static_cast<double>(samples);

			double stdevEM = 0.0, stdevMilstein = 0.0;

			for (auto i = 0; i < samples; i++) {
				stdevEM += pow(dataEM[i] - meanEM, 2.0);
				stdevMilstein += pow(dataMilstein[i] - meanMilstein, 2.0);
			}

			stdevEM = sqrt(stdevEM / static_cast<double>(samples));
			stdevMilstein = sqrt(stdevMilstein / static_cast<double>(samples));

			metameanEM[m] = meanEM;
			metastdevEM[m] = stdevEM;
			metameanMilstein[m] = meanMilstein;
			metastdevMilstein[m] = stdevMilstein;
		}

		double meanmean = 0.0, meanstdev = 0.0, stdevmean = 0.0, stdevstdev = 0.0;

		//
		// Euler-Maruyama
		//
		
		for (auto i = 0; i < metasamples; i++) {
			meanmean += metameanEM[i];
			stdevmean += metastdevEM[i];
		}

		meanmean = meanmean / static_cast<double>(metasamples);
		stdevmean = stdevmean / static_cast<double>(metasamples);

		for (auto i = 0; i < metasamples; i++) {
			meanstdev += pow(metameanEM[i] - meanmean, 2.0);
			stdevstdev += pow(metastdevEM[i] - stdevmean, 2.0);
		}

		meanstdev = sqrt(meanstdev / static_cast<double>(metasamples));
		stdevstdev = sqrt(stdevstdev / static_cast<double>(metasamples));

		std::cout << "Euler-Maruyama : dt : " << dt << " : "
			<< "MEAN : mean: " << meanmean << " : stdev: " << meanstdev << " : "
			<< "STD DEV : mean: " << stdevmean << " : stdev: " << stdevstdev << std::endl;
		
		//
		// Milstein
		//

		meanmean = 0.0;
		meanstdev = 0.0;
		stdevmean = 0.0;
		stdevstdev = 0.0;

		for (auto i = 0; i < metasamples; i++) {
			meanmean += metameanMilstein[i];
			stdevmean += metastdevMilstein[i];
		}

		meanmean = meanmean / static_cast<double>(metasamples);
		stdevmean = stdevmean / static_cast<double>(metasamples);

		for (auto i = 0; i < metasamples; i++) {
			meanstdev += pow(metameanMilstein[i] - meanmean, 2.0);
			stdevstdev += pow(metastdevMilstein[i] - stdevmean, 2.0);
		}

		meanstdev = sqrt(meanstdev / static_cast<double>(metasamples));
		stdevstdev = sqrt(stdevstdev / static_cast<double>(metasamples));

		std::cout << "Milstein : dt : " << dt << " : "
			<< "MEAN : mean: " << meanmean << " : stdev: " << meanstdev << " : "
			<< "STD DEV : mean: " << stdevmean << " : stdev: " << stdevstdev << std::endl;
	}
		
	return 0;
}


