#include "UterineSMC2dCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dCellFactory::UterineSMC2dCellFactory() : 
	AbstractCardiacCellFactory<2>(),
	mpStimulus(new SimpleStimulus(-2e5, 0.5, 10)) // uA/cm2, ms, ms
{
	ReadConfigParams(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);
}


AbstractCardiacCell* UterineSMC2dCellFactory::CreateCardiacCellForTissueNode(
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
				return new CellChayKeizerFromCellML(mpSolver, mpStimulus);
		
			default:
				return new CellHodgkinHuxley1952FromCellML(mpSolver,
					mpStimulus);
		}
	}
	else
	{
		/* The other cells have zero stimuli. */
		switch (mpCell_id)
		{
			case 0:
				return new CellHodgkinHuxley1952FromCellML(mpSolver,
					mpZeroStimulus);

			case 1:
				return new CellChayKeizerFromCellML(mpSolver, mpZeroStimulus);

			default:
				return new CellHodgkinHuxley1952FromCellML(mpSolver,
					mpStimulus);
		}	
	}
}


void UterineSMC2dCellFactory::ReadConfigParams(std::string config_path)
{
	const auto params = toml::parse(config_path);
	
	mpCell_type = toml::find<std::string>(params, "cell_type");

	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);
	
	// Stimulus location parameters
	mpX_stim_start = toml::find<double>(cell_params, "x_stim_start");
	mpX_stim_end = toml::find<double>(cell_params, "x_stim_end");
	mpY_stim_start = toml::find<double>(cell_params, "y_stim_start");
	mpY_stim_end = toml::find<double>(cell_params, "y_stim_end");

	// Stimulus parameters
	mpStimulus->SetMagnitude(toml::find<double>(cell_params, "magnitude"));
	mpStimulus->SetDuration(toml::find<double>(cell_params, "duration"));
	mpStimulus->SetStartTime(toml::find<double>(cell_params, "start_time"));

	// Cell id
	mpCell_id = toml::find<unsigned short int>(cell_params, "cell_id");
}


void UterineSMC2dCellFactory::PrintParams()
{
	std::cout << "mpX_stim_start = " << mpX_stim_start << "\n";
	std::cout << "mpX_stim_end = " << mpX_stim_end << "\n";
	std::cout << "mpY_stim_start = " << mpY_stim_start << "\n";
	std::cout << "mpY_stim_end = " << mpY_stim_end << "\n";
	std::cout << "mpCell_type = " << mpCell_type << "\n";
	std::cout << "mpCell_id = " << mpCell_id << "\n";
}
