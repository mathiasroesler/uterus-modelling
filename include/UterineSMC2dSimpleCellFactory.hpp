#ifndef UTERINESMC2DSIMPLECELLFACTORY_HPP
#define UTERINESMC2DSIMPLECELLFACTORY_HPP

#include <toml.hpp>
#include "UterineSMC2dCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "SimpleStimulus.hpp"

class UterineSMC2dSimpleCellFactory : public UterineSMC2dCellFactory
{
private:
	double mpX_stim_start;
	double mpX_stim_end;
	double mpY_stim_start;
	double mpY_stim_end;
    boost::shared_ptr<SimpleStimulus> mpStimulus;

public:
	UterineSMC2dSimpleCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();
};

#endif // UTERINESMC2DSIMPLECELLFACTORY_HPP
