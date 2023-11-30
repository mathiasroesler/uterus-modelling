# Chaste uterine modeling
# Table of contents
1. [General setup](#general-setup)
   1. [Edits](#edits)
   2. [Ready to build](#build)
   3. [Testing](#testing)
2. [Configuration files](#config)
	1. [Cells](#cells)
	2. [0D simulations](#0d)
	3. [2D simulations](#2d)
	4. [3D simulations](#3d)
2. [Running simulations](#simulations)

<a id="general-setup"></a>
## General setup
This setup guide assumes that the uterine version of [Chaste](https://github.com/mathiasroesler/chaste/tree/uterine-chaste) has been built successfully. Here is an example of the directory tree:
```
Chaste/ (top-level directory)
|
|-- src/ (source code directory)
|	|-- projects/
|		|--uterus-modelling/ (this project)
|		   |-- config/
|		   |-- scripts/
|			|-- chaste-env
|			|-- chaste-simulation
|-- lib/ (build directory)
|-- testoutput/ (results directory)
|-- config/ (cp from uterus-modelling)
|-- scripts/ (cp from uterus-modelling)
```

Clone the project in the projects folder of the Chaste source code.

<a id="edits"></a>
### Edits

Copy the **config** and **scripts** folder from the _uterus-modelling_ project to the Chaste top-level directory and create the **testoutput** folder.

The project uses environment variables that need to be updated in order to run the project. Open the **chaste-env** script in a text editor and change the **CHASTE_DIR** variable to be the path from **/** to the Chaste top-level directory. Make sure that the **CHASTE_SOURCE_DIR** and **CHASTE_BUILD_DIR** variables are using the correct names of the source and build directory, respectively.

**Note:** the **APPTAINERENV_** variables are only used on the HPCs and don't have to be updated.

It is recommended to update the user's **.bashrc** file to source the **chaste-env** script automatically when opening a new terminal window. Open the **.bashrc** file in a text editor:

```
$ gedit ~/.bashrc
```

Add the following line at the end of the file after replacing __path_to_Chaste__ with the path to the Chaste top-level directory:

```
source ${HOME}/path_to_Chaste/Chaste/scripts/chaste-env
```


<a id="build"></a>
### Ready to build
Run the **setup_project.py** script in the _uterus-modelling_ folder in the **src** directory and answer the prompted questions. 
 
**Note:** this project only uses cardiac Chaste.

In the Chaste build folder run the following command to update the CMakeLists
```
$ cmake .
```

Navigate to the _uterus-modelling_ folder in the **build** directory and run the following command to build the project
```
$ cmake --build .
```

<a id="testing"></a>
### Testing
Source the **chaste-env** script in the scripts folder in the Chaste top-level directory to update the environment variables
```
$ source chaste-env
```

In the _uterus-modelling_ folder in the **build** directory run the tests and make sure that they all pass
```
$ ctest 
```

<a id="config"></a>
## Configuration files

The project uses [TOML](https://toml.io/en/) configuration files to edit simulation and cell parameters. An example of configuration files for the different simulations and each available cell type are found in the **config** folder of the _uterus-modelling_ folder in the **src** directory. 

**Note:** the configuration files used during the simulations are located in the **config** folder of the Chaste top-level directory. 

<a id="cells"></a>
### Cells

The cell configuration files are all structured in the same way:
1. _Cell properties_ which consists of the capacitance and conductivities for 2D and 3D simulations;
2. _Stimulus_ contains the settings of the stimulus, the magnitude, period (only used if a regular stimulus is applied), the duration, and the start time;
3. _cell_id_ is the unique identifier of the cell. There are currently 4 different cells;
4.  _Cell parameters_ which lists the modifiable parameters in the CellML model. 

The three first categories are required for the cell model to work. The _Cell parameters_ category should only contain the name and value of parameters that have been identified as modifiable in the CellML model. However, if the parameter is modifiable it does not need to be listed for the cell model to work, the default value will be used instead. 
	
**Note:** The units are specified as comments after _Cell properties_ and _Stimulus_ parameters. The initial value and range are specified after _Cell parameters_ parameters. 

<a id="0d"></a>
### 0D simulations

<a id="2d"></a>
### 2D simulations

<a id="3d"></a>
### 3D simulations

<a id="simulations"></a>
## Running simulations

The simulations are piloted through the config files found in the **config** folder of the Chaste top-level directory and the **chaste-simulation** script found in the **scripts** folder of the Chaste top-level directory.

The **chaste-simulation** script as one argument: the dimension of the simulation. Valid options are 0, 2, and 3. Depending on the dimension, the 0d_, 2d_ or 3d_params.toml file will be used. The parameters for the different cell types are found in the config files with their respective name. 

The results of each simulation are stored in the **testoutput** folder with the following path monodomain_DIM/CELL/results, where DIM is the **chaste-simulation** input dimension and CELL is the cell name found in the config file. A log file is created for each simulation which saves the parameters used for the simulation. 

**Note:** for 0D simulations the results are stored directly in the 0d_simulation folder. 

**Note:** the **results** folder is not automatically created and needs to be done manually otherwise the results will not be saved.

