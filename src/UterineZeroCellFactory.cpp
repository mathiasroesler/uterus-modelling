#include "UterineZeroCellFactory.hpp"
#include "Exception.hpp"

UterineZeroCellFactory::UterineZeroCellFactory() : 
	AbstractUterineCellFactory(), 
	mpStimulus(new ZeroStimulus())
{
}


AbstractCardiacCell* UterineZeroCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
{
	return AbstractUterineCellFactory::CreateCardiacCellForTissueNode(pNode);
}


void UterineZeroCellFactory::ReadConfigParams(std::string config_path)
{
	AbstractUterineCellFactory::ReadConfigParams(config_path);
}


void UterineZeroCellFactory::PrintParams()
{
	AbstractUterineCellFactory::PrintParams();
}


