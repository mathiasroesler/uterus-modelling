#include "simulations.hpp"

void simulation_0d()
{
	FHNOdeSystem ode;
	EulerIvpOdeSolver euler_solver;

	const auto sysParams = toml::parse(
		FHN_ODE_SYSTEM_CONSTANTS::SYS_CONFIG_PATH);

	auto initial_conditions = toml::find<std::vector<double>>(
		sysParams, "initial_conditions");

	const double start_time = toml::find<double>(sysParams, "start_time");
	const double end_time = toml::find<double>(sysParams, "end_time");
	const double timestep = toml::find<double>(sysParams, "timestep");
	const double sampling_step = toml::find<double>(sysParams, 
		"sampling_step");

	OdeSolution solution = euler_solver.Solve(&ode, initial_conditions, 
		start_time, end_time, timestep, sampling_step);

	solution.WriteToFile("0d_simulation", "ode_solution", "sec");
}
