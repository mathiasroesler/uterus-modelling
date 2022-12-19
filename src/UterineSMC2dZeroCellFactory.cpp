#include "UterineSMC2dZeroCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dZeroCellFactory::UterineSMC2dZeroCellFactory() : 
	UterineSMC2dCellFactory(), 
	mpStimulus(new ZeroStimulus())
{
}


AbstractCardiacCell* UterineSMC2dZeroCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
{
	return UterineSMC2dCellFactory::CreateCardiacCellForTissueNode(pNode);
}


void UterineSMC2dZeroCellFactory::PrintParams()
{
	UterineSMC2dCellFactory::PrintParams();
}


