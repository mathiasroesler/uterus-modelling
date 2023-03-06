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
	const std::string CONFIG_DIR = 
		"/usr/local/config/";
	const std::string GENERAL_PARAM_FILE = 
		"3d_params.toml";
}

class AbstractUterineCellFactory3d : public AbstractCardiacCellFactory<3>
{
protected:
	std::string mpCell_type;
	unsigned short int mpCell_id; // 0 = HH, 1 = CK, 2 = Means, 3 = Tong


public:
	AbstractUterineCellFactory3d();
	AbstractCardiacCell* CreateCardiacCellForTissueNode(Node<3>* pNode);
	std::string GetCellType();
	void ReadParams(std::string general_param_file);
	virtual void ReadCellParams(std::string cell_param_file);
	virtual void PrintParams();
	virtual void WriteLogInfo(std::string log_file);

};

#endif // ABSTRACTUTERINECELLFACTORY3d_HPP

