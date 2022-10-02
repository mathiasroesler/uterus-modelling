#include "FHNOdeSystem.hpp"
#include "Exception.hpp"

FHNOdeSystem::FHNOdeSystem() : AbstractOdeSystem(2)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();

	// Initialise parameters with default config files
	ReadParamConfig(FHN_ODE_SYSTEM_CONSTANTS::PARAM_CONFIG_PATH);
	ReadSysConfig(FHN_ODE_SYSTEM_CONSTANTS::SYS_CONFIG_PATH);
}


FHNOdeSystem::FHNOdeSystem(std::string configFile) : AbstractOdeSystem(2)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();

	ReadParamConfig(configFile);
}

void FHNOdeSystem::EvaluateYDerivatives(double time, 
	const std::vector<double>& rY, std::vector<double>& rDY)
{
	double beta = mC * sin(2*M_PI*mFreq*time); // Define the beta function

	// rY[0] = u and rY[1] = r
	rDY[0] = mA*rY[0] * (rY[0] - beta) * (mDelta - rY[0]) - mB * rY[1];
	rDY[1] = mEpsilon * (rY[0] - mGamma*rY[1]);
}


void FHNOdeSystem::ReadParamConfig(std::string configFile)
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
	
	mSlowWave = toml::find<bool>(sysParams, "slowWave");
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
	std::cout << "mSlowWave = " << mSlowWave << "\n";
}
