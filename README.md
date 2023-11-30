# Chaste uterine modeling

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

### Edits

Copy the **config** and **scripts** folder from the uterus-modelling project to the Chaste top-level directory and create the **testoutput** folder.

The project uses environment variables that need to be updated in order to run the project. Open the **chaste-env** script in a text editor and change the **CHASTE_DIR** variable to be the path from / to the Chaste top-level directory. Make sure that the **CHASTE_SOURCE_DIR** and **CHASTE_BUILD_DIR** variables are using the correct names of the source and build directory, respectively. The **APPTAINERENV_** variables should also be updated accordingly. 

### Ready to build
Run the setup_project.py script in the uterus-modelling folder in the **src** directory and answer the prompted questions. This project only uses cardiac chaste.

In the Chaste build folder run the following command to update the CMakeLists
```
$ cmake .
```

Navigate to the uterus-modelling folder in the **build** directory and run the following command to build the project
```
$ cmake --build .
```

### Testing
Source the **chaste-env** script in the scripts folder in the Chaste top-level directory to update the environment variables
```
$ source chaste-env
```

In the uterus-modelling folder in the **build** directory run the tests and make sure that they all pass
```
$ ctest 
```

## Running simulations
**The chaste-env script needs to be sourced before running the first simulation in a new terminal**

The simulations are piloted through the config files found in the **config** folder of the Chaste top-level directory and the **chaste-simulation** script found in the **scripts** folder of the Chaste top-level directory.

The **chaste-simulation** script as one argument: the dimension of the simulation. Valid options are 0, 2, and 3. Depending on the dimension, the 0d_, 2d_ or 3d_params.toml file will be used. The parameters for the different cell types are found in the config files with their respective name. 

The results of each simulation are stored in the **testoutput** folder with the following path monodomain_DIM/CELL/results, where DIM is the **chaste-simulation** input dimension and CELL is the cell name found in the config file. A log file is created for each simulation which saves the parameters used for the simulation. 

**Note:** for 0D simulations the results are stored directly in the 0d_simulation folder. 

**Note:** the results folder is not automatically created and needs to be done manually otherwise the results will not be saved.