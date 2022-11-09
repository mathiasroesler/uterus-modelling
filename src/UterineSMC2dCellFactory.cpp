#include "UterineSMC2dCellFactory.hpp"
#include "Exception.hpp"

UterineSMC2dCellFactory::UterineSMC2dCellFactory() : 
	AbstractCardiacCellFactory<2>()
{
	ReadConfigParams(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);
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
