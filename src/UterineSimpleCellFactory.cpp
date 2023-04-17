#include "UterineSimpleCellFactory.hpp"
#include "Exception.hpp"

UterineSimpleCellFactory::UterineSimpleCellFactory() : 
	AbstractUterineCellFactory(), 
	mpStimulus(new SimpleStimulus(0.0, 0.0))
{
	ReadParams(USMC_2D_SYSTEM_CONSTANTS::GENERAL_PARAM_FILE);
	ReadCellParams(mpCell_type + ".toml");
}


AbstractCardiacCell* UterineSimpleCellFactory::CreateCardiacCellForTissueNode(
	Node<2>* pNode)
{
	double x = pNode->rGetLocation()[0];
	double y = pNode->rGetLocation()[1];

	if (x >= mpX_stim_start && x <= mpX_stim_end && 
			y >= mpY_stim_start && y <= mpY_stim_end)
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
		return AbstractUterineCellFactory::CreateCardiacCellForTissueNode(pNode);
	}
}


void UterineSimpleCellFactory::ReadParams(std::string general_param_file)
{
	AbstractUterineCellFactory::ReadParams(general_param_file);

	std::string general_param_path = USMC_2D_SYSTEM_CONSTANTS::CONFIG_DIR +
		general_param_file;
	const auto params = toml::parse(general_param_path);

	// Stimulus location parameters
	mpX_stim_start = toml::find<double>(params, "x_stim_start");
	mpX_stim_end = toml::find<double>(params, "x_stim_end");
	mpY_stim_start = toml::find<double>(params, "y_stim_start");
	mpY_stim_end = toml::find<double>(params, "y_stim_end");
}


void UterineSimpleCellFactory::ReadCellParams(std::string cell_param_file)
{
	std::string cell_param_path = USMC_2D_SYSTEM_CONSTANTS::CONFIG_DIR +
		cell_param_file;
	const auto cell_params = toml::parse(cell_param_path);
	
	// Stimulus parameters
	mpStimulus->SetMagnitude(toml::find<double>(cell_params, "magnitude"));
	mpStimulus->SetDuration(toml::find<double>(cell_params, "duration"));
	mpStimulus->SetStartTime(toml::find<double>(cell_params, "start_time"));
}


void UterineSimpleCellFactory::PrintParams()
{
	AbstractUterineCellFactory::PrintParams();
	std::cout << "mpX_stim_start = " << mpX_stim_start << "\n";
	std::cout << "mpX_stim_end = " << mpX_stim_end << "\n";
	std::cout << "mpY_stim_start = " << mpY_stim_start << "\n";
	std::cout << "mpY_stim_end = " << mpY_stim_end << "\n";
	std::cout << "mpStimulus magnitude = " << mpStimulus->GetMagnitude() << std::endl;
	std::cout << "mpStimulus duration = " << mpStimulus->GetDuration() << std::endl;
	std::cout << "mpStimulus start time = " << mpStimulus->GetStartTime() << std::endl;
}


void UterineSimpleCellFactory::WriteLogInfo(std::string log_file)
{
	AbstractUterineCellFactory::WriteLogInfo(log_file);

	std::ofstream log_stream;
	log_stream.open(log_file, ios::app); // Open log file in append mode

	log_stream << "Stimulus parameters" << std::endl;
	log_stream << "  type: simple" << std::endl;
	log_stream << "  start time: " << mpStimulus->GetStartTime() << " ms" << std::endl; 
	log_stream << "  duration: " << mpStimulus->GetDuration() << " ms" << std::endl;
	log_stream << "  magnitude: " << mpStimulus->GetMagnitude() << " uA/cm2" << std::endl;
	log_stream << "  stimulated region: " << mpX_stim_start << " <= x <= ";
	log_stream << mpX_stim_end << "   " << mpY_stim_start << " <= y <= ";
	log_stream << mpY_stim_end << std::endl;

	log_stream.close();
}
