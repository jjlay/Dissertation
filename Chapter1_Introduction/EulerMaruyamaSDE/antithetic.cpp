#include <iostream>
#include <iomanip>
#include <random>

int main(int argc, char* argv[]) {

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

		double XEM = 0.0, XEM1 = 0.0, XEM2 = 0.0, XMilstein = 0.0, XMilstein1 = 0.0, XMilstein2 = 0.0, dx = 0.0, dW1 = 0.0, dW2 = 0.0;

		for (auto m = 0; m < metasamples; m++) {
			//
			// Perform simulation
			//

			for (auto i = 0; i < samples; i++) {
				XEM = X0;
				XMilstein = X0;

				for (auto j = 0; j < steps; j += 2) {
					// Use the same random values for both the Milstein and Euler-Maruyama
					dW1 = dist(gen) * sqrtdt;
					dW2 = dist(gen) * sqrtdt;
					
					// antithetic Euler-Maruyama
					dx = (r * XEM * dt) + (volatility * XEM * dW1);
					XEM1 = XEM + dx;
					dx = (r * XEM1 * dt) + (volatility * XEM1 * dW2);
					XEM1 = XEM1 + dx;

					dx = (r * XEM * dt) + (volatility * XEM * dW2);
					XEM2 = XEM + dx;
					dx = (r * XEM2 * dt) + (volatility * XEM2 * dW1);
					XEM2 = XEM2 + dx;

					XEM = (XEM1 + XEM2) / 2.0;


					// antithetic Milstein
					dx = (r * XMilstein * dt) + (volatility * XMilstein * dW1) + (0.5 * (volatility * XMilstein) * (volatility) * (dW1 * dW1 - dt));
					XMilstein1 = XMilstein + dx;
					dx = (r * XMilstein1 * dt) + (volatility * XMilstein1 * dW2) + (0.5 * (volatility * XMilstein1) * (volatility) * (dW2 * dW2 - dt));
					XMilstein1 = XMilstein1 + dx;

					dx = (r * XMilstein * dt) + (volatility * XMilstein * dW2) + (0.5 * (volatility * XMilstein) * (volatility) * (dW2 * dW2 - dt));
					XMilstein2 = XMilstein + dx;
					dx = (r * XMilstein2 * dt) + (volatility * XMilstein2 * dW1) + (0.5 * (volatility * XMilstein2) * (volatility) * (dW1 * dW1 - dt));
					XMilstein2 = XMilstein2 + dx;

					XMilstein = (XMilstein1 + XMilstein2) / 2.0;
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

		std::cout << "antithetic : Euler-Maruyama : dt : " << dt << " : "
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

		std::cout << "antithetic : Milstein : dt : " << dt << " : "
			<< "MEAN : mean: " << meanmean << " : stdev: " << meanstdev << " : "
			<< "STD DEV : mean: " << stdevmean << " : stdev: " << stdevstdev << std::endl;
	}

	return 0;
}


