#ifndef UTERINESMC2DREGULARCELLFACTORY_HPP
#define UTERINESMC2DREGULARCELLFACTORY_HPP

#include <toml.hpp>
#include "UterineSMC2dCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "RegularStimulus.hpp"

class UterineSMC2dRegularCellFactory : public UterineSMC2dCellFactory
{
private:
	double mpX_stim_start;
	double mpX_stim_end;
	double mpY_stim_start;
	double mpY_stim_end;
    boost::shared_ptr<RegularStimulus> mpStimulus;

public:
	UterineSMC2dRegularCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();
};

#endif // UTERINESMC2DREGULARCELLFACTORY_HPP

