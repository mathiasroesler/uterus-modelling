#include "UterineRegularCellFactory3d.hpp"
#include "Exception.hpp"

UterineRegularCellFactory3d::UterineRegularCellFactory3d() : 
	AbstractUterineCellFactory3d(), 
	mpStimulus(new RegularStimulus(0.0, 0.0, 0.1, 0.0))
{
	ReadConfigParams(USMC_3D_SYSTEM_CONSTANTS::CONFIG_PATH);
}


AbstractCardiacCell* UterineRegularCellFactory3d::CreateCardiacCellForTissueNode(
	Node<3>* pNode)
{
	double x = pNode->rGetLocation()[0];
	double y = pNode->rGetLocation()[1];
	double z = pNode->rGetLocation()[2];

	if (x >= mpX_stim_start && x <= mpX_stim_end && 
			y >= mpY_stim_start && y <= mpY_stim_end &&
			z >= mpZ_stim_start && z <= mpZ_stim_end)
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

			case 3:
				return new CellTong2014FromCellML(mpSolver, mpStimulus);
		
			default:
				return new CellHodgkinHuxley1952FromCellML(mpSolver,
					mpStimulus);
		}
	}
	else
	{
		/* The other cells have zero stimuli. */
		return AbstractUterineCellFactory3d::CreateCardiacCellForTissueNode(pNode);
	}
}


void UterineRegularCellFactory3d::ReadConfigParams(std::string config_path)
{
	AbstractUterineCellFactory3d::ReadConfigParams(config_path);
	const auto params = toml::parse(config_path);
	
	// The cell type serves as a table name in the config file
	const auto& cell_params = toml::find(params, mpCell_type);

	// Stimulus location parameters
	mpX_stim_start = toml::find<double>(cell_params, "x_stim_start");
	mpX_stim_end = toml::find<double>(cell_params, "x_stim_end");
	mpY_stim_start = toml::find<double>(cell_params, "y_stim_start");
	mpY_stim_end = toml::find<double>(cell_params, "y_stim_end");
	mpZ_stim_start = toml::find<double>(cell_params, "z_stim_start");
	mpZ_stim_end = toml::find<double>(cell_params, "z_stim_end");
	
	// Stimulus parameters
	mpStimulus->SetMagnitude(toml::find<double>(cell_params, "magnitude"));
	mpStimulus->SetPeriod(toml::find<double>(cell_params, "period"));
	mpStimulus->SetDuration(toml::find<double>(cell_params, "duration"));
	mpStimulus->SetStartTime(toml::find<double>(cell_params, "start_time"));
} 


void UterineRegularCellFactory3d::PrintParams()
{
	AbstractUterineCellFactory3d::PrintParams();
	std::cout << "mpX_stim_start = " << mpX_stim_start << "\n";
	std::cout << "mpX_stim_end = " << mpX_stim_end << "\n";
	std::cout << "mpY_stim_start = " << mpY_stim_start << "\n";
	std::cout << "mpY_stim_end = " << mpY_stim_end << "\n";
	std::cout << "mpZ_stim_start = " << mpZ_stim_start << "\n";
	std::cout << "mpZ_stim_end = " << mpZ_stim_end << "\n";
	std::cout << "mpStimulus magnitude = " << mpStimulus->GetMagnitude() << std::endl;
	std::cout << "mpStimulus period = " << mpStimulus->GetPeriod() << std::endl;
	std::cout << "mpStimulus duration = " << mpStimulus->GetDuration() << std::endl;
	std::cout << "mpStimulus start time = " << mpStimulus->GetStartTime() << std::endl;
}


void UterineRegularCellFactory3d::WriteLogInfo(std::string log_file)
{
	std::ofstream log_stream;
	log_stream.open(log_file, ios::app); // Open log file in append mode

	log_stream << "Stimulus parameters" << std::endl;
	log_stream << "  type: regular" << std::endl;
	log_stream << "  start time: " << mpStimulus->GetStartTime() << " ms" << std::endl; 
	log_stream << "  duration: " << mpStimulus->GetDuration() << " ms" << std::endl;
	log_stream << "  magnitude: " << mpStimulus->GetMagnitude() << " uA/cm2" << std::endl;
	log_stream << "  period: " << mpStimulus->GetPeriod() << " ms" << std::endl;
	log_stream << "  stimulated region: " << mpX_stim_start << " <= x <= ";
	log_stream << mpX_stim_end << "   " << mpY_stim_start << " <= y <= ";
	log_stream << mpY_stim_end << "   " << mpZ_stim_start << " <= z <= ";
	log_stream << mpZ_stim_end << std::endl;

	log_stream.close();
}

