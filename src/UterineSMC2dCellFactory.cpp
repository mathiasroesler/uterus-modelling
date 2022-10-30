#include "UterineSMC2dCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dCellFactory::UterineSMC2dCellFactory() : 
	AbstractCardiacCellFactory<2>(),
	mpStimulus(new SimpleStimulus(-5e5, 5.0))
{
	ReadConfigParams(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);
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
			return new CellChayKeizerFromCellML(mpSolver, mpZeroStimulus);
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


void UterineSMC2dCellFactory::ReadConfigPath(std::string config_path)
{
	const auto params = toml::parse(config_path);
	
	mpCell_type = toml::find<std::string>("cell_type");

	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);
	
	mpX_stim_start = toml::find<double>(cell_params, "x_stim_start");
	mpX_stim_end = toml::find<double>(cell_params, "x_stim_end");
	mpY_stim_start = toml::find<double>(cell_params, "y_stim_start");
	mpY_stim_end = toml::find<double>(cell_params, "y_stim_end");
}
