#ifndef UTERINEZEROCELLFACTORY_HPP
#define UTERINEZEROCELLFACTORY_HPP

#include <toml.hpp>
#include "AbstractUterineCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "ZeroStimulus.hpp"

class UterineZeroCellFactory : public AbstractUterineCellFactory
{
private:
    boost::shared_ptr<ZeroStimulus> mpStimulus;

public:
	UterineZeroCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();
};

#endif // UTERINEZEROCELLFACTORY_HPP


