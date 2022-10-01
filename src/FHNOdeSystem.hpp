#ifndef FHNODESYSTEM_HPP
#define FHNODESYSTEM_HPP

#include "CheckpointArchiveTypes.hpp"
#include "EulerIvpOdeSolver.hpp"
#include "AbstractOdeSystem.hpp"
#include "OdeSystemInformation.hpp"


class FHNOdeSystem : public AbstractOdeSystem
{
public:
    FHNOdeSystem();

    void EvaluateYDerivatives(double time, const std::vector<double>& rY,
                              std::vector<double>& rDY);
};

template<>
void OdeSystemInformation<FHNOdeSystem>::Initialise()
{
    this->mVariableNames.push_back("y");
    this->mVariableUnits.push_back("dimensionless");
    this->mInitialConditions.push_back(0.0);

    this->mInitialised = true;
}

#endif // FHNODESYSTEM_HPP
