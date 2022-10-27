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
	HeartConfig::Instance()->SetSimulationDuration(450.0); //ms
	HeartConfig::Instance()->SetMeshFileName("/home/mathias/Chaste/mesh/test/data/2D_0_to_1mm_800_elements");
	HeartConfig::Instance()->SetOutputDirectory("Monodomain_2D");
	HeartConfig::Instance()->SetOutputFilenamePrefix("results");

	HeartConfig::Instance()->SetVisualizeWithVtk(true);

	UterineSMC2dCellFactory factory;

	MonodomainProblem<2> monodomain_problem( &factory );

	HeartConfig::Instance()->SetIntracellularConductivities(Create_c_vector(1.75, 0.19));

	HeartConfig::Instance()->SetSurfaceAreaToVolumeRatio(1400); // 1/cm
	HeartConfig::Instance()->SetCapacitance(1.0); // uF/cm^2

	HeartConfig::Instance()->SetOdePdeAndPrintingTimeSteps(0.01, 0.01, 0.1);

	std::cout << "Running 2D simulation..." << std::endl;
	monodomain_problem.Initialise();
	monodomain_problem.Solve();

	HeartEventHandler::Headings();
	HeartEventHandler::Report();
}

