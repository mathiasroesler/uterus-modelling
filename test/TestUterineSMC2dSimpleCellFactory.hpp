#ifndef TESTUTERINESMC2DSIMPLECELLFACTORY_HPP_
#define TESTUTERINESMC2DSIMPLECELLFACTORY_HPP_

#include <cxxtest/TestSuite.h>
#include "PetscSetupAndFinalize.hpp"
#include "UterineSMC2dSimpleCellFactory.hpp"

class TestUterineSMC2dSimpleCellFactory : public CxxTest::TestSuite
{
public:
    void TestUterineSMC2dSimpleCellFactoryClass()
    {
		HeartConfig::Instance()->SetSimulationDuration(5.0); //ms
        HeartConfig::Instance()->SetMeshFileName("mesh/test/data/2D_0_to_1mm_800_elements");
        HeartConfig::Instance()->SetOutputDirectory("MonodomainTest");
        HeartConfig::Instance()->SetOutputFilenamePrefix("results");

        HeartConfig::Instance()->SetVisualizeWithVtk(true);

		UterineSMC2dSimpleCellFactory factory;

		factory.PrintParams();

        MonodomainProblem<2> monodomain_problem( &factory );

        HeartConfig::Instance()->SetIntracellularConductivities(Create_c_vector(1.75, 0.19));
        HeartConfig::Instance()->SetExtracellularConductivities(Create_c_vector(6.2, 2.4));

        HeartConfig::Instance()->SetSurfaceAreaToVolumeRatio(1400); // 1/cm
        HeartConfig::Instance()->SetCapacitance(1.0); // uF/cm^2

        HeartConfig::Instance()->SetOdePdeAndPrintingTimeSteps(0.01, 0.01, 0.1);

        monodomain_problem.Initialise();

        monodomain_problem.Solve();

        HeartEventHandler::Headings();
        HeartEventHandler::Report();
    }
};

#endif /*TESTUTERINESMC2DSIMPLECELLFACTORY_HPP_*/
