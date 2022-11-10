#ifndef UTERINESMC2DREGULARCELLFACTORY_HPP
#define UTERINESMC2DREGULARCELLFACTORY_HPP

#include <toml.hpp>
#include "UterineSMC2dCellFactory.hpp"
#include "MonodomainProblem.hpp"
#include "RegularStimulus.hpp"

class UterineSMC2dRegularCellFactory : public UterineSMC2dCellFactory
{
private:
    boost::shared_ptr<RegularStimulus> mpStimulus;

public:
	UterineSMC2dRegularCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void PrintParams();
};

#endif // UTERINESMC2DREGULARCELLFACTORY_HPP

