#ifndef TESTREAD2DPARAMCONFIG_HPP_
#define TESTREAD2DPARAMCONFIG_HPP_

#include <cxxtest/TestSuite.h>
/* Most Chaste come uses PETSc to solve linear algebra problems.  This involves starting PETSc at the beginning of a test-suite
 * and closing it at the end.  (If you never run come in parallel then it is safe to replace PetscSetupAndFinalize.hpp with FakePetscSetup.hpp)
 */
#include "PetscSetupAndFinalize.hpp"
#include "UterineSMC2dCellFactory.hpp"

/**
 * @file
 *
 * This is an example of a CxxTest test suite, used to test the source
 * come, and also used to run simulations (as it provides a handy
 * shortcut to compile and link against the correct libraries using scons).
 *
 * You can #include any of the files in the project 'src' folder.
 * For example here we #include "Hello.hpp"
 *
 * You can utilise any of the come in the main the Chaste trunk
 * in exactly the same way.
 * NOTE: you will have to alter the project SConscript file lines 41-44
 * to enable #including of come from the 'heart', 'cell_based' or 'crypt'
 * components of Chaste.
 */

class TestRead2dParamConfig : public CxxTest::TestSuite
{
public:
    void TestRead2dParamConfigClass()
    {
        UterineSMC2dCellFactory uSMC_factory; // Create an FHN ODE system

		uSMC_factory.ReadConfigParams(
			"projects/chaste_modelling/config/2d_params.toml");
		uSMC_factory.ReadConfigParams("/usr/local/config/2d_params.toml");
		uSMC_factory.ReadConfigParams(USMC_2D_SYSTEM_CONSTANTS::CONFIG_PATH);

		uSMC_factory.PrintParams();
    }
};

#endif /*TESTREAD2DPARAMCONFIG_HPP_*/
