#ifndef UTERINESMC2DCELLFACTORY_HPP
#define UTERINESMC2DCELLFACTORY_HPP

#include "MonodomainProblem.hpp"
#include "SimpleStimulus.hpp"
#include "HodgkinHuxley1952.hpp"

class UterineSMC2dCellFactory : public AbstractCardiacCellFactory<2>
{
private:
    boost::shared_ptr<SimpleStimulus> mpStimulus;

public:
	UterineSMC2dCellFactory() : 
		AbstractCardiacCellFactory<2>(),
		mpStimulus(new SimpleStimulus(-5e5, 0.5))
	{
	}

    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode)
	{
		double x = pNode->rGetLocation()[0];
		double y = pNode->rGetLocation()[1];
		// if x<=0.02 and y<=0.02 
		if (x < 0.02+1e-6 && y < 0.02+1e-6) 
		{
			return new CellHodgkinHuxley1952FromCellML(mpSolver, mpStimulus);
		}
		else
		{
			/* The other cells have zero stimuli. */
			return new CellHodgkinHuxley1952FromCellML(mpSolver, mpZeroStimulus);
		}
	}
};

#endif // UTERINESMC2DCELLFACTORY_HPP
