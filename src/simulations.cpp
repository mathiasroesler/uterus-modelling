#include "simulations.hpp"

void simulation_0d()
{
	FHNOdeSystem ode;
	EulerIvpOdeSolver euler_solver;

	const auto sysParams = toml::parse(
		FHN_ODE_SYSTEM_CONSTANTS::CONFIG_PATH);

	auto initial_conditions = toml::find<std::vector<double>>(
		sysParams, "initial_conditions");

	const double start_time = toml::find<double>(sysParams, "start_time");
	const double end_time = toml::find<double>(sysParams, "end_time");
	const double timestep = toml::find<double>(sysParams, "timestep");
	const double sampling_step = toml::find<double>(sysParams, 
		"sampling_step");

	std::cout << "Running 0D simulation..." << std::endl;

	OdeSolution solution = euler_solver.Solve(&ode, initial_conditions, 
		start_time, end_time, timestep, sampling_step);

	solution.WriteToFile("0d_simulation", "ode_solution", "sec");
}


void simulation_2d()
{
	// Get parameters from config file
	const auto sys_params = toml::parse(
		USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);

	// Time constants
	const double sim_duration = toml::find<double>(sys_params, "sim_duration");
	const double ode_timestep = toml::find<double>(sys_params, "ode_timestep");
	const double pde_timestep = toml::find<double>(sys_params, "pde_timestep");
	const double print_timestep = toml::find<double>(sys_params, 
		"print_timestep");

	const std::string mesh_path = toml::find<std::string>(sys_params, 
		"mesh_path");
	const std::string cell_type = toml::find<std::string>(sys_params, 
		"cell_type");
	const std::string save_dir = toml::find<std::string>(sys_params,
		"save_dir"); // Top folder to save results
	const std::string stimulus_type = toml::find<std::string>(sys_params,
		"stimulus_type"); // Regular or simple stimulus

	const auto& cell_params = toml::find(sys_params, cell_type);

	// Cell parameters
	auto conductivities = toml::find<std::vector<double>>(
		cell_params, "conductivities");	
	const double capacitance = toml::find<double>(cell_params, "capacitance");
	
	std::string default_ionic_model = cell_type + "I";
	std::string save_path = save_dir + "/" + cell_type + "/" + stimulus_type;

	HeartConfig::Instance()->SetSimulationDuration(sim_duration); //ms
	HeartConfig::Instance()->SetMeshFileName(mesh_path);
	HeartConfig::Instance()->SetOutputDirectory(save_path);
	HeartConfig::Instance()->SetOutputFilenamePrefix("results");

	HeartConfig::Instance()->SetVisualizeWithVtk(true);

	UterineSMC2dCellFactory *factory = NULL;

	if (stimulus_type == "simple")
	{
		factory = new UterineSMC2dSimpleCellFactory();
	}

	else if (stimulus_type == "regular")
	{
		factory = new UterineSMC2dRegularCellFactory();
	}

	else
	{
		const std::string err_message = "Unrecognized stimulus type";
		const std::string err_filename = "simulations.cpp";
		unsigned line_number = 86;

		throw Exception(err_message, err_filename, line_number);
	}

	MonodomainProblem<2> monodomain_problem(factory);

	HeartConfig::Instance()->SetIntracellularConductivities(Create_c_vector(
		conductivities[0], conductivities[1]));

	// HeartConfig::Instance()->SetSurfaceAreaToVolumeRatio(1400); // 1/cm
	HeartConfig::Instance()->SetCapacitance(capacitance); // uF/cm^2

	HeartConfig::Instance()->SetOdePdeAndPrintingTimeSteps(ode_timestep, 
		pde_timestep, print_timestep);
	HeartConfig::Instance()->SetDefaultIonicModel(default_ionic_model);

	// Print information on the simulation to screen
	std::cout << "Running 2D simulation..." << std::endl;

	std::cout << "\nStimulus type: " << stimulus_type << std::endl;
	std::cout << "\nuSMC cell factory parameters:\n" << std::endl;
	factory->PrintParams();
	std::cout << "x axis conductance = " << conductivities[0] << std::endl;
	std::cout << "y axis conductance = " << conductivities[1] << std::endl;

	std::cout << std::endl;

	monodomain_problem.Initialise();
	monodomain_problem.Solve();

	HeartEventHandler::Headings();
	HeartEventHandler::Report();
}

