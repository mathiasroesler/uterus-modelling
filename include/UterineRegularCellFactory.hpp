#ifndef UTERINEREGULARCELLFACTORY_HPP
#define UTERINEREGULARCELLFACTORY_HPP

#include <toml.hpp>
#include "AbstractUterineCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "RegularStimulus.hpp"

class UterineRegularCellFactory : public AbstractUterineCellFactory
{
private:
	double mpX_stim_start;
	double mpX_stim_end;
	double mpY_stim_start;
	double mpY_stim_end;
    boost::shared_ptr<RegularStimulus> mpStimulus;

public:
	UterineRegularCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();
};

#endif // UTERINEREGULARCELLFACTORY_HPP

