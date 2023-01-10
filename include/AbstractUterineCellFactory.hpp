#ifndef ABSTRACTUTERINECELLFACTORY_HPP
#define ABSTRACTUTERINECELLFACTORY_HPP

#include <toml.hpp>
#include "MonodomainProblem.hpp"
#include "ZeroStimulus.hpp"
#include "HodgkinHuxley1952.hpp"
#include "ChayKeizer1983.hpp"
#include "Means2022.hpp"
#include "Tong2014.hpp"

namespace USMC_2D_SYSTEM_CONSTANTS
{
	const std::string CONFIG_PATH = 
		"/usr/local/config/2d_params.toml";
}

class AbstractUterineCellFactory : public AbstractCardiacCellFactory<2>
{
protected:
	std::string mpCell_type;
	unsigned short int mpCell_id; // 0 = HH, 1 = CK, 2 = Means, 3 = Tong


public:
	AbstractUterineCellFactory();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<2>* pNode);
	std::string GetCellType();
	virtual void ReadConfigParams(std::string config_path);
	virtual void PrintParams();
	virtual void WriteLogInfo(std::string log_file);

};

#endif // ABSTRACTUTERINECELLFACTORY_HPP
