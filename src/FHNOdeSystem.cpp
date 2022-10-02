#include "FHNOdeSystem.hpp"
#include "Exception.hpp"

FHNOdeSystem::FHNOdeSystem() : AbstractOdeSystem(2)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();

	// Initialise parameters with default config files
	ReadSysConfig(FHN_ODE_SYSTEM_CONSTANTS::SYS_CONFIG_PATH);
	ReadParamConfig(FHN_ODE_SYSTEM_CONSTANTS::PARAM_CONFIG_PATH);
}


FHNOdeSystem::FHNOdeSystem(std::string paramConfigFile, 
	std::string sysConfigFile) : AbstractOdeSystem(2)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();

	ReadSysConfig(sysConfigFile);
	ReadParamConfig(paramConfigFile);
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
	std::string tableName;
	const auto params = toml::parse(configFile);

	if (mSlowWave)
	{
		tableName = "FHNSlowWave";
	}

	else
	{
		tableName = "FHNOriginal";
	}

	const auto& FHNOdeSystemParams = toml::find(params, tableName);

	mA = toml::find<double>(FHNOdeSystemParams, "A");
	mB = toml::find<double>(FHNOdeSystemParams, "B");
	mC = toml::find<double>(FHNOdeSystemParams, "C");
	mFreq = toml::find<double>(FHNOdeSystemParams, "f");
	mBeta = toml::find<double>(FHNOdeSystemParams, "beta");
	mDelta = toml::find<double>(FHNOdeSystemParams, "delta");
	mEpsilon = toml::find<double>(FHNOdeSystemParams, "epsilon");
	mGamma = toml::find<double>(FHNOdeSystemParams, "gamma");
	mStim = toml::find<double>(FHNOdeSystemParams, "Istim");
	
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
	std::cout << "mBeta = " << mBeta << "\n";
	std::cout << "mDelta = " << mDelta << "\n";
	std::cout << "mEpsilon = " << mEpsilon << "\n";
	std::cout << "mGamma = " << mGamma << "\n";
	std::cout << "mStim = " << mStim << "\n";
	std::cout << "mSlowWave = " << mSlowWave << "\n";
}
