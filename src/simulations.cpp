#include <iostream>
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

	const double sim_duration = toml::find<double>(sys_params, "sim_duration");
	const std::string mesh_path = toml::find<std::string>(sys_params, "mesh_path");
	auto conductivities = toml::find<std::vector<double>>(
		sys_params, "conductivities");	
	const double capacitance = toml::find<double>(sys_params, "capacitance");

	HeartConfig::Instance()->SetSimulationDuration(sim_duration); //ms
	HeartConfig::Instance()->SetMeshFileName(mesh_path);
	HeartConfig::Instance()->SetOutputDirectory("Monodomain_2D");
	HeartConfig::Instance()->SetOutputFilenamePrefix("results");

	HeartConfig::Instance()->SetVisualizeWithVtk(true);

	UterineSMC2dCellFactory factory;

	MonodomainProblem<2> monodomain_problem( &factory );

	HeartConfig::Instance()->SetIntracellularConductivities(Create_c_vector(
		conductivities[0], conductivities[1]));

	// HeartConfig::Instance()->SetSurfaceAreaToVolumeRatio(1400); // 1/cm
	HeartConfig::Instance()->SetCapacitance(capacitance); // uF/cm^2

	HeartConfig::Instance()->SetOdePdeAndPrintingTimeSteps(0.01, 0.01, 0.1);
	HeartConfig::Instance()->SetDefaultIonicModel("ChayKeizerI");

	std::cout << "Running 2D simulation..." << std::endl;
	factory.PrintParams();
	monodomain_problem.Initialise();
	monodomain_problem.Solve();

	HeartEventHandler::Headings();
	HeartEventHandler::Report();
}

