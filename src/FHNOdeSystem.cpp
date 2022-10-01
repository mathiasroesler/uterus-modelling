#include "FHNOdeSystem.hpp"
#include "Exception.hpp"

FHNOdeSystem::FHNOdeSystem() : AbstractOdeSystem(2)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();

	// Initialise parameters
	mA = 1.0;
	mB = 2.0;
	mC = 2.0;
	mFreq = 16e-3;
	mDelta = 0.8;
	mEpsilon = 0.115;
	mGamma = 0.1;
}

void FHNOdeSystem::EvaluateYDerivatives(double time, 
	const std::vector<double>& rY, std::vector<double>& rDY)
{
	beta = mC * sin(2*M_PI*mFreq*time); // Define the beta function

	// rY[0] = u and rY[1] = r
	rDY[0] = mA*rY[0] * (rY[0] - beta) * (mDelta - rY[0]) - mB * rY[1];
	rDY[1] = mEpsilon * (rY[0] - mGamma*rY[1]);
}
