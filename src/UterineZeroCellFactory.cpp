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


void UterineZeroCellFactory::WriteLogInfo(std::string log_file)
{
	std::ofstream log_stream;
	log_stream.open(log_file, ios::app); // Open log file in append mode

	log_stream << "Stimulus parameters" << std::endl;
	log_stream << "  type: zero" << std::endl;

	log_stream.close();
}
