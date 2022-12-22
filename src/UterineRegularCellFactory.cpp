#include "UterineRegularCellFactory.hpp"
#include "Exception.hpp"

UterineRegularCellFactory::UterineRegularCellFactory() : 
	AbstractUterineCellFactory(), 
	mpStimulus(new RegularStimulus(0.0, 0.0, 0.1, 0.0))
{
	ReadConfigParams(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);
}


AbstractCardiacCell* UterineRegularCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
{
	double x = pNode->rGetLocation()[0];
	double y = pNode->rGetLocation()[1];

	if (x > mpX_stim_start && x < mpX_stim_end && 
			y > mpY_stim_start && y < mpY_stim_end)
	{
		switch (mpCell_id)
		{
			case 0:
				return new CellHodgkinHuxley1952FromCellML(mpSolver,
					mpStimulus);

			case 1:
				return new CellChayKeizer1983FromCellML(mpSolver, mpStimulus);

			case 2:
				return new CellMeans2022FromCellML(mpSolver, mpStimulus);
		
			default:
				return new CellHodgkinHuxley1952FromCellML(mpSolver,
					mpStimulus);
		}
	}
	else
	{
		/* The other cells have zero stimuli. */
		return AbstractUterineCellFactory::CreateCardiacCellForTissueNode(pNode);
	}
}


void UterineRegularCellFactory::ReadConfigParams(std::string config_path)
{
	AbstractUterineCellFactory::ReadConfigParams(config_path);
	const auto params = toml::parse(config_path);
	
	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);

	// Stimulus location parameters
	mpX_stim_start = toml::find<double>(cell_params, "x_stim_start");
	mpX_stim_end = toml::find<double>(cell_params, "x_stim_end");
	mpY_stim_start = toml::find<double>(cell_params, "y_stim_start");
	mpY_stim_end = toml::find<double>(cell_params, "y_stim_end");
	
	// Stimulus parameters
	mpStimulus->SetMagnitude(toml::find<double>(cell_params, "magnitude"));
	mpStimulus->SetPeriod(toml::find<double>(cell_params, "period"));
	mpStimulus->SetDuration(toml::find<double>(cell_params, "duration"));
	mpStimulus->SetStartTime(toml::find<double>(cell_params, "start_time"));
} 


void UterineRegularCellFactory::PrintParams()
{
	AbstractUterineCellFactory::PrintParams();
	std::cout << "mpX_stim_start = " << mpX_stim_start << "\n";
	std::cout << "mpX_stim_end = " << mpX_stim_end << "\n";
	std::cout << "mpY_stim_start = " << mpY_stim_start << "\n";
	std::cout << "mpY_stim_end = " << mpY_stim_end << "\n";
	std::cout << "mpStimulus magnitude = " << mpStimulus->GetMagnitude() << std::endl;
	std::cout << "mpStimulus period = " << mpStimulus->GetPeriod() << std::endl;
	std::cout << "mpStimulus duration = " << mpStimulus->GetDuration() << std::endl;
	std::cout << "mpStimulus start time = " << mpStimulus->GetStartTime() << std::endl;
}

