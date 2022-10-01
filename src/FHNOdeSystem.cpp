#include "FHNOdeSystem.hpp"
#include "Exception.hpp"

FHNOdeSystem::FHNOdeSystem() : AbstractOdeSystem(1)
{
	mpSystemInfo = OdeSystemInformation<FHNOdeSystem>::Instance();
}

void FHNOdeSystem::EvaluateYDerivatives(double time, 
	const std::vector<double>& rY, std::vector<double>& rDY)
{
	rDY[0] = rY[0]*rY[0] + time*time;
}
