#ifndef FHNODESYSTEM_HPP
#define FHNODESYSTEM_HPP

#include <cmath>
#include <toml.hpp>
#include <iostream>

#include "CheckpointArchiveTypes.hpp"
#include "EulerIvpOdeSolver.hpp"
#include "AbstractOdeSystem.hpp"
#include "OdeSystemInformation.hpp"


namespace FHN_ODE_SYSTEM_CONSTANTS
{
	const std::string PARAM_CONFIG_PATH = 
		"/usr/local/config/params.toml";
	const std::string SYS_CONFIG_PATH = 
		"/usr/local/config/system.toml";
}

class FHNOdeSystem : public AbstractOdeSystem
{
private:
	double mA;
	double mB;
	double mC;
	double mFreq;
	double mBeta;
	double mDelta;
	double mGamma;
	double mEpsilon;
	double mStim;
	bool mSlowWave; // True if slow-wave version of FHN

public:
    FHNOdeSystem();
	FHNOdeSystem(std::string paramConfigFile, std::string sysConfigFile);

    void EvaluateYDerivatives(double time, const std::vector<double>& rY,
                              std::vector<double>& rDY);
	void ReadParamConfig(std::string configFile);
	void ReadSysConfig(std::string configFile);
	void PrintParams();
};

template<>
void OdeSystemInformation<FHNOdeSystem>::Initialise()
{
	// FHN source variable
    this->mVariableNames.push_back("u");
    this->mVariableUnits.push_back("mV");
    this->mInitialConditions.push_back(-1.0);

	// FHN recovery variable
	this->mVariableNames.push_back("r");
	this->mVariableUnits.push_back("mV");
	this->mInitialConditions.push_back(0.0);

    this->mInitialised = true;
}

#endif // FHNODESYSTEM_HPP
