#include "UterineSMC2dCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dCellFactory::UterineSMC2dCellFactory() : 
	AbstractCardiacCellFactory<2>(),
	mpStimulus(new SimpleStimulus(-5e5, 5.0))
{
	mpX_location = 0.04;
	mpY_location = 0.02;
	mpChay_keizer = true;
}


AbstractCardiacCell* UterineSMC2dCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
{
	double x = pNode->rGetLocation()[0];
	double y = pNode->rGetLocation()[1];
	// if x<=0.02 and y<=0.02 
	if (x < mpX_location && y < mpY_location) 
	{
		if (mpChay_keizer)
		{
			return new CellChayKeizerFromCellML(mpSolver, mpStimulus);
		}

		else
		{
			return new CellHodgkinHuxley1952FromCellML(mpSolver, mpStimulus);
		}
	}
	else
	{
		/* The other cells have zero stimuli. */
		
		if (mpChay_keizer)
		{
			return new CellChayKeizerFromCellML(mpSolver, mpZeroStimulus);
		}

		else
		{
			return new CellHodgkinHuxley1952FromCellML(mpSolver, mpZeroStimulus);
		}
	}
}
