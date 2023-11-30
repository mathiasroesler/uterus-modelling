# Chaste uterine modeling
# Table of contents
1. [General setup](#general-setup)
   1. [Edits](#edits)
   2. [Ready to build](#build)
   3. [Testing](#testing)
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

<a id="simulations"></a>
## Running simulations

The simulations are piloted through the config files found in the **config** folder of the Chaste top-level directory and the **chaste-simulation** script found in the **scripts** folder of the Chaste top-level directory.

The **chaste-simulation** script as one argument: the dimension of the simulation. Valid options are 0, 2, and 3. Depending on the dimension, the 0d_, 2d_ or 3d_params.toml file will be used. The parameters for the different cell types are found in the config files with their respective name. 

The results of each simulation are stored in the **testoutput** folder with the following path monodomain_DIM/CELL/results, where DIM is the **chaste-simulation** input dimension and CELL is the cell name found in the config file. A log file is created for each simulation which saves the parameters used for the simulation. 

**Note:** for 0D simulations the results are stored directly in the 0d_simulation folder. 

**Note:** the **results** folder is not automatically created and needs to be done manually otherwise the results will not be saved.
