#ifndef UTERINESMC2DCELLFACTORY_HPP
#define UTERINESMC2DCELLFACTORY_HPP

#include <toml.hpp>
#include "MonodomainProblem.hpp"
#include "ZeroStimulus.hpp"
#include "HodgkinHuxley1952.hpp"
#include "ChayKeizer1983.hpp"
#include "Means2022.hpp"

namespace USMC_2D_SYSTEM_CONSTANTS
{
	const std::string CONFIG_PATH = 
		"/usr/local/config/2d_params.toml";
}

class UterineSMC2dCellFactory : public AbstractCardiacCellFactory<2>
{
protected:
	std::string mpCell_type;
	unsigned short int mpCell_id; // 0 for HH, 1 for CK


public:
	UterineSMC2dCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	std::string GetCellType();
	virtual void ReadConfigParams(std::string config_path);
	virtual void PrintParams();

};

#endif // UTERINESMC2DCELLFACTORY_HPP
