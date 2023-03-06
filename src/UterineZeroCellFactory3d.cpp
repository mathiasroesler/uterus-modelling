#include "UterineZeroCellFactory3d.hpp"
#include "Exception.hpp"

UterineZeroCellFactory3d::UterineZeroCellFactory3d() : 
	AbstractUterineCellFactory3d(), 
	mpStimulus(new ZeroStimulus())
{
	AbstractUterineCellFactory3d::ReadParams(
		USMC_3D_SYSTEM_CONSTANTS::GENERAL_PARAM_FILE);
	ReadCellParams(mpCell_type + ".toml");
}


AbstractCardiacCell* UterineZeroCellFactory3d::CreateCardiacCellForTissueNode(
	Node<3>* pNode)
{
	return AbstractUterineCellFactory3d::CreateCardiacCellForTissueNode(pNode);
}


void UterineZeroCellFactory3d::ReadCellParams(std::string cell_param_file)
{
	AbstractUterineCellFactory3d::ReadParams(cell_param_file);
}


void UterineZeroCellFactory3d::PrintParams()
{
	AbstractUterineCellFactory3d::PrintParams();
}


void UterineZeroCellFactory3d::WriteLogInfo(std::string log_file)
{
	std::ofstream log_stream;
	log_stream.open(log_file, ios::app); // Open log file in append mode

	log_stream << "Stimulus parameters" << std::endl;
	log_stream << "  type: zero" << std::endl;

	log_stream.close();
}

