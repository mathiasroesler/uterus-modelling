#ifndef UTERINESMC2DZEROCELLFACTORY_HPP
#define UTERINESMC2DZEROCELLFACTORY_HPP

#include <toml.hpp>
#include "UterineSMC2dCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "ZeroStimulus.hpp"

class UterineSMC2dZeroCellFactory : public UterineSMC2dCellFactory
{
private:
    boost::shared_ptr<ZeroStimulus> mpStimulus;

public:
	UterineSMC2dZeroCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();
};

#endif // UTERINESMC2DZEROCELLFACTORY_HPP


