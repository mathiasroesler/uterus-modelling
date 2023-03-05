#include "AbstractUterineCellFactory3d.hpp"
#include "Exception.hpp"

AbstractUterineCellFactory3d::AbstractUterineCellFactory3d() : 
	AbstractCardiacCellFactory<3>()
{
	ReadConfigParams(USMC_3D_SYSTEM_CONSTANTS::CONFIG_PATH);
}


AbstractCardiacCell* AbstractUterineCellFactory3d::CreateCardiacCellForTissueNode(
	Node<3>* pNode)
{
	switch (mpCell_id)
	{
		case 0:
			return new CellHodgkinHuxley1952FromCellML(mpSolver,
				mpZeroStimulus);

		case 1:
			return new CellChayKeizer1983FromCellML(mpSolver, mpZeroStimulus);

		case 2:
			return new CellMeans2022FromCellML(mpSolver, mpZeroStimulus);
		
		case 3:
			return new CellTong2014FromCellML(mpSolver, mpZeroStimulus);

		default:
			return new CellHodgkinHuxley1952FromCellML(mpSolver,
				mpZeroStimulus);
	}	
}


std::string AbstractUterineCellFactory3d::GetCellType()
{
	return mpCell_type;
}


void AbstractUterineCellFactory3d::ReadConfigParams(std::string config_path)
{
	const auto params = toml::parse(config_path);
	
	mpCell_type = toml::find<std::string>(params, "cell_type");

	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);
	
	// Cell id
	mpCell_id = toml::find<unsigned short int>(cell_params, "cell_id");
}


void AbstractUterineCellFactory3d::PrintParams()
{
	std::cout << "mpCell_type = " << mpCell_type << "\n";
	std::cout << "mpCell_id = " << mpCell_id << "\n";
}


void AbstractUterineCellFactory3d::WriteLogInfo(std::string log_file)
{
	std::ofstream log_stream;
	log_stream.open(log_file, ios::app); // Open log file in append mode

	log_stream << "Cell type: " << mpCell_type << std::endl;

	log_stream.close();
}

