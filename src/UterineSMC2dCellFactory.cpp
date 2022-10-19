#include "UterineSMC2dCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dCellFactory::UterineSMC2dCellFactory() : 
	AbstractCardiacCellFactory<2>(),
	mpStimulus(new SimpleStimulus(-5e5, 0.5))
{
}

UterineSMC2dCellFactory::AbstractCardiacCell* 
	CreateUterineCellForTissueNode(Node<2>* pNode)
{
	double x = pNode->rGetLocation()[0];
	double y = pNode->rGetLocation()
	// if x<=0.02 and y<=0.02 
	if (x<0.02+1e-6 && y<0.02+1e-6) 
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
