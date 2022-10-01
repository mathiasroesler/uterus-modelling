#ifndef FHNODESYSTEM_HPP
#define FHNODESYSTEM_HPP

#include "CheckpointArchiveTypes.hpp"
#include "EulerIvpOdeSolver.hpp"
#include "AbstractOdeSystem.hpp"
#include "OdeSystemInformation.hpp"
#include <cmath>


class FHNOdeSystem : public AbstractOdeSystem
{
private:
	double mA;
	double mB;
	double mC;
	double mFreq;
	double mDelta;
	double mGamma;
	double mEpsilon;

public:
    FHNOdeSystem();

    void EvaluateYDerivatives(double time, const std::vector<double>& rY,
                              std::vector<double>& rDY);
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
