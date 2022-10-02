#ifndef TESTREADCONFIG_HPP_
#define TESTREADCONFIG_HPP_

#include <cxxtest/TestSuite.h>
/* Most Chaste code uses PETSc to solve linear algebra problems.  This involves starting PETSc at the beginning of a test-suite
 * and closing it at the end.  (If you never run code in parallel then it is safe to replace PetscSetupAndFinalize.hpp with FakePetscSetup.hpp)
 */
#include "PetscSetupAndFinalize.hpp"
#include "FHNOdeSystem.hpp"

/**
 * @file
 *
 * This is an example of a CxxTest test suite, used to test the source
 * code, and also used to run simulations (as it provides a handy
 * shortcut to compile and link against the correct libraries using scons).
 *
 * You can #include any of the files in the project 'src' folder.
 * For example here we #include "Hello.hpp"
 *
 * You can utilise any of the code in the main the Chaste trunk
 * in exactly the same way.
 * NOTE: you will have to alter the project SConscript file lines 41-44
 * to enable #including of code from the 'heart', 'cell_based' or 'crypt'
 * components of Chaste.
 */

class TestReadParamConfig : public CxxTest::TestSuite
{
public:
    void TestReadParamConfigClass()
    {
        FHNOdeSystem ode; // Create an FHN ODE system
		FHNOdeSystem ode2("projects/chaste_modelling/config/params.toml");
		FHNOdeSystem ode3(FHN_ODE_SYSTEM_CONSTANTS::PARAM_CONFIG_PATH);

		ode.ReadParamConfig("projects/chaste_modelling/config/params.toml");

		ode.PrintParams();
		ode2.PrintParams();
		ode3.PrintParams();
    }
};

#endif /*TESTREADCONFIG_HPP_*/
