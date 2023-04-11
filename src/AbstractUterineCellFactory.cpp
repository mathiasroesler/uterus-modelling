#include "AbstractUterineCellFactory.hpp"
#include "Exception.hpp"

AbstractUterineCellFactory::AbstractUterineCellFactory() : 
	AbstractCardiacCellFactory<2>()
{
	ReadParams(USMC_2D_SYSTEM_CONSTANTS::GENERAL_PARAM_FILE);
}


AbstractCardiacCell* AbstractUterineCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
{
	AbstractCardiacCell* cell;

	switch (mpCell_id)
	{
		case 0:
			cell = new CellHodgkinHuxley1952FromCellML(mpSolver,
				mpZeroStimulus);
			break;

		case 1:
			cell = new CellChayKeizer1983FromCellML(mpSolver, mpZeroStimulus);
			break;

		case 2:
			cell = new CellMeans2022FromCellML(mpSolver, mpZeroStimulus);
			break;
		
		case 3:
			cell = new CellTong2014FromCellML(mpSolver, mpZeroStimulus);
			break;

		default:
			cell = new CellHodgkinHuxley1952FromCellML(mpSolver,
				mpZeroStimulus);
	}	

	return cell;
}


std::string AbstractUterineCellFactory::GetCellType()
{
	return mpCell_type;
}


void AbstractUterineCellFactory::ReadParams(std::string general_param_file)
{
	std::string general_param_path = USMC_2D_SYSTEM_CONSTANTS::CONFIG_DIR +
		general_param_file;
	const auto params = toml::parse(general_param_path);
	
	mpCell_type = toml::find<std::string>(params, "cell_type");

	// Get the cell id
	std::string cell_param_file = mpCell_type + ".toml";
	ReadCellParams(cell_param_file);
}


void AbstractUterineCellFactory::ReadCellParams(std::string cell_param_file)
{
	std::string cell_param_path = USMC_2D_SYSTEM_CONSTANTS::CONFIG_DIR +
		cell_param_file;
	const auto cell_params = toml::parse(cell_param_path);
	
	mpCell_id = toml::find<unsigned short int>(cell_params, "cell_id");
}


void AbstractUterineCellFactory::PrintParams()
{
	std::cout << "mpCell_type = " << mpCell_type << "\n";
	std::cout << "mpCell_id = " << mpCell_id << "\n";
}


void AbstractUterineCellFactory::WriteLogInfo(std::string log_file)
{
	std::ofstream log_stream;
	log_stream.open(log_file, ios::app); // Open log file in append mode

	log_stream << "Cell type: " << mpCell_type << std::endl;

	log_stream.close();
}
