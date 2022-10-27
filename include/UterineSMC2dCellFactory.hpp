#ifndef UTERINESMC2DCELLFACTORY_HPP
#define UTERINESMC2DCELLFACTORY_HPP

#include "MonodomainProblem.hpp"
#include "SimpleStimulus.hpp"
#include "HodgkinHuxley1952.hpp"
#include "ChayKeizer.hpp"

class UterineSMC2dCellFactory : public AbstractCardiacCellFactory<2>
{
private:
    boost::shared_ptr<SimpleStimulus> mpStimulus;
	double mpX_location;
	double mpY_location;
	bool mpChay_keizer; // True if the cell model is Chay-Keizer

public:
	UterineSMC2dCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);

};

#endif // UTERINESMC2DCELLFACTORY_HPP
