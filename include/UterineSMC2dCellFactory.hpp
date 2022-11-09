#ifndef UTERINESMC2DCELLFACTORY_HPP
#define UTERINESMC2DCELLFACTORY_HPP

#include <toml.hpp>
#include "MonodomainProblem.hpp"
#include "SimpleStimulus.hpp"
#include "HodgkinHuxley1952.hpp"
#include "ChayKeizer.hpp"

namespace USMC_2D_SYSTEM_CONSTANTS
{
	const std::string CONFIG_PATH = 
		"/usr/local/config/2d_params.toml";
}

class UterineSMC2dCellFactory : public AbstractCardiacCellFactory<2>
{
protected:
    boost::shared_ptr<SimpleStimulus> mpStimulus;
	double mpX_stim_start;
	double mpX_stim_end;
	double mpY_stim_start;
	double mpY_stim_end;
	std::string mpCell_type;
	unsigned short int mpCell_id; // 0 for HH, 1 for CK


public:
	UterineSMC2dCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	void ReadConfigParams(std::string config_path);
	void PrintParams();

};

#endif // UTERINESMC2DCELLFACTORY_HPP
