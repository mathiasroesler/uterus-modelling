#ifndef SIMULATIONS_HPP
#define SIMULATIONS_HPP

#include <iostream>
#include "Exception.hpp"
#include "PetscException.hpp"
#include "FHNOdeSystem.hpp"
#include "UterineSMC2dSimpleCellFactory.hpp"
#include "UterineSMC2dRegularCellFactory.hpp"
#include "UterineSMC2dZeroCellFactory.hpp"

void simulation_0d();
void simulation_2d();

#endif // SIMULATIONS_HPP

