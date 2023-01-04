#include "AbstractUterineCellFactory.hpp"
#include "Exception.hpp"

AbstractUterineCellFactory::AbstractUterineCellFactory() : 
	AbstractCardiacCellFactory<2>()
{
	ReadConfigParams(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);
}


AbstractCardiacCell* AbstractUterineCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
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


void AbstractUterineCellFactory::ReadConfigParams(std::string config_path)
{
	const auto params = toml::parse(config_path);
	
	mpCell_type = toml::find<std::string>(params, "cell_type");

	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);
	
	// Cell id
	mpCell_id = toml::find<unsigned short int>(cell_params, "cell_id");
}


void AbstractUterineCellFactory::PrintParams()
{
	std::cout << "mpCell_type = " << mpCell_type << "\n";
	std::cout << "mpCell_id = " << mpCell_id << "\n";
}


std::string AbstractUterineCellFactory::GetCellType()
{
	return mpCell_type;
}
