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


FHNOdeSystem::FHNOdeSystem(std::string configFile) : AbstractOdeSystem(2)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();

	ReadConfig(configFile);
}

void FHNOdeSystem::EvaluateYDerivatives(double time, 
	const std::vector<double>& rY, std::vector<double>& rDY)
{
	double beta = mC * sin(2*M_PI*mFreq*time); // Define the beta function

	// rY[0] = u and rY[1] = r
	rDY[0] = mA*rY[0] * (rY[0] - beta) * (mDelta - rY[0]) - mB * rY[1];
	rDY[1] = mEpsilon * (rY[0] - mGamma*rY[1]);
}


void FHNOdeSystem::ReadConfig(std::string configFile)
{
	const auto params = toml::parse(configFile);
	const auto& FHNSlowWaveParams = toml::find(params, "FHNSlowWave");

	mA = toml::find<double>(FHNSlowWaveParams, "A");
	mB = toml::find<double>(FHNSlowWaveParams, "B");
	mC = toml::find<double>(FHNSlowWaveParams, "C");
	mFreq = toml::find<double>(FHNSlowWaveParams, "f");
	mDelta = toml::find<double>(FHNSlowWaveParams, "delta");
	mEpsilon = toml::find<double>(FHNSlowWaveParams, "epsilon");
	mGamma = toml::find<double>(FHNSlowWaveParams, "gamma");
	
}


void FHNOdeSystem::ReadSysConfig(std::string configFile)
{
	const auto sysParams = toml::parse(configFile);
	
	mSlowWave = toml::find<bool>(sysParams, slowWave);
}


void FHNOdeSystem::PrintParams()
{
	// Print all parameters for testing purposes
	std::cout << "mA = " << mA << "\n";
	std::cout << "mB = " << mB << "\n";
	std::cout << "mC = " << mC << "\n";
	std::cout << "mFreq = " << mFreq << "\n";
	std::cout << "mDelta = " << mDelta << "\n";
	std::cout << "mEpsilon = " << mEpsilon << "\n";
	std::cout << "mGamma = " << mGamma << "\n";
}
