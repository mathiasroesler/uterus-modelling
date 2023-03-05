#ifndef ABSTRACTUTERINECELLFACTORY3d_HPP
#define ABSTRACTUTERINECELLFACTORY3d_HPP

#include <toml.hpp>
#include "MonodomainProblem.hpp"
#include "ZeroStimulus.hpp"
#include "HodgkinHuxley1952.hpp"
#include "ChayKeizer1983.hpp"
#include "Means2022.hpp"
#include "Tong2014.hpp"

namespace USMC_3D_SYSTEM_CONSTANTS
{
	const std::string CONFIG_PATH = 
		"/usr/local/config/3d_params.toml";
}

class AbstractUterineCellFactory3d : public AbstractCardiacCellFactory3d<3>
{
protected:
	std::string mpCell_type;
	unsigned short int mpCell_id; // 0 = HH, 1 = CK, 2 = Means, 3 = Tong


public:
	AbstractUterineCellFactory3d();
    AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<3>* pNode);
	std::string GetCellType();
	virtual void ReadConfigParams(std::string config_path);
	virtual void PrintParams();
	virtual void WriteLogInfo(std::string log_file);

};

#endif // ABSTRACTUTERINECELLFACTORY3d_HPP

