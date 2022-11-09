#ifndef UTERINESMC2DSIMPLECELLFACTORY_HPP
#define UTERINESMC2DSIMPLECELLFACTORY_HPP

#include <toml.hpp>
#include "UterineSMC2dCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "SimpleStimulus.hpp"
#include "HodgkinHuxley1952.hpp"
#include "ChayKeizer.hpp"

class UterineSMC2dSimpleCellFactory : public UterineSMC2dCellFactory
{
private:
    boost::shared_ptr<SimpleStimulus> mpStimulus;

public:
	UterineSMC2dSimpleCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void PrintParams();
};

#endif // UTERINESMC2DSIMPLECELLFACTORY_HPP
