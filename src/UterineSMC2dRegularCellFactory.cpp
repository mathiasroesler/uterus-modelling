#include "UterineSMC2dRegularCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dRegularCellFactory::UterineSMC2dRegularCellFactory() : 
	UterineSMC2dCellFactory(), 
	mpStimulus(new RegularStimulus(0.0, 0.0, 0.1, 0.0))
{
	const auto params = toml::parse(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);
	
	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);
	
	// Stimulus parameters
	mpStimulus->SetMagnitude(toml::find<double>(cell_params, "magnitude"));
	mpStimulus->SetPeriod(toml::find<double>(cell_params, "period"));
	mpStimulus->SetDuration(toml::find<double>(cell_params, "duration"));
	mpStimulus->SetStartTime(toml::find<double>(cell_params, "start_time"));
}


AbstractCardiacCell* UterineSMC2dRegularCellFactory::CreateCardiacCellForTissueNode(
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
		return UterineSMC2dCellFactory::CreateCardiacCellForTissueNode(pNode);
	}
}


void UterineSMC2dRegularCellFactory::PrintParams()
{
	UterineSMC2dCellFactory::PrintParams();
	std::cout << "mpStimulus magnitude = " << mpStimulus->GetMagnitude() << std::endl;
	std::cout << "mpStimulus period = " << mpStimulus->GetPeriod() << std::endl;
	std::cout << "mpStimulus duration = " << mpStimulus->GetDuration() << std::endl;
	std::cout << "mpStimulus start time = " << mpStimulus->GetStartTime() << std::endl;
}

