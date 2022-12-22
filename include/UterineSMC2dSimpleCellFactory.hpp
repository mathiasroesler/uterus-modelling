#ifndef UTERINESIMPLECELLFACTORY_HPP
#define UTERINESIMPLECELLFACTORY_HPP

#include <toml.hpp>
#include "AbstractUterineCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "SimpleStimulus.hpp"

class UterineSimpleCellFactory : public AbstractUterineCellFactory
{
private:
	double mpX_stim_start;
	double mpX_stim_end;
	double mpY_stim_start;
	double mpY_stim_end;
    boost::shared_ptr<SimpleStimulus> mpStimulus;

public:
	UterineSimpleCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();
};

#endif // UTERINESIMPLECELLFACTORY_HPP
