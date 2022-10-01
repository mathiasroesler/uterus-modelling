#ifndef FHNODESYSTEM_HPP
#define FHNODESYSTEM_HPP

#include "CheckpointArchiveTypes.hpp"
#include "EulerIvpOdeSolver.hpp"
#include "AbstractOdeSystem.hpp"
#include "OdeSystemInformation.hpp"

#include "FakePetscSetup.hpp"

class FHNOdeSystem : public AbstractOdeSystem
{
public:
    FHNOdeSystem();

    void EvaluateYDerivatives(double time, const std::vector<double>& rY,
                              std::vector<double>& rDY);
};

template<>
void OdeSystemInformation<FHNOdeSystem>::Initialise();

#endif // FHNODESYSTEM_HPP
